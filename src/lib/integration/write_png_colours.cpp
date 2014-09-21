#include "png/png.h"
#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

/**
 * Generate a PNG file of colours
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    
    Png::PngData pngData;
    pngData.width = 256;
    pngData.height = 256;
    pngData.title = "Colours";
    
    Png::Png png(argv[1], pngData);
    LOG(DEBUG) << "Starting rows";
    for (uint16_t y = 0; y < pngData.height; ++y) {
        LOG(DEBUG) << "Row: " << y;
        std::vector<Png::RGB> row;
        for (uint16_t x = 0; x < pngData.width; ++x) {
            row.push_back({(uint8_t)y, (uint8_t)x, 0});
        }
        png.writeRow(row);
    }
    LOG(DEBUG) << "Finished rows";
}
