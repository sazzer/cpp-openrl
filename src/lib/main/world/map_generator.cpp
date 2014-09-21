#include "world/map_generator.h"
#include <easylogging++.h>

namespace World {
    MapGenerator::MapGenerator(Rng& rng) : rng_(rng) {
        
    }
    
    void MapGenerator::generateContinents(Overview& overview) {
        LOG(DEBUG) << "Generating continents";
        std::vector<bool> landTiles;
        landTiles.resize(overview.width() * overview.height());
        
        // First step - randomly speckle the entire map
        LOG(TRACE) << "Speckling the map";
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        for (size_t i = 0; i < landTiles.size(); ++i) {
            landTiles[i] = (rng_.generate<double>(distribution) > 0.7);
        }

        // Finally, set the actual tiles as appropriate
        LOG(TRACE) << "Generating land tiles";
        for (uint16_t x = 0; x < overview.height(); ++x) {
            for (uint16_t y = 0; y < overview.width(); ++y) {
                auto landTilesOffset = overview.tileIndex(x, y);
                uint8_t h = (landTiles[landTilesOffset] ? 100 : 0);
                overview.at(x, y).height(h);
            }
        }
        LOG(DEBUG) << "Generated continents";
    }

    Overview MapGenerator::generateMap(const uint16_t width, const uint16_t height) {
        Overview result(width, height);
        generateContinents(result);

        return result;
    }

}
