#ifndef ENTROPY_H
#define ENTROPY_H

#include <fstream>
#include <cmath>

#define FILENAME "res/lvls/entropy.dat"


static struct {
    void write() {
        std::ofstream out(FILENAME);
        out << (uint32_t) std::rand() << std::endl;
        out.close();
    }
    uint32_t read() {
        std::ifstream in(FILENAME);
        uint32_t seed;
        in >> seed;
        in.close();
        std::srand(seed);
        write();
        return std::rand();
    }
} Entropy;

#endif // ENTROPY_H
