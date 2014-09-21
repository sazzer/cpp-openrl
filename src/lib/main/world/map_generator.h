#ifndef OPENRL_WORLD_MAP_GENERATOR_H
#define OPENRL_WORRD_MAP_GENERATOR_H

#include "world/overview.h"

namespace World {
    /**
     * Class encapsulating a map generator
     */
    class MapGenerator {
    public:
        /**
         * Generate a map
         * @param width The width of the map to generate
         * @param height The height of the map to generate
         * @return the generated map
         */
        Overview generateMap(const uint16_t width, const uint16_t height) const;
    private:
    };
}

#endif