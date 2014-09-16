#ifndef OPENGL_WORLD_OVERVIEW_H
#define OPENGL_WORLD_OVERVIEW_H

#include <vector>

namespace World {
    /**
     * Representation of a single tile on the overview map
     */
    class OverviewTile {
        public:
        /**
         * Get the height of the tile
         * @return the height of the tile
         */
        uint8_t height() const {
            return height_;
        }
        /**
         * Set the height of the tile
         * @param height The height of the tile
         */
        void height(const uint8_t height) {
            height_ = height;
        }
        private:
        /** The height of the tile */
        uint8_t height_;
    };
    
    /**
     * Representation of the overview map of the world
     */
    class Overview {
        public:
        /**
         * Create the overview map
         * @param width The width of the world. Note that these are Overview units which equate to 1km.
         * @param height The height of the world. Note that these are Overview units which equate to 1km.
         */
        Overview(const uint16_t width, const uint16_t height);
        /**
         * Get the width of the world
         * @return the width of the world
         */
        uint16_t width() const {
            return width_;
        }
        /**
         * Get the height of the world
         * @return the height of the world
         */
        uint16_t height() const {
            return height_;
        }
        /**
         * Get the tile at the given X and Y co-ordinates
         * @param x The X-Ordinate
         * @param y The Y-Ordinate
         * @return the tile
         */
        const OverviewTile& at(const uint16_t x, const uint16_t y) const {
            return tiles_[tileIndex(x, y)];    
        }
        /**
         * Get the tile at the given X and Y co-ordinates
         * @param x The X-Ordinate
         * @param y The Y-Ordinate
         * @return the tile
         */
        OverviewTile& at(const uint16_t x, const uint16_t y) {
            return tiles_[tileIndex(x, y)];
        }
        private:
        /**
         * Calculate the index into the tiles vector for the given co-ordinates
         * @param x The X-Ordinate
         * @param y The Y-Ordinate
         * @return the index into the tiles vector
         */
        size_t tileIndex(const uint16_t x, const uint16_t y) const;
        
        /** The width of the world */
        const uint16_t width_;
        /** The height of the world */
        const uint16_t height_;
        /** The actual tiles that make up the world */
        std::vector<OverviewTile> tiles_;
    };    
}

#endif // OPENGL_WORLD_OVERVIEW_H
