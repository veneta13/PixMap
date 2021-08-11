#include "../inc/handler.h"

Handler::Handler() {
    currentInstance = nullptr;
    fileManager = &FileManager::getInstance();
}

Handler::~Handler() {
    delete currentInstance;
}

///
/// @param args - command arguments
void Handler::open(std::vector<std::string> args) {

    //ensuring image is clear
    Image& image = Image::getInstance();
    image.clear();

    fileManager->openFile(args);
    if (image.getType() < 4) {currentInstance = new TextHandler();}
    else {currentInstance = new BinaryHandler();}

    currentInstance->open(args);
}

///
/// @param unsavedChanges - boolean flag for unsaved changes
void Handler::close(bool unsavedChanges)
{
    Image& image = Image::getInstance();

    if (unsavedChanges){
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            currentInstance->save();
            fileManager->closeFile();
        }
    }

    image.clear();
    currentInstance = nullptr;
}

///
/// @param args - command arguments
void Handler::create(std::vector<std::string> args)
{
    currentInstance = nullptr;
    fileManager->newFile(args);

    int choice = -1;
    do{
        std::cout << "Choose file type:\n1 - Text\n2 - Binary\n";
        std::cin.clear();
        std::cin.ignore(10000000, '\n');
        std::cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1){currentInstance = new TextHandler();}
    else {currentInstance = new BinaryHandler();}

    currentInstance->create(args);
}

void Handler::save()
{
    currentInstance->save();
}

///
/// @param args - command arguments
void Handler::saveAs(std::vector <std::string> args)
{
    currentInstance->saveAs(args);
}

void Handler::dither()
{
    currentInstance->dither();
}

///
/// @param args - command arguments
void Handler::crop(std::vector<std::string> args)
{
    currentInstance->crop(args);
}

///
/// @param args - command arguments
void Handler::resize(std::vector<std::string> args)
{
    currentInstance->resize(args);
}