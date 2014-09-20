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
