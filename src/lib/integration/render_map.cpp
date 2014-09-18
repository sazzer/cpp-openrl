#include "world/overview.h"
#include "png/png.h"
#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    Png::Png png(filename);
}

/**
 * Generate a map and render it to a PNG file
 */
int main(void) {
    World::Overview overviewMap(4000, 4000);
    renderMapToFile(overviewMap, "/tmp/map.png");
}
