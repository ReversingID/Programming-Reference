/*
    Interpreter
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ interpreter.cpp -o interpreter
    
    [gcc]
    $ g++ interpreter.cpp -o interpreter

    [msvc]
    $ cl interpreter.cpp

Run:
    $ interpreter
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Context { };

// ======================================================================================

/**
 * Expression (abstract)
 * 
 * Representasi sebuah ekspresi yang akan diinterpretasi.
 */
class Expression
{
public:
    virtual ~Expression() { }

    virtual int interpret(const Context & ctx) = 0;
};

using ExpressionPtr = std::shared_ptr<Expression>;

// ======================================================================================

/**
 * TerminalExpr (concrete)
 * 
 * Representasi node terminal pada expression.
 */
class TerminalExpr : public Expression 
{
    std::string _statement;

public:
    TerminalExpr(std::string statement) : _statement{statement}
    { }

    int interpret(const Context & ctx) override
    {
        std::cout << "[TerminalExpr] -> " << _statement << std::endl;
        return 0;
    }
};

// ======================================================================================

/**
 * NonTerminalExpr (concrete)
 * 
 * Representasi node non-terminal pada expression.
 */
class NonTerminalExpr : public Expression 
{
    ExpressionPtr   _expression;
    int _times;

public:
    NonTerminalExpr(ExpressionPtr expression, int times)
        : _expression{expression}, _times{times}
    { }

    int interpret(const Context & ctx) override
    {
        std::cout << "[NonTerminalExpr] :: " << _times << std::endl;
        for (int i = 0; i < _times; i++)
            _expression->interpret(ctx);
        return 0;
    }
};

// ======================================================================================

/**
 * Evaluator (concrete)
 * 
 * Evaluasi sebuah ekspresi
 */
class Evaluator : public Expression 
{
    ExpressionPtr _expression;

public:
    // Membangun objek expression dari representasi mentah
    Evaluator (std::string expression)
    { }

    void set(ExpressionPtr expression)
    {
        _expression = expression;
    }

    int interpret(const Context & context) override
    {
        return _expression->interpret(context);
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    Context ctx;

    auto tp  = std::make_shared<TerminalExpr>("echo");
    auto ntp = std::make_shared<NonTerminalExpr>(tp, 4);

    std::string raw = "expression should be here";
    auto eval = std::make_shared<Evaluator>(raw);
    eval->set(ntp);
    eval->interpret(ctx);

    return 0;
}