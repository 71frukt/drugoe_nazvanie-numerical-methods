#pragma once

#include <vector>
#include <random>

template <std::floating_point T>
std::vector<T> BuildNormDistr(size_t arr_size, T mid, T deviation, std::mt19937& rd)
{
    std::normal_distribution<T> dist(mid, deviation);

    std::vector<T> result(arr_size);
    
    for (size_t i = 0; i < arr_size; ++i)
    {
        result[i] = dist(rd);
    }
    
    return result;
}