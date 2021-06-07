#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "inc.h"
#include "command.h"
#include "netpbm.h"
#include "dithering.h"

class Executor {
    NetPBM * picture;
    std::string commandName;
    std::vector<std::string> commandArguments;
    std::vector<std::string> comments;
    std::vector<std::vector<int>> imageGrid;

    std::fstream fileStream;
    bool unsavedChanges = false;
    

    int execute();
    void exitFile();
    void closeFile();
    void saveFile();
    void openFile();
    void saveAsFile();
    void newFile();
    void ditherFile();
    void cropFile();
    void resizeFile();

    int getFileType();
    void loadFileIntoMemory();

    public:

    Executor(Command command);
    void newCommand (Command command);
    int code = 1;
    ~Executor();
};
#endif 