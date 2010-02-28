#include <iostream>
#include "nth_prime.hpp"


int main(int argc, char* argv[])
{

    // std::cout << "Is 2 prime?" << is_prime<2>::value;
    // std::cout << "Is 3 prime?" << is_prime<3>::value;
    // std::cout << "Is 4 prime?" << is_prime<4>::value;
    // std::cout << "Is 5 prime?" << is_prime<5>::value;
    // std::cout << "Is 6 prime?" << is_prime<6>::value;
    std::cout << "What is the 100th prime?" << nth_prime<100>::value;
    return 0;
}
