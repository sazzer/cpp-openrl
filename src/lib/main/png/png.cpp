#include "png/png.h"
#include <memory>
#include <cstdio>
#include <easylogging++.h>
#include <png.h>

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

    /**
     * RAII Wrapper around a libpng png_structp object for writing PNG files
     */
    class PngWrite {
    public:
        /**
         * Construct the PNG Structure
         */
        PngWrite() {
            png_ = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            if (png_ == NULL) {
                LOG(ERROR) << "Failed to create PNG Write Structure";
                throw 1; // TODO: Fix
            }
            LOG(DEBUG) << "Created PNG Write Structure: " << png_;

            pngInfo_ = png_create_info_struct(png_);
            if (pngInfo_ == NULL) {
                LOG(ERROR) << "Failed to create PNG Info Structure";
                throw 1; // TODO: Fix
            }
            LOG(DEBUG) << "Created PNG Info Structure: " << pngInfo_;
        }
        /**
         * Destroy the PNG Structure
         */
        ~PngWrite() {
            if (pngInfo_) {
                png_free_data(png_, pngInfo_, PNG_FREE_ALL, -1);
                LOG(DEBUG) << "Destroyed PNG Info Structure";
            }
            if (png_) {
                png_destroy_write_struct(&png_, (png_infopp)NULL);
                LOG(DEBUG) << "Destroyed PNG Write Structure: " << png_;
            }
        }
    private:
        /** The PNG pointer */
        png_structp png_;
        /** The Info Pointer */
        png_infop pngInfo_;
    };
    
    struct Png::Impl {
        std::unique_ptr<PngFile> pngFile;
        std::unique_ptr<PngWrite> pngWrite;
    };
    
    Png::Png(const std::string& filename) : pImpl(new Png::Impl) {
        pImpl->pngFile.reset(new PngFile(filename, "wb"));
        pImpl->pngWrite.reset(new PngWrite);
    }
    Png::~Png() {
        delete pImpl;
    }
}
