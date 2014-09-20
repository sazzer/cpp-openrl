#include "world/overview.h"
#include "png/png.h"
#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    Png::PngData pngData;
    pngData.width = 50;
    pngData.height = 50;
    pngData.title = "Colours";
    
    Png::Png png(filename, pngData);
    LOG(DEBUG) << "Starting rows";
    for (uint16_t r = 0; r < pngData.height; ++r) {
        LOG(DEBUG) << "Row: " << r;
        std::vector<Png::RGB> row;
        for (uint16_t g = 0; g < pngData.width; ++g) {
            row.push_back({(uint8_t)r, (uint8_t)g, 0});
        }
        png.writeRow(row);
    }
    LOG(DEBUG) << "Finished rows";
}

/**
 * Generate a map and render it to a PNG file
 */
int main(void) {
    World::Overview overviewMap(4000, 4000);
    renderMapToFile(overviewMap, "/tmp/map.png");
}
