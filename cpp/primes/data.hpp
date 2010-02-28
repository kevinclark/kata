#ifndef DATA_HPP
#define DATA_HPP

template <typename T, T v>
struct data
{
    typedef T   value_type;
    static const value_type value = v;
};

#endif
