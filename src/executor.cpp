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

Executor::~Executor ()
{
    delete picture;
    picture = nullptr;
}

void Executor::execute() {

    if (commandName.compare("EXIT") == 0){
        code = 0;
        return;
    }
    
    if (commandName.compare("CLOSE") == 0){
        closeFile();
        return;
    }

    if (commandName.compare("SAVE") == 0){
        saveFile();
        return;
    }

    if (commandName.compare("OPEN") == 0){
        openFile();
        return;
    }

    if (commandName.compare("SAVEAS") == 0){ 
        saveAsFile();
        return;
    }

    if (commandName.compare("NEW") == 0){
        newFile();
        return;
    }

    if (commandName.compare("DITHER") == 0){
        ditherFile();
        return;
    }

    if (commandName.compare("CROP") == 0){
        cropFile();
        return;
    }

    if (commandName.compare("RESIZE") == 0){
        resizeFile();
        return;
    }
    throw std::runtime_error("Error: Could not execute the command.");
}

void Executor::closeFile()
{
    if (unsavedChanges == true){
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            saveFile();
        }
    }
    commandName.clear();
    commandArguments.clear();
    comments.clear();
    imageGrid.clear();
    delete picture;
    picture = nullptr;
    unsavedChanges = false;
}

void Executor::saveFile()
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
    //picture->ditherImage();
    unsavedChanges = true;
}

void Executor::cCrop()
{
    //picture->cropImage();
    unsavedChanges = true;
}

void Executor::cResize()
{
    //picture->resizeImage();
    unsavedChanges = true;
}

int Executor::getFileType()
{
    std::string fileType;
    fileStream.open(commandArguments.at(0), std::ios::in);
    fileStream >> fileType;
    fileStream.close();

    if (fileType.compare("P1") == 0) {
        picture = new Pbm();
        return 1;
    }
    if (fileType.compare("P2") == 0) {
        picture = new Pgm();
        return 2;
    }
    if (fileType.compare("P3") == 0) {
        picture = new Ppm();
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