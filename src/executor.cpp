#include "../inc/executor.h"

Executor::Executor() 
{
    handler = new Handler();
    commandReader = &CommandReader::getInstance();
}

void Executor::execute()
{
    log();
    std::shared_ptr<Command> command = commandReader->newCommand();
    commandHandler(command);
}

///
/// @param command - pointer to the current command
void Executor::commandHandler(std::shared_ptr<Command> command)
{
    if (command->tellName().compare("EXIT") == 0){
        if (handler != nullptr){
            delete handler;
            handler = nullptr;
        }
        return;
    }
    else if (command->tellName().compare("CLOSE") == 0){
        handler->close(unsavedChanges);
        unsavedChanges = false;
    }
    else if (command->tellName().compare("SAVE") == 0){
        handler->save();
        unsavedChanges = false;
    }
    else if (command->tellName().compare("OPEN") == 0){
        handler->open(command->tellArguments());
        unsavedChanges = true;
    }
    else if (command->tellName().compare("SAVEAS") == 0){
        handler->saveAs(command->tellArguments());
        unsavedChanges = false;
    }
    else if (command->tellName().compare("NEW") == 0){
        handler->create(command->tellArguments());
        unsavedChanges = true;
    }
    else if (command->tellName().compare("DITHER") == 0){
        handler->dither();
        unsavedChanges = true;
    }
    else if (command->tellName().compare("CROP") == 0){
        handler->crop(command->tellArguments());
        unsavedChanges = true;
    }
    else if (command->tellName().compare("RESIZE") == 0){
        handler->resize(command->tellArguments());
        unsavedChanges = true;
    }
    else {
        if (handler != nullptr){
            delete handler;
            handler = nullptr;
        }
        throw std::runtime_error("Error: Could not execute the command.");
    }

    execute();
}

void Executor::log()
{
    std::cout << "To use this program, you must enter the following instructions:\n"
              << " - open <path to pbm/pgm/ppm file >\n"
              << " - new <image width> <image height> <background color #XXXXXX format>\n"
              << " - save\n"
              << " - saveAs <path>\n"
              << " - dither\n"
              << " - crop <leftUpperCorner X> <leftUpperCorner Y> <rightBottomCorner X> <rightBottomCorner Y> \n"
              << " - resize <scaling percentage>\n"
              << " - resize <image width> <image height>\n"
              << " - close\n"
              << " - exit\n";
}