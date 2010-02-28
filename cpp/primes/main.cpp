#include <iostream>
#include "nth_prime.hpp"


int main(int argc, char* argv[])
{
    std::cout << "What is the 50th prime?" << nth_prime<50>::value;

    return 0;
}
