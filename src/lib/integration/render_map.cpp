#include "world/overview.h"
#include <string>
#include <png.h>
#include <iostream>
#include <memory>

void fileCloser(FILE* file) {
        fclose(file);
        std::cerr << "Closing file: " << file << std::endl;    
}

std::unique_ptr<FILE, void(*)(FILE*)> openFile(const std::string& filename, const std::string& mode) {
    FILE* fp = fopen(filename.c_str(), mode.c_str());
    std::cerr << "Opened file: " << fp << std::endl;
    return std::unique_ptr<FILE, void(*)(FILE*)>(fp, fileCloser);
}

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    auto fp = openFile(filename, "wb");
    if (!fp) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }
}

/**
 * Generate a map and render it to a PNG file
 */
int main(void) {
    World::Overview overviewMap(4000, 4000);
    renderMapToFile(overviewMap, "/tmp/map.png");
}
