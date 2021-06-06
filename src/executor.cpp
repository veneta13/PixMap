#include "../inc/executor.h"
#include "../inc/executor_functions.h"

Executor::Executor (Command command)
{
    this->commandName = command.getName();
    this->commandArguments = command.getArgs();
    execute();
}

void Executor::newCommand(Command command)
{
    this->commandName = command.getName();
    this->commandArguments = command.getArgs();
    execute();
}

int Executor::execute() {

    if (commandName.compare("EXIT") == 0){
        return 1;
    }
    
    if (commandName.compare("CLOSE") == 0){
        executorClose();
        return -1;
    }

    if (commandName.compare("SAVE") == 0){
        cSave();
        return -1;
    }

    if (commandName.compare("OPEN") == 0){
        cOpen();
        return -1;
    }

    if (commandName.compare("SAVEAS") == 0){ 
        cSaveAs();
        return -1;
    }

    if (commandName.compare("NEW") == 0){
        cNew();
        return -1;
    }

    if (commandName.compare("DITHER") == 0){
        cDither();
        return -1;
    }

    if (commandName.compare("CROP") == 0){
        cCrop();
        return -1;
    }

    if (commandName.compare("RESIZE") == 0){
        cResize();
        return -1;
    }
    throw std::runtime_error("Error: Could not execute the command.");
}

void Executor::cExit()
{

}

void Executor::cClose()
{
    if (unsavedChanges == true){
        std::cout << "Would you like to save changes?\ny - yes\nother - no\n"
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            saveFile();
        }
    }
    unsavedChanges = false;
}

void Executor::cSave()
{

}

void Executor::cOpen()
{
    
}

void Executor::cSaveAs()
{

}

void Executor::cNew()
{
    fileStream (filePath, ios::out)
}

void Executor::cDither()
{
    unsavedChanges = true;
}

void Executor::cCrop()
{
    unsavedChanges = true;
}

void Executor::cResize()
{
    unsavedChanges = true;
}