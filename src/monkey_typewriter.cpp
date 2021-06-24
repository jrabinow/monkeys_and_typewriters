#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

#include <unistd.h>

#include "pcg_random.hpp"


int main(int argc, char *argv[])
{
    // this is Monke. Monke has a typewriter he can bang on
    pcg32_k16384 monkey_typewriter_combo;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " STATEFILE" << std::endl;
        exit(0);
    }
    std::ifstream bananas (argv[1], std::ios::in);
    // feed Monke some bananas
    bananas >> monkey_typewriter_combo;
    if (bananas.fail())
        abort();

    constexpr size_t BUFFER_SIZE = 1024ull * 128ull;
    uint32_t buffer[BUFFER_SIZE];
    constexpr size_t ROUNDS = 1024ull * 1024ull / sizeof(buffer);

    std::ofstream shakespeare_file ("data.raw", std::ios::out | std::ios::binary);

    for (size_t i = 0; i < ROUNDS; ++i) {
        for (auto& monkey_keypress : buffer)
            // Monke bangs on the typewriter
            monkey_keypress = monkey_typewriter_combo();
        shakespeare_file.write((char*) buffer, sizeof(buffer));
    }
    std::cout << "check out data.raw. Hint, it may be a zip file" << std::endl;

    return 0;
}
