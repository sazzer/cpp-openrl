#ifndef OPENRL_RNG_H
#define OPENRL_RNG_H

#include <random>
#include <chrono>

/**
 * The RNG. This is the source of all random numbers in the entire system.
 * The only reason this class exists is so that a mocked version can be used for tests.
 */
class Rng {
public:
    /**
     * Seed the RNG with a random starting value
     */
    Rng() {
        auto now = std::chrono::high_resolution_clock::now();
        generator.seed(now.time_since_epoch().count());
    }
    /**
     * Actually generate a new random number from the provided distribution
     * @param distribution The distribution to generate from
     * @return the generated number
     */
    template <typename T, typename D>
    T generate(D& distribution) {
        return distribution(generator);
    }
private:
    /** The random number generator to use */
    std::mt19937 generator;
};

#endif /* OPENRL_RNG_H */
