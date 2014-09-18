#include "png/png.h"
#include <memory>
#include <cstdio>
#include <easylogging++.h>

namespace Png {
    /**
     * RAII Wrapper around a C-Style FILE* pointer
     */
    class PngFile {
    public:
        /**
         * Open the file
         * @param filename The file to open
         * @param mode The mode to open the file in
         */
        PngFile(const std::string& filename, const std::string& mode) : file_(fopen(filename.c_str(), mode.c_str())) {
            LOG(DEBUG) << "Opening file: " << filename;
            if (!file_) {
                LOG(ERROR) << "Failed to open file: " << filename;
                throw 1; // TODO: Fix
            }
            LOG(DEBUG) << "Opened file " << filename << " as " << file_;
        }
        /**
         * Close the file
         */
        ~PngFile() {
            if (file_) {
                fclose(file_);
                LOG(DEBUG) << "Closed file " << file_;
            }
        }
        /**
         * Get the FILE pointer
         * @return the file pointer
         */
        const FILE* file() const {
            return file_;
        }
    private:
        /** The file pointer */
        FILE* file_;
    };

    struct Png::Impl {
        std::unique_ptr<PngFile> pngFile;
    };
    
    Png::Png(const std::string& filename) : pImpl(new Png::Impl) {
        pImpl->pngFile.reset(new PngFile(filename, "wb"));
    }
    Png::~Png() {
        delete pImpl;
    }
}
