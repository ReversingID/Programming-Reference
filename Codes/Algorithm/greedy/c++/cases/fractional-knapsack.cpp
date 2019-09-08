/*
    Fractional Knapsack
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ fractional-knapsack.cpp -o fractional-knapsack

    [gcc]
    $ g++ fractional-knapsack.cpp -o fractional-knapsack

    [msvc]
    $ cl fractional-knapsack.cpp

Run:
    $ fractional-knapsack
*/
#include <vector>
#include <algorithm>

/*
    Variasi dari Knapsack Problem dengan item dapat berupa pecahan.

    Diberikan n buah objek dan sebuah knapsack (kantong) dengan kapasitas bobot K.
    Setiap objek memiliki properti bobot (weight) w, dan keuntungan (profit) p.
    Tentukan komposisi objek yang dimasukkan ke dalam knapsack sedemikian hingga
    memaksimumkan keuntungan. Total bobot objek yang dimasukkan ke dalam knapsack
    tidak boleh melebihi kapasitas knapsack.

Masalah:
    
Langkah:
*/

// ======================================================================================

struct item_t 
{
    int object_id;
    int weight;
    int profit;
    double ratio;
};

bool compare_profit(item_t a, item_t b)
{
    return (a.profit > b.profit);
}

bool compare_weight(item_t a, item_t b)
{
    return (a.weight < b.weight);
}

bool compare_density(item_t a, item_t b)
{
    return ((a.profit/a.weight) > (b.profit/b.weight));
}

// ======================================================================================

/** Iterative Solution -- greedy by profit **/

auto algorithm(item_t arr[], size_t size, double capacity)
{
    std::vector<item_t> result;
    int weight = 0;
    size_t i;

    // urutkan objek berdasarkan profit
    std::sort(arr, arr + size, compare_profit);

    // pemilihan objek
    for (i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            item_t t = arr[i];
            t.ratio = 1.0;

            result.push_back(t);
            weight += arr[i].weight;
        }
    }

    if (weight < capacity && i < size)
    {
        item_t t = arr[i];
        t.ratio = (capacity - weight)/t.weight;

        result.push_back(t);
    }

    return result;
}

// ======================================================================================

/** Iterative Solution -- greedy by weight **/

auto algorithm(item_t arr[], size_t size, double capacity)
{
    std::vector<item_t> result;
    int weight = 0;
    size_t i = 0;

    // urutkan objek berdasarkan weight (bobot)
    std::sort(arr, arr + size, compare_weight);

    // pemilihan objek
    for (i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            item_t t = arr[i];
            t.ratio = 1.0;

            result.push_back(t);
            weight += arr[i].weight;
        }
    }

    if (weight < capacity && i < size)
    {
        item_t t = arr[i];
        t.ratio = (capacity - weight)/t.weight;

        result.push_back(t);
    }


    return result;
}

// ======================================================================================

/** Iterative Solution -- greedy by density **/

auto algorithm(item_t arr[], size_t size, double capacity)
{
    std::vector<item_t> result;
    int weight = 0;
    size_t i;

    // urutkan item berdasarkan densitas (kepadatan)
    std::sort(arr, arr + size, compare_density);

    // pemilihan objek
    for (i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            item_t t = arr[i];
            t.ratio = 1.0;

            result.push_back(t);
            weight += arr[i].weight;
        }
    }

    if (weight < capacity && i < size)
    {
        item_t t = arr[i];
        t.ratio = (capacity - weight)/t.weight;

        result.push_back(t);
    }


    return result;
}