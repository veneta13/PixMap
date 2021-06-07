#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "../inc/inc.h"
#include "../inc/command.h"
#include "../inc/netpbm.h"

class Executor {

    std::string commandName;
    std::vector<std::string> commandArguments;
    std::vector<std::string> file;
    NetPBM * picture;

    std::fstream fileStream;
    bool unsavedChanges = false;

    int execute();

    void cExit();
    void cClose();
    void cSave();
    void cOpen();
    void cSaveAs();
    void cNew();
    void cDither();
    void cCrop();
    void cResize();

    int getFileType();
    void loadFileIntoMemory();

    public:
    Executor(Command command);
    void newCommand (Command command);
    
};
#endif 