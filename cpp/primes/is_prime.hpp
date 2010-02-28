#include "divides_by.hpp"
#include "static_if.hpp"

template <int n, int checking>
struct is_prime_impl
{
    typedef bool    value_type;

    static const bool value =
        ! divides_by<n, checking>::value &&
            // If we're checking an even,
            // bump it to an odd and try again
            static_if< checking % 2 == 0,
                is_prime_impl<n, checking + 1>,

                static_if< checking >= n / 2,
                    data<bool, true>,
                    is_prime_impl<n, checking + 2> // Avoid evens
                >
            >::value;
};

template <int checking>
struct is_prime_impl<3, checking>
{
    typedef bool    value_type;

    static const bool value = true;
};

template<int checking>
struct is_prime_impl<2, checking>
{
    typedef bool    value_type;

    static const bool value = true;
};


template <int n>
struct is_prime
{
    static const bool value = is_prime_impl<n, 2>::value;
};
