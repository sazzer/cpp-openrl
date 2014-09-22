#include "world/map_generator.h"
#include <easylogging++.h>

namespace World {
    MapGenerator::MapGenerator(Rng& rng) : rng_(rng) {
        
    }
    
    struct Seed {
        uint16_t x;
        uint16_t y;
        uint16_t radius;
    };

    void MapGenerator::generateContinents(Overview& overview) {
        LOG(DEBUG) << "Generating continents";
        std::vector<bool> landTiles;
        landTiles.resize(overview.width() * overview.height());

        // The number of cells on the map is w*h
        // We want to achieve ~50% of this as land
        // We therefore want to calculate a number of seeds and an average radius to achieve this
        // This means that (numberOfSeeds * 3.14 * averageRadius * averageRadius) / (w*h) ~= 0.5
        // We need to fix either numberOfSeeds or averageRadius, and then calculate the other one.
        // Options for this are:
        
        // w and h are fixed. averageRadius can be just a random number. This means that we can
        // calculate numberOfSeeds from this.
        // The average radius is therefore going to be 5% of the width +- 10%;
        // The number of seeds is therefore:
        //// 0.5 * w * h = numberOfSeeds * 3.14 * averageRadius * averageRadius
        //// (0.5 * w * h) / (3.14 * averageRadius * averageRadius) = numberOfSeeds
        // For example: w = 4000, h = 4000, averageRadius = 200
        //// (0.5 * 4000 * 4000) / (3.14 * 200 * 200) = numberOfSeeds
        //// (8000000 / 125600) = numberOfSeeds
        //// 64 = numberOfSeeds
        // This gives a smaller number of larger seeds
        
        // w and h are fixed. numberOfSeeds can be just a random number. This means that we can
        // calculate averageRadius from this.
        // The number of seeds is therefore going to be 10% of the width +- 10%.
        // The average radius is therefore:
        //// 0.5 * w * h = numberOfSeeds * 3.14 * averageRadius * averageRadius
        //// (0.5 * w * h) / (numberOfSeeds * 3.14) = averageRadius ^ 2
        //// sqrt((0.5 * w * h) / (numberOfSeeds * 3.14)) = averageRadius
        // For example: w = 4000, h = 4000, numberOfSeeds = 400
        //// sqrt((0.5 * 4000 * 4000) / (400 * 3.14)) = averageRadius = 79
        // This gives a larger number of small seeds

        double landPercentage = 0.5;
        uint16_t numberOfSeeds = (overview.width() / 10);
        uint16_t averageRadius = sqrt((landPercentage * overview.width() * overview.height()) / (numberOfSeeds * 3.14));

        LOG(DEBUG) << "Land Percentage: " << landPercentage;
        LOG(DEBUG) << "Number of seeds: " << numberOfSeeds;
        LOG(DEBUG) << "Average Radius: " << averageRadius;

        uint16_t numberOfSeedsSD = numberOfSeeds / 20;
        uint16_t averageRadiusSD = averageRadius / 20;
        numberOfSeeds = rng_.generate<double>(std::normal_distribution<double>(numberOfSeeds, numberOfSeedsSD));
        averageRadius = rng_.generate<double>(std::normal_distribution<double>(averageRadius, averageRadiusSD));
        LOG(DEBUG) << "Number of seeds SD: " << numberOfSeedsSD;
        LOG(DEBUG) << "Average Radius SD: " << averageRadiusSD;
        LOG(DEBUG) << "Adjusted Number of seeds: " << numberOfSeeds;
        LOG(DEBUG) << "Adjusted Average Radius: " << averageRadius;

        LOG(DEBUG) << "Average seed percentage: " << (numberOfSeeds * 3.14 * averageRadius * averageRadius) / (overview.width() * overview.height());
        
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
