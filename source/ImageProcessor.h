#ifndef CIMAGE_PROCESSOR_H
#define CIMAGE_PROCESSOR_H


class CImageProcessor {
private:
    CImageProcessor() {};
    // CImageProcessor(FILE* source, FILE* result);
    ~CImageProcessor() {};

    // TODO think about thread pool to paralize processing

public:

    void runDeinterlaceProcess(FILE* source, FILE* result);
};

#endif // CIMAGE_PROCESSOR_H