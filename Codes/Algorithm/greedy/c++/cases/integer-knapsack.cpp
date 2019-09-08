/*
    1/0 Knapsack (Integer Knapsack)
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ integer-knapsack.cpp -o integer-knapsack

    [gcc]
    $ g++ integer-knapsack.cpp -o integer-knapsack

    [msvc]
    $ cl integer-knapsack.cpp

Run:
    $ integer-knapsack
*/
#include <vector>
#include <algorithm>

/*
Masalah:
    Diberikan n buah objek dan sebuah knapsack (kantong) dengan kapasitas bobot K.
    Setiap objek memiliki properti bobot (weight) w, dan keuntungan (profit) p.
    Tentukan komposisi objek yang dimasukkan ke dalam knapsack sedemikian hingga
    memaksimumkan keuntungan. Total bobot objek yang dimasukkan ke dalam knapsack
    tidak boleh melebihi kapasitas knapsack.
    
Solusi:
    beberapa variasi solusi
    - greedy by profit
      pada setiap langkah, knapsack diisi dengan objek yang memiliki keuntungan terbesar.
    - greedy by weight
      pada setiap langkah, knapsack diisi dengan objek yang memiliki berat paling ringan
    - greedy by density
      pada setiap langkah, knapsack diisi dengan objek yang memiliki kepadatan, p/w, 
      terbesar.
*/

// ======================================================================================

struct item_t 
{
    int object_id;
    int weight;
    int profit;
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

auto algorithm(item_t arr[], size_t size, int capacity)
{
    std::vector<item_t> result;
    int weight = 0;

    // urutkan objek berdasarkan profit
    std::sort(arr, arr + size, compare_profit);

    // pemilihan objek
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            result.push_back(arr[i]);
            weight += arr[i].weight;
        }
    }

    return result;
}

// ======================================================================================

/** Iterative Solution -- greedy by weight **/

auto algorithm(item_t arr[], size_t size, int capacity)
{
    std::vector<item_t> result;
    int weight = 0;

    // urutkan objek berdasarkan weight (bobot)
    std::sort(arr, arr + size, compare_weight);

    // pemilihan objek
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            result.push_back(arr[i]);
            weight += arr[i].weight;
        }
    }

    return result;
}

// ======================================================================================

/** Iterative Solution -- greedy by density **/

auto algorithm(item_t arr[], size_t size, int capacity)
{
    std::vector<item_t> result;
    int weight = 0;

    // urutkan item berdasarkan densitas (kepadatan)
    std::sort(arr, arr + size, compare_density);

    // pemilihan objek
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i].weight + weight <= capacity)
        {
            result.push_back(arr[i]);
            weight += arr[i].weight;
        }
    }

    return result;
}