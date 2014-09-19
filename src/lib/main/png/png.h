#ifndef OPENRL_PNG_H
#define OPENRL_PNG_H

#include <string>
#include <vector>

namespace Png {
    /**
     * Representation of the metadata about the PNG
     */
    struct PngData {
    public:
        /** The title of the PNG */
        std::string title = "";
        /** The width of the PNG */
        uint32_t width;
        /** The height of the PNG */
        uint32_t height;
        /** The bit-depth of the PNG */
        uint8_t bitDepth = 8;
    };

    /**
     * RGB Colour
     */
    struct RGB {
    public:
        /** Red */
        uint8_t r;
        /** Green */
        uint8_t g;
        /** Blue */
        uint8_t b;
    };
    
    /**
     * Wrapper around the details necessary for writing PNG files
     */
    class Png {
    public:
        /**
         * Construct the PNG
         * @param filename The file to write to
         * @param data The metadata of the PNG
         */
        Png(const std::string& filename, const PngData& data);
        /**
         * Destroy the PNG
         */
        ~Png();
        /**
         * Write a row of pixels to the file
         * @param row The row of pixels
         */
        void writeRow(const std::vector<RGB>& row);
    private:
        /** The private implementation details */
        struct Impl;
        /** The pointer to the private implementation details */
        Impl* pImpl;
    };
}

#endif /* OPENRL_PNG_H */
