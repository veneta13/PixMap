#ifndef FILEMANAGER_
#define FILEMANAGER_

#include "inc.h"
#include "image.h"

/**
 * @class FileManager
 * @brief handler IO file operations
 *
 * Implements the Singleton design pattern.
 */
class FileManager {
    FileManager();

    /**
     * the path the currently opened file
     */
    std::string currentPath;

public:
    static FileManager& getInstance();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;

    void loadText();
    void loadBinaryPBM();
    void loadBinary();

    int headerProcessorText(int headerNumberCount, std::vector <std::string>& file);
    int headerProcessorBinary(int headerNumberCount, std::stringstream& file);

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
