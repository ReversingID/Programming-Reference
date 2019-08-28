/*
    Reverse Polish Notation
    Archive of Reversing.ID
    Design Pattern (Behavioral/Interpreter)

Compile:
    [clang]
    $ clang++ rpn.cpp -o rpn
    
    [gcc]
    $ g++ rpn.cpp -o rpn

    [msvc]
    $ cl rpn.cpp

Run:
    $ rpn

Note:
    Interpretasi dapat beragam dan tergantung kepada situasi dari aplikasi
    serta kondisi yang akan diinterpretasikan.
*/
#include <memory>
#include <map>
#include <list>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Expression;

using ExpressionPtr = std::shared_ptr<Expression>;
using Map   = std::map<std::string, ExpressionPtr>;
using Stack = std::list<ExpressionPtr>;

// ======================================================================================

/**
 * Expression (abstract)
 * 
 * Representasi sebuah ekspresi aritmatika
 */
class Expression
{
public:
    virtual ~Expression() { }

    virtual int interpret(Map variables) = 0;
};

// ======================================================================================

/**
 * Number (concrete)
 * 
 * Representasi angka
 */
class Number : public Expression 
{
    int _value;

public:
    Number(int value) : _value{value}
    { }

    int interpret(Map variables) override
    {
        return _value;
    }
};

// ======================================================================================

/**
 * Plus (concrete)
 * 
 * Representasi operasi penjumlahan
 */
class Plus : public Expression 
{
    ExpressionPtr _left;
    ExpressionPtr _right;

public:
    Plus(ExpressionPtr left, ExpressionPtr right) : _left{left}, _right{right}
    { }

    int interpret(Map variables) override
    {
        return _left->interpret(variables) + _right->interpret(variables);
    }
};

// ======================================================================================

/**
 * Minus (concrete)
 * 
 * Representasi operasi penjumlahan
 */
class Minus : public Expression 
{
    ExpressionPtr _left;
    ExpressionPtr _right;

public:
    Minus(ExpressionPtr left, ExpressionPtr right) : _left{left}, _right{right}
    { }

    int interpret(Map variables) override
    {
        return _left->interpret(variables) - _right->interpret(variables);
    }
};

// ======================================================================================

/**
 * Variable (concrete)
 * 
 * Representasi variable
 */
class Variable : public Expression 
{
    std::string _name;

public:
    Variable (std::string name) : _name{name}
    { }

    int interpret(Map variables) override
    {
        if (variables.end() == variables.find(_name)) return 0;
        return variables[_name]->interpret(variables);
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
    // Membangun objek expression dari string
    Evaluator (std::string expression)
    {
        Stack _expStack;

        size_t last = 0;
        for (size_t next = 0; std::string::npos != last; last = (std::string::npos == next) ? next : (1+next)) 
        {
            next = expression.find(' ', last);
            std::string token( expression.substr(last, (std::string::npos == next) ? (expression.length()-last) : (next-last)));

                if  (token == "+") {
                    auto right = _expStack.back(); _expStack.pop_back();
                    auto left  = _expStack.back(); _expStack.pop_back();
                    auto expr  = std::make_shared<Plus>(left, right);
                    _expStack.push_back(expr);
                }
                else if (token == "-") {
                    auto right = _expStack.back(); _expStack.pop_back();
                    auto left  = _expStack.back(); _expStack.pop_back();
                    auto expr  = std::make_shared<Minus>(left, right);
                    _expStack.push_back(expr);
                }
                else                        
                    _expStack.push_back(std::make_shared<Variable>(token));
        }

        _expression = _expStack.back();
        _expStack.pop_back();
    }

    int interpret(Map context) override
    {
        return _expression->interpret(context);
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    Evaluator sentence("w x z - +");

    static const int sequences[][3] = {
        {5, 10, 42}, {1, 3, 2}, {7, 9, -5}
    };

    for (size_t i = 0; i < 3; i++)
    {
        Map variables;
        variables["w"] = std::make_shared<Number>(sequences[i][0]);
        variables["x"] = std::make_shared<Number>(sequences[i][1]);
        variables["z"] = std::make_shared<Number>(sequences[i][2]);

        int result = sentence.interpret(variables);

        std::cout << "Interpreter result: " << result << std::endl;
    }

    return 0;
}