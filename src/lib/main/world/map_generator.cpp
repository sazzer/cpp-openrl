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
            landTiles[i] = (rng_.generate<double>(distribution) > 0.4);
        }

        // Run the actual CA process, changing every tile to land if 5/9s of the 3x3 area are land
        // And changing the tile to water otherwise
        for (uint16_t i = 0; i < 5; ++i) {
            LOG(TRACE) << "Running CA process: " << i;
            std::vector<bool> nextLandTiles = landTiles;
            for (uint16_t y = 0; y < overview.height(); ++y) {
                for (uint16_t x = 0; x < overview.width(); ++x) {
                    int landCount = 0;
                    for (int slx = -2; slx <= 2; ++slx) {
                        for (int sly = -2; sly <= 2; ++sly) {
                            bool isLand;
                            if (slx + x <= 0) {
                                isLand = false;
                            } else if (sly + y <= 0) {
                                isLand = false;
                            } else if (slx + x >= overview.width()) {
                                isLand = false;
                            } else if (sly + y >= overview.height()) {
                                isLand = false;
                            } else {
                                auto landTilesOffset = overview.tileIndex(slx + x, sly + y);
                                isLand = landTiles[landTilesOffset];
                            }
                            if (isLand) {
                                ++landCount;
                            }
                        }
                    }
                
                    auto landTilesOffset = overview.tileIndex(x, y);
                    bool isNewLand = landCount >= 15;
                    nextLandTiles[landTilesOffset] = isNewLand;
                }
            }
            std::swap(landTiles, nextLandTiles);
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
