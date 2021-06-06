#include "../inc/executor.h"

// ............................................................
//    make Singleton??????????????????????
// ............................................................

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
        cExit();
        return 1;
    }
    
    if (commandName.compare("CLOSE") == 0){
        cClose();
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

// void Executor::printSuccessMessage () const
// {
//     if (commandIndex == 0){
//         std::cout << "Exiting the program...\n" << endl;
//     }
//     else if (commandIndex == 1){
//         std::cout << "Successfully closed " << command.getArgs().at(0) << "\n";
//     }
//     else if (commandIndex == 2){
//         std::cout << "Successfully saved" << command.getArgs().at(0) << "\n";
//     }
//     else if (commandIndex == 3){
//         std::cout << "Successfully opened " << command.getArgs.at(0) << "\n";
//     }
//     else if (commandIndex == 4){
//         std::cout << "Successfully saved another " << command.getArgs.at(0) << "\n"; 
//     }
//     else if (commandIndex == 5){
//         std::cout << "Created new document with size " 
//                   << command.getArgs[0] << "x" << command.getArgs[1] 
//                   << " and filled with " << command.getArgs[2] << "\n"; 
//     }
// }

void Executor::cExit()
{

}

void Executor::cClose()
{
    
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
    
}

void Executor::cDither()
{

}

void Executor::cCrop()
{

}

void Executor::cResize()
{

}