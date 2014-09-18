#include "world/overview.h"
#include <string>
#include <png.h>
#include <iostream>
#include <memory>
#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

class File {
public:
    File(const std::string& filename, const std::string& mode) {
        LOG(DEBUG) << "Opening file: " << filename;
        fp = fopen(filename.c_str(), mode.c_str());
        if (!fp) {
            throw 1;
        }
        LOG(DEBUG) << "Opened file " << filename << " as " << fp;
    }
    ~File() {
        LOG(DEBUG) << "Closing file: " << fp;
    }
    const FILE* file() const {
        return fp;
    }
private:
    FILE* fp;
};

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    File file(filename, "wb");
}

/**
 * Generate a map and render it to a PNG file
 */
int main(void) {
    World::Overview overviewMap(4000, 4000);
    renderMapToFile(overviewMap, "/tmp/map.png");
}
