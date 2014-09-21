#include <bandit/bandit.h>
#include "rng.h"

using namespace bandit;

go_bandit([](){
        describe("RNG", [&](){
                Rng rng;
                it("Generates random ints", [&](){
                        std::uniform_int_distribution<uint16_t> distribution(1, 6);
                        auto result = rng.generate<uint16_t>(distribution);
                        AssertThat(result, Is().Not().LessThan(1).And().Not().GreaterThan(6));
                    });
                it("Generates lots of random ints", [&](){
                        uint16_t values[6]{0, 0, 0, 0, 0, 0};
                        std::uniform_int_distribution<uint16_t> distribution(0, 5);
                        for (uint16_t i = 0; i < 60000; ++i) {
                            auto result = rng.generate<uint16_t>(distribution);
                            ++values[result];
                        }
                        for (uint16_t i = 0; i < 6; ++i) {
                            std::cout << i << ": " << values[i] << std::endl;
                            // For now we'll check that the generated values are within 10% of uniform
                            AssertThat(values[i], Is().GreaterThan(9000).And().LessThan(11000));
                        }
                    });
            });
    });
