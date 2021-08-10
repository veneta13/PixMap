#include "../inc/executor.h"

Executor::Executor() 
{
    commandReader = &CommandReader::getInstance();
}

void Executor::execute()
{
    log();
    std::shared_ptr<Command> command = commandReader->newCommand();
    commandHandler(command);
}

void Executor::commandHandler(std::shared_ptr<Command> command)
{
    Handler handler = new Handler();

    if (command->tellName().compare("EXIT") == 0){
        if (handler != nullptr){
            delete handler;
            handler = nullptr;
        }
        return;
    }
    else if (command->tellName().compare("CLOSE") == 0){
        handler.closeFile();
    }
    else if (command->tellName().compare("SAVE") == 0){
        handler.saveFile();
    }
    else if (command->tellName().compare("OPEN") == 0){
        handler.openFile();
    }
    else if (command->tellName().compare("SAVEAS") == 0){
        handler.saveFile();
    }
    else if (command->tellName().compare("NEW") == 0){
        handler.newFile();
    }
    else if (command->tellName().compare("DITHER") == 0){
        handler.ditherFile();
    }
    else if (command->tellName().compare("CROP") == 0){
        handler.cropFile();
    }
    else if (command->tellName().compare("RESIZE") == 0){
        handler.resizeFile();
    }
    else {
        if (handler != nullptr){
            delete handler;
            handler = nullptr;
        }
        throw std::runtime_error("Error: Could not execute the command.");
    }
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