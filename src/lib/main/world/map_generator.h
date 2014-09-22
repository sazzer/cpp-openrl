#ifndef OPENRL_WORLD_MAP_GENERATOR_H
#define OPENRL_WORLD_MAP_GENERATOR_H

#include "world/overview.h"
#include "rng.h"

namespace World {
    /**
     * Class encapsulating a map generator
     */
    class MapGenerator {
    public:
        /**
         * Construct the map generator
         * @param rng The RNG to use
         */
        MapGenerator(Rng& rng);
        /**
         * Generate a map
         * @param width The width of the map to generate
         * @param height The height of the map to generate
         * @return the generated map
         */
        Overview generateMap(const uint16_t width, const uint16_t height);
    private:
        /**
         * Generate the continent layout
         * @param overview The overview map to populate
         */
        void generateContinents(Overview& overview);

        /** The RNG to use */
        Rng& rng_;
    };
}

#endif
