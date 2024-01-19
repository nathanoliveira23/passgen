#include <random>
#include "../includes/random.hpp"

std::uint32_t randInt(std::uint32_t begin, std::uint32_t end)
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<std::size_t> distribution(begin, end);

    return distribution(rng);
}
