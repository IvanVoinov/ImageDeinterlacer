#ifndef CFILE_MANAGER_H
#define CFILE_MANAGER_H

#include <string>
#include <memory>
#include <functional>

class CFileManager {
private:
    std::string m_InputPath;
    std::string m_OutputPath;

    using deleted_unique_ptr = std::unique_ptr<FILE, std::function<void(FILE*)>>;
    deleted_unique_ptr m_InputFile;
    deleted_unique_ptr m_OutputFile;

public:
    CFileManager() = delete;
    CFileManager(const std::string& inputPath, const std::string& outputPath);
    ~CFileManager() {};

    FILE* getInputFile();
    FILE* getOutputFile();
    bool isFilesSuccessfullyOpened();
};

#endif // CFILE_MANAGER_H