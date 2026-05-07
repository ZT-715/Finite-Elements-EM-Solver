#include <iostream>

int main(int argc, char** argv) {
    std::printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        std::printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
