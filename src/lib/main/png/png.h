#ifndef OPENRL_PNG_H
#define OPENRL_PNG_H

#include <string>

namespace Png {
    /**
     * Wrapper around the details necessary for writing PNG files
     */
    class Png {
    public:
        /**
         * Construct the PNG
         * @param filename The file to write to
         */
        Png(const std::string& filename);
        /**
         * Destroy the PNG
         */
        ~Png();
    private:
        /** The private implementation details */
        struct Impl;
        /** The pointer to the private implementation details */
        Impl* pImpl;
    };
}

#endif /* OPENRL_PNG_H */
