#ifndef OPENGL_WORLD_OVERVIEW_H
#define OPENGL_WORLD_OVERVIEW_H

namespace World {
    /**
     * Representation of the overview map of the world
     */
    class Overview
    {
    public:
        /**
         * Create the overview map
         * @param width The width of the world. Note that these are Overview units which equate to 1km.
         * @param height The height of the world. Note that these are Overview units which equate to 1km.
         */
        Overview(const unsigned int width, const unsigned int height);
        /**
         * Get the width of the world
         * @return the width of the world
         */
        unsigned int width() const {
            return width_;
        }
        /**
         * Get the height of the world
         * @return the height of the world
         */
        unsigned int height() const {
            return height_;
        }
    private:
        /** The width of the world */
        const unsigned int width_;
        /** The height of the world */
        const unsigned int height_;
    };    
}

#endif // OPENGL_WORLD_OVERVIEW_H
