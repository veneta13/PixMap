#include "../inc/executor.h"

Executor::Executor (Command command)
{
    this->command = command;
    getCommandIndex();
}

Executor::Executor (const Executor &e)
{
    this->command = e.returnCommand();
    this->commandIndex = e.returnCommandIndex();
}

int Executor::execute() {
    if (commandIndex == 0) {
        closeCurrentFile();
        return 0;
    }
    
    if (commandIndex == 1) {

    }
}

int Executor::returnCommandIndex () const
{
    return commandIndex;
}

Command Executor::returnCommand () const 
{
    return command;
}

void Executor::getCommandIndex()
{
     std::string validCommandNames[] = {"EXIT", "CLOSE", "SAVE", "OPEN", "SAVEAS",
                                       "NEW", "DITHER", "CROP", "RESIZE" };
    for (int i = 0; i < validCommandNames.size(); i++) 
    {
        if (command.getName().compare(validCommandNames[i]) == 0){
            commandIndex = i;
            return;
        }
    }
    
    throw std::runtime_error("Unsuccessful command indexing");
}

void Executor::printSuccessMessage () const
{
    if (commandIndex == 0){
        std::cout << "Exiting the program...\n" << endl;
    }
    else if (commandIndex == 1){
        std::cout << "Successfully closed " << command.getArgs().at(0) << "\n";
    }
    else if (commandIndex == 2){
        std::cout << "Successfully saved" << command.getArgs().at(0) << "\n";
    }
    else if (commandIndex == 3){
        std::cout << "Successfully opened " << command.getArgs.at(0) << "\n";
    }
    else if (commandIndex == 4){
        std::cout << "Successfully saved another " << command.getArgs.at(0) << "\n"; 
    }
    else if (commandIndex == 5){
        std::cout << "Created new document with size " 
                  << command.getArgs[0] << "x" << command.getArgs[1] 
                  << " and filled with " << command.getArgs[2] << "\n"; 
    }
}