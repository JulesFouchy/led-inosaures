#pragma once

template<typename T>
T fract(T x)
{
    return x - floor(x);
}