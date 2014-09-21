#include "png/png.h"
#include <easylogging++.h>
#include "world/map_generator.h"

_INITIALIZE_EASYLOGGINGPP

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    Png::PngData pngData;
    pngData.width = map.width();
    pngData.height = map.height();
    pngData.title = "Map";
    
    Png::Png png(filename, pngData);
    LOG(DEBUG) << "Starting rows";
    for (uint16_t y = 0; y < pngData.height; ++y) {
        std::vector<Png::RGB> row;
        for (uint16_t x = 0; x < pngData.width; ++x) {
            auto height = map.at(x, y).height();
            if (height > 0) {
                row.push_back({0, 100, 0});
            } else {
                row.push_back({0, 0, 100});                
            }
        }
        png.writeRow(row);
    }
    LOG(DEBUG) << "Finished rows";
}

/**
 * Generate a PNG file of colours
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    
    Rng rng;
    World::MapGenerator mapGenerator(rng);
    World::Overview overviewMap = mapGenerator.generateMap(4000, 4000);
    renderMapToFile(overviewMap, argv[1]);
}
