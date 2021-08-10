#ifndef FILEMANAGER
#define FILEMANAGER

#include "inc.h"
#include "image.h"

class FileManager {
    FileManager();
    std::string currentPath;

public:
    static FileManager& getInstance();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;

    void loadText();
    void loadBinaryPBM();
    void loadBinary();

    int headerProcessorText(int headerNumberCount);
    int headerProcessorBinary(int headerNumberCount);

    void getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number);

    void getFileType();
    void load();

    void openFile(std::vector<std::string> args);
    void closeFile();
    void saveTextFile();
    void saveBinaryFile();
    void newFile(std::vector<std::string> args);
};


#endif
