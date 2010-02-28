#ifndef DIVIDES_BY_HPP
#define DIVIDES_BY_HPP

template <int lhs, int rhs>
struct divides_by
{
    static const bool value = lhs % rhs == 0;
};

#endif
