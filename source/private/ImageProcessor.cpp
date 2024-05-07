#include <iostream>

#include "../ImageProcessor.h"

CImageProcessor::CImageProcessor() noexcept
    : m_DecompressObj()
    , m_CompressObj()
    , m_ErrorMng()
    , m_Buffer(nullptr)
{
}

void CImageProcessor::initAndReadImage(FILE* const source) {
    // Initialize libjpeg decompress structure
    m_DecompressObj.err = jpeg_std_error(&m_ErrorMng);
    jpeg_create_decompress(&m_DecompressObj);

    jpeg_stdio_src(&m_DecompressObj, source);

    jpeg_read_header(&m_DecompressObj, TRUE);

    m_DecompressObj.out_color_space = J_COLOR_SPACE::JCS_YCbCr;
    m_DecompressObj.jpeg_color_space = J_COLOR_SPACE::JCS_YCbCr;

    jpeg_start_decompress(&m_DecompressObj);

    std::cout << "JPEG File Information: \n";
    std::cout << "Image width and height: " << m_DecompressObj.image_width << " pixels and " << m_DecompressObj.image_height << "pixels.\n";
    std::cout << "Color components per pixel: " << m_DecompressObj.num_components << ".\n";
    std::cout << "Color space: " << m_DecompressObj.jpeg_color_space << ".\n";

    // Allocate memory for scanline buffers
    auto row_stride = m_DecompressObj.output_width * m_DecompressObj.output_components;
    m_Buffer = (*m_DecompressObj.mem->alloc_sarray)
    (reinterpret_cast<j_common_ptr>(&m_DecompressObj), JPOOL_IMAGE, row_stride, m_DecompressObj.output_height);

    // Read scanlines
    while (m_DecompressObj.output_scanline < m_DecompressObj.output_height) {
        jpeg_read_scanlines(&m_DecompressObj, &m_Buffer[m_DecompressObj.output_scanline], 1);
    }
}

void CImageProcessor::initAndWriteImage(FILE* const result) {
    // Initialize libjpeg compress structure
    m_CompressObj.err = jpeg_std_error(&m_ErrorMng);
    jpeg_create_compress(&m_CompressObj);
    jpeg_stdio_dest(&m_CompressObj, result);
    m_CompressObj.image_width = m_DecompressObj.output_width;
    m_CompressObj.image_height = m_DecompressObj.output_height;
    m_CompressObj.input_components = m_DecompressObj.output_components;
    m_CompressObj.in_color_space = m_DecompressObj.out_color_space;

    jpeg_set_defaults(&m_CompressObj);
    jpeg_simple_progression(&m_CompressObj);
    jpeg_start_compress(&m_CompressObj, TRUE);

    // Write scanlines
    while (m_CompressObj.next_scanline < m_CompressObj.image_height) {
        jpeg_write_scanlines(&m_CompressObj, &m_Buffer[m_CompressObj.next_scanline], 1);
    }
}

void CImageProcessor::runDeinterlaceProcess(FILE* const source, FILE* const result, int intensity) {

    initAndReadImage(source);

    executeDeinterlaceBlending(intensity);

    initAndWriteImage(result);

    finishAndDestroy();
}

void CImageProcessor::finishAndDestroy() {
    jpeg_finish_compress(&m_CompressObj);
    jpeg_destroy_compress(&m_CompressObj);

    jpeg_finish_decompress(&m_DecompressObj);
    jpeg_destroy_decompress(&m_DecompressObj);
}

void CImageProcessor::executeDeinterlaceBlending(int intensity)
{
    // Iterate over the image pixels and apply the "Blending" algorithm
    int i = 0;
    JDIMENSION totalWidth = m_DecompressObj.output_width * m_DecompressObj.output_components;
    while (i < intensity) {
        for (JDIMENSION y = 1; y < m_DecompressObj.output_height; ++y) {
            for (JDIMENSION x = 0; x < totalWidth; ++x) {
                m_Buffer[y][x] = (m_Buffer[y][x] + m_Buffer[y - 1][x]) / 2;
            }
        }
        ++i;
    }
}