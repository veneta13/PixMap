#include "../inc/executor.h"
#include "../inc/executor_functions.h"

Executor::Executor (Command command)
{
    this->commandName = command.getName();
    for (int i = 0; i < command.getArgCount(); i++)
    {
        this->commandArguments.push_back(command.getArgs().at(i));
    }
    execute();
}

void Executor::newCommand(Command command)
{
    this->commandName = command.getName();
    for (int i = 0; i < command.getArgCount(); i++)
    {
        this->commandArguments.push_back(command.getArgs().at(i));
    }
    execute();
}

int Executor::execute() {

    if (commandName.compare("EXIT") == 0){
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

void Executor::cClose()
{
    if (unsavedChanges == true){
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            cSave();
        }
    }
    commandName.clear();
    commandArguments.clear();
    file.clear();
    unsavedChanges = false;
}

void Executor::cSave()
{
    int fileType = getFileType();
    if (fileType == 1 || fileType == 2 || fileType == 3) {
        fileStream.open(commandArguments.at(0), std::ios::out | std::ios::trunc);
        if (fileStream.good()) {
            for (int i = 0; i < commandArguments.size(); i++) 
            {
                fileStream >> commandArguments.at(i);
            }
            fileStream.close();
            return;
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }
    }
    throw std::runtime_error("Error: Unrecognised magic number when saving the file.");

}

void Executor::cOpen()
{
    loadFileIntoMemory();
}

void Executor::cSaveAs()
{
    int fileType = getFileType();
    if (fileType == 1 || fileType == 2 || fileType == 3) {
        fileStream.open(commandArguments.at(0), std::ios::out | std::ios::trunc);
        if (fileStream.good()) {
            for (int i = 0; i < commandArguments.size(); i++) 
            {
                fileStream >> commandArguments.at(i);
            }
            fileStream.close();
            return;
        }
    }
    throw std::runtime_error("Error: Unrecognised magic number when saving the file.");
}

void Executor::cNew()
{
    int pixel;

    pixel = (commandArguments[2] == "#FFFFFF") ? 1 : 0;

    for (int i = 0; i < std::stoi(commandArguments[0]); i++)
    {
        std::string line = "";
        for(int j = 0; j < std::stoi(commandArguments[1]);j++)
        {
            line += std::to_string(pixel);
        }
    } 
    unsavedChanges = true;
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

int Executor::getFileType()
{
    std::string fileType;
    fileStream.open(commandArguments.at(0), std::ios::in);
    fileStream >> fileType;
    fileStream.close();

    if (fileType.compare("P1") == 0) {
        Pbm p;
        picture = &p;
        return 1;
    }
    if (fileType.compare("P2") == 0) {
        Pgm p;
        picture = &p;
        return 2;
    }
    if (fileType.compare("P3") == 0) {
        Ppm p;
        picture = &p;
        return 3;
    }
    // if (fileType.compare("P4") == 0) {
    //     return 4;
    // }
    // if (fileType.compare("P5") == 0) {
    //     return 5;
    // }
    // if (fileType.compare("P6") == 0) {
    //     return 6;
    // }
    throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
}

void Executor::loadFileIntoMemory()
{
    int fileType = getFileType();
    if (fileType == 1 || fileType == 2 || fileType == 3) {
        fileStream.open(commandArguments.at(0), std::ios::in);
        if (fileStream.good()) {
            std::string line;
            while (std::getline(fileStream, line)) {
                file.push_back(line);
            }
            fileStream.close();
            return;
        }
    }
    // if (fileType == 4 || fileType == 5 || fileType == 6) {
    //     fileStream.open(commandArg.at(0), std::ios::in | std::ios::binary);
    //     if (fileStream.good()) {
    //         std::string line;
    //         while (std::getline(fileStream, line)) {
    //             file.push_back(line);
    //         }
    //         fileStream.close();
    //         return;
    //     }
    // }
    throw std::runtime_error("Error: Error loading the file into memory.\n");
}