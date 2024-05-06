#ifndef CIMAGE_PROCESSOR_H
#define CIMAGE_PROCESSOR_H

#include "../build/libjpeg/include/jpeglib.h"

class CImageProcessor {
private:
    // TODO think about thread pool to paralize processing

    jpeg_decompress_struct m_DecompressObj;
    jpeg_compress_struct m_CompressObj;
    jpeg_error_mgr m_ErrorMng;

    JSAMPARRAY m_Buffer;

    void initAndReadImage(FILE* const source);
    void initAndWriteImage(FILE* const result);
    void finishAndDestroy();
    void executeDeinterlaceBlending();

public:
    CImageProcessor() noexcept;
    ~CImageProcessor() {};
    void runDeinterlaceProcess(FILE* const source, FILE* const result);
};

#endif // CIMAGE_PROCESSOR_H