#include <iostream>

#include "../FileManager.h"

CFileManager::CFileManager(const std::string& inputPath, const std::string& outputPath)
    : m_InputPath(inputPath)
    , m_OutputPath(outputPath)
{
}

FILE* CFileManager::getInputFile() {
    return m_InputFile.get();
}

FILE* CFileManager::getOutputFile() {
    return m_OutputFile.get();
}

bool CFileManager::isFilesSuccessfullyOpened() {

    bool isFilesOpened = false;
    auto inputFile = fopen(m_InputPath.c_str(), "rb");
    auto outputFile = fopen(std::string(m_OutputPath + "_out.jpg").c_str(), "wb");

    if (inputFile && outputFile)
    {
        m_InputFile = std::move(deleted_unique_ptr(inputFile,
                                                   [](FILE *f)
                                                   { fclose(f); }));

        m_OutputFile = std::move(deleted_unique_ptr(outputFile,
                                                    [](FILE *f)
                                                    { fclose(f); }));
        isFilesOpened = true;

        std::cout << "Files successfully opened! \n";
    }

    else {
        if(!inputFile) {
            std::cerr << "Failed to open file " << m_InputPath << ". You may need to use absolute path\n";
        }
        if(!outputFile) {
            std::cerr << "Failed to open file " << m_OutputPath << ". You may need to use absolute path\n";
        }
    }
    return isFilesOpened;
}
