#include <iostream>
#include <fstream>

// #include "third_party/lib_jpeg/jpeglib.h"
#include "source/FileManager.h"
// #include "source/ImageProcessor.h"

int main(int argc, char** argv) {
    
    std::string inputFilePath{}, outputDirPath{};
    if(argc != 5) {
        std::cout << "Wrong arguments. Usage: " << argv[0] << " -i <input file to process> -o <output directory>" << std::endl;
        return EXIT_FAILURE;
    }

    for (auto i = 1; i < argc; i += 2) {
        if ("-i" == std::string{argv[i]}) {
            inputFilePath = argv[i+1];
        }
        else if("-o" == std::string{argv[i]}) {
            outputDirPath = argv[i+1];
        }
        else {
            std::cerr << "Invalid argument: " << argv[i] << "!\n";
            return EXIT_FAILURE;
        }
    }

    CFileManager fileManager(inputFilePath, outputDirPath);
    if (fileManager.isFilesSuccessfullyOpened()) {
        auto prt = fileManager.getInputFile();
        std::cout << "main -> ptr get" << std::endl;

        char line[256];
        while (fgets(line, sizeof(line), prt)) {
            fputs(line, stdout);
        }
    }
    else 
        return EXIT_FAILURE;

    std::cout << "Hello, from picture_deinterlacer!\n";

    return EXIT_SUCCESS;
}
