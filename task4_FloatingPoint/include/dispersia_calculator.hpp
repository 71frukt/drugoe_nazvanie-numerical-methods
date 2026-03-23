#pragma once

#include <vector>

template <std::floating_point T>
auto VarianceiaFast(const std::vector<T>& data)
{
    if (data.size() == 0)
        return T(0);

    T variance = 0;
    T mid = 0;

    for (size_t i = 0; i < data.size(); ++i)
    {
        variance  += data[i] * data[i];
        mid += data[i];
    }

    mid      /= data.size();
    variance /= data.size();

    return variance - mid * mid;    
}

template <std::floating_point T>
auto VarianceiaTwoPass(const std::vector<T>& data)
{
    if (data.size() == 0)
        return T(0);

    T mid = 0;

    for (size_t i = 0; i < data.size(); ++i)
    {
        mid += data[i];
    }
    mid /= data.size();

    T variance = 0;
    
    for (size_t i = 0; i < data.size(); ++i)
    {
        variance += (data[i] - mid) * (data[i] - mid);
    }
    variance /= data.size();

    return variance;
}

template <std::floating_point T>
auto VarianceiaOnePass(const std::vector<T>& data)
{
    if (data.size() == 0)
        return T(0);

    T m_prev  = data[0];
    T m_cur   = 0;

    T dx_prev = 0;
    T dx_cur  = 0;

    for (size_t i = 1; i < data.size(); ++i)
    {
        m_cur   = m_prev  + ( data[i] - m_prev) / (i + 1);
        dx_cur  = dx_prev + ((data[i] - m_prev) * (data[i] - m_cur) - dx_prev) / (i + 1);
        
        m_prev  = m_cur;
        dx_prev = dx_cur;
    }

    return dx_cur;
}