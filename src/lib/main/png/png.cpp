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
        FILE* file() const {
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
        PngWrite(PngFile& file) {
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

            png_init_io(png_, file.file());
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
                png_write_end(png_, NULL);
                png_destroy_write_struct(&png_, (png_infopp)NULL);
                LOG(DEBUG) << "Destroyed PNG Write Structure: " << png_;
            }
        }

        /**
         * Set the metadata of the PNG
         * @param data The metadata
         */
        void setData(const PngData& data) {
            LOG(DEBUG) << "Setting the PNG data";
            png_set_IHDR(png_,
                         pngInfo_,
                         data.width,
                         data.height,
                         data.bitDepth,
                         PNG_COLOR_TYPE_RGB,
                         PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_BASE,
                         PNG_FILTER_TYPE_BASE);
            if (!data.title.empty()) {
                LOG(DEBUG) << "Setting the PNG title to: " << data.title;
                png_text titleText;
                titleText.compression = PNG_TEXT_COMPRESSION_NONE;
                titleText.text = (png_charp)data.title.c_str();
                titleText.key = (png_charp)"Title";
                png_set_text(png_, pngInfo_, &titleText, 1);
            }
            png_write_info(png_, pngInfo_);
            LOG(DEBUG) << "Written the PNG Info";
        }
        /**
         * Write a row of pixels to the file
         * @param row The row of pixels
         */
        void writeRow(const std::vector<RGB>& row) {
            std::vector<png_byte> rowData;
            rowData.resize(row.size() * 3);
            png_write_row(png_, (png_bytep)(&(rowData[0])));
            LOG(DEBUG) << "Written a row of PNG image data of size: " << rowData.size();
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
    
    Png::Png(const std::string& filename, const PngData& data) : pImpl(new Png::Impl) {
        pImpl->pngFile.reset(new PngFile(filename, "wb"));
        pImpl->pngWrite.reset(new PngWrite(*(pImpl->pngFile)));
        pImpl->pngWrite->setData(data);
    }
    Png::~Png() {
        delete pImpl;
    }
    /**
     * Write a row of pixels to the file
     * @param row The row of pixels
     */
    void Png::writeRow(const std::vector<RGB>& row) {
        pImpl->pngWrite->writeRow(row);
    }
}
