#include <iostream>
#include <string>

#include "source/FileManager.h"
#include "source/ImageProcessor.h"

int parseCmdArguments(int argc, char** argv, std::string& in, std::string& out) {
    if (argc != 5) {
        std::cerr << "Wrong arguments. Usage: " << argv[0] << " -i <input file to process> -o <output directory\n";
        return EXIT_FAILURE;
    }
    for (auto i = 1; i < argc; i += 2) {
        if ("-i" == std::string{argv[i]}) {
            in = argv[i+1];
        }
        else if("-o" == std::string{argv[i]}) {
            out = argv[i+1];
        }
        else {
            std::cerr << "Invalid argument: " << argv[i] << "!\n";
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int getBlengingIntensity() {
    std::cout << "Enter blending intensity value. \n1 - weak; \n2 - strong.\n";

    std::string str;
    int intensity = 2;
    std::getline(std::cin, str);
    if (!str.empty()) {
        try {
            intensity = std::stoi(str);
        } 
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        } 
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Strong is using by default\n";
    }

    return intensity == 1 ? intensity : 2;
}


int main(int argc, char** argv) {
    
    std::string inputFilePath{}, outputDirPath{};
    if (parseCmdArguments(argc, argv, inputFilePath, outputDirPath) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    CFileManager fileManager(inputFilePath, outputDirPath);
    if (fileManager.isFilesSuccessfullyOpened()) {
        CImageProcessor imageProcessor;
        imageProcessor.runDeinterlaceProcess(fileManager.getInputFile(), 
                                             fileManager.getOutputFile(),
                                             getBlengingIntensity());
    }
    else 
        return EXIT_FAILURE;

    std::cout << "Done. Check result in: " << outputDirPath  << "\n";

    return EXIT_SUCCESS;
}
