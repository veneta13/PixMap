#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "../inc/inc.h"
#include "../inc/command.h"

class Executor {

    std::string commandName;
    std::vector<std::string> commandArguments;
    std::string filePath;

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

    public:
    Executor(Command command);
    void newCommand (Command command);
};
#endif 