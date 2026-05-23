#include <filesystem>
#include <iostream>
#include "parse_msh.hpp"

int main(int argc, char** argv) {
    std::filesystem::path filename;

    std::printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        std::printf("argv[%d] = %s\n", i, argv[i]);
        if (i == 1) filename = argv[i];
    }

    std::printf("Executando Parser: \n");
    ifrs::parser::ParseMsh parser{filename};
    return 0;
}
