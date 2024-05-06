#include <iostream>

#include "../FileManager.h"

CFileManager::CFileManager(const std::string& inputPath, const std::string& outputPath)
    : m_IsFilesSuccessfullyOpened(false)
{
    // TODO think how to cut file name and add "Out" at the end
    // and add check for absolute path
    //std::string outFilePath = outFilePath + "/" + inputPath.find_last_of("/")
    auto inputFile = fopen(inputPath.c_str(), "rb");
    auto outputFile = fopen(std::string(outputPath + "_out.jpg").c_str(), "wb");

    if (inputFile && outputFile)
    {
        m_InputFile = std::move(deleted_unique_ptr(inputFile,
                                                   [](FILE *f)
                                                   { fclose(f); }));

        m_OutputFile = std::move(deleted_unique_ptr(outputFile,
                                                    [](FILE *f)
                                                    { fclose(f); }));
        m_IsFilesSuccessfullyOpened = true;

        std::cout << "Files successfully opened! \n";
    }

    else {
        m_IsFilesSuccessfullyOpened = false;
        if(!inputFile) {
            perror(std::string("Failed to open file " + inputPath).c_str());
        }
        if(!outputFile) {
            perror(std::string("Failed to open file " + outputPath).c_str());
        }
    }
}

FILE* CFileManager::getInputFile() {
    return m_InputFile.get();
}

FILE* CFileManager::getOutputFile() {
    return m_OutputFile.get();
}
