#ifndef FILEMANAGER
#define FILEMANAGER

#include "inc.h"
#include "fileStruct.h"

class FileManager {
    FileManager();

    bool unsavedChanges = false;
    std::string currentPath;

    int width;
    int height;
    int max = -1;
    std::vector <std::string> imageGrid;

    void loadText();
    void loadBinaryPBM();
    void loadBinary();
    int headerProcessorText(int headerNumberCount);
    int headerProcessorBinary(int headerNumberCount);
    void getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number);

public:

    static FileManager& getInstance();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;

    fileStruct getFile();
    int getFileType();

    int openFile(std::vector<std::string> args);
    int closeFile();
    void saveTextFile(int type);
    void saveBinaryFile(int type);
    void newFile(std::vector<std::string> args);
};


#endif
