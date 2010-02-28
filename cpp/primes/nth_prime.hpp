#ifndef NTH_PRIME_HPP
#define NTH_PRIME_HPP

#include "static_if.hpp"
#include "is_prime.hpp"


template <int n, int starting_at>
struct nth_prime_impl
{
    typedef int     value_type;

    static const int next_n =
        static_if< is_prime<starting_at>::value, 
            data<int, n - 1>, 
            data<int, n>
        >::value;

    static const int next_check =
        static_if< starting_at % 2 == 0,
            data<int, starting_at + 1>,
            data<int, starting_at + 2>
        >::value;

    static const int value = nth_prime_impl< next_n, next_check>::value;
};

template <int starting_at>
struct nth_prime_impl<0, starting_at>
{
    typedef int     value_type;

    static const value_type value = starting_at;
};

template <int n>
struct nth_prime
{
    typedef int     value_type;
    
    static const value_type value = nth_prime_impl<n, 2>::value;
};

#endif
