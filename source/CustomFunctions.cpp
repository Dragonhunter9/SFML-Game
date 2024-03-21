#include "CustomFunctions.h"
#include <random>

int RandomNumber(const int min, const int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return (distribution(mt));
}