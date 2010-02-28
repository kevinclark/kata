#ifndef STATIC_IF_HPP
#define STATIC_IF_HPP

#include "data.hpp"

template <bool condition, typename true_branch, typename false_branch>
struct static_if;

template <typename true_branch, typename false_branch>
struct static_if<true, true_branch, false_branch>
{
    typedef typename true_branch::value_type value_type;
    static const value_type value = true_branch::value;
};

template <typename true_branch, typename false_branch>
struct static_if<false, true_branch, false_branch>
{
    typedef typename false_branch::value_type value_type;
    static const value_type value = false_branch::value;
};

#endif
