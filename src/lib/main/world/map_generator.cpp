#include "world/map_generator.h"

namespace World {
    Overview MapGenerator::generateMap(const uint16_t width, const uint16_t height) const {
        return Overview(width, height);
    }

}