#include <iostream>
#include "nth_prime.hpp"


int main(int argc, char* argv[])
{
    std::cout << "What is the 100th prime?" << nth_prime<100>::value;

    return 0;
}
