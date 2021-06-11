#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "inc.h"
#include "command.h"
#include "netpbm.h"
#include "dithering.h"
#include "executor_functions.h"

class Executor {
    Pbm* pbm = nullptr;
    Pgm* pgm = nullptr;
    Ppm* ppm = nullptr;
    std::string commandName;
    std::vector<std::string> commandArguments;
    std::string currentPath;
    std::fstream fileStream;
    std::vector<int> imageGrid;
    int height = 0;
    int width = 0;
    int max = 0;
    int type = 0;
    bool unsavedChanges = false;

    void execute();
    void exitFile();
    void closeFile();
    void saveFile();
    void openFile();
    void newFile();
    void ditherFile();
    void cropFile();
    void resizeFile();

    void getFileType();
    void loadFileIntoMemory();
    void createInstances(int type);

    public:

    int code = 1;

    Executor(Command command);
    void newCommand (Command command);
    ~Executor();
};
#endif 