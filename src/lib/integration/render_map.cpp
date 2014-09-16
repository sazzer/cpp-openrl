#include "world/overview.h"
#include <string>
#include <png.h>

void renderMapToFile(const World::Overview& map, const std::string& filename) {
    
}

/**
 * Generate a map and render it to a PNG file
 */
int main(void) {
    World::Overview overviewMap(4000, 4000);
    renderMapToFile(overviewMap, "/tmp/map.png");
}
