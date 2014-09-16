#include "overview.h"

namespace World {
    
    Overview::Overview(const uint16_t width, const uint16_t height)  :
        width_(width),
        height_(height)
    {
        tiles_.resize(width * height);
    }

    size_t Overview::tileIndex(const uint16_t x, const uint16_t y) const {
        return (x * height_) + y;
    }

}
