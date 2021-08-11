#include "../inc/handler.h"

Handler::Handler() {
    currentInstance = nullptr;
    fileManager = &FileManager::getInstance();
}

Handler::~Handler() {
    delete currentInstance;
}

void Handler::open(std::vector<std::string> args) {

    //ensuring image is clear
    Image& image = Image::getInstance();
    image.clear();
    unsavedChanges = false;

    fileManager->openFile(args);
    if (image.getType() < 4) {currentInstance = new TextHandler();}
    else {currentInstance = new BinaryHandler();}

    currentInstance->open(args);
    std::cout<< typeid(*currentInstance).name();
}

void Handler::close()
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
    unsavedChanges = false;
}

void Handler::create(std::vector<std::string> args)
{
    currentInstance = nullptr;
    fileManager->newFile(args);

    int choice = -1;
    while (choice != 1 || choice != 2){
        std::cout << "Choose file type:\n1 - Text\n2 - Binary\n";
        std::cin.clear();
        std::cin.ignore(10000000, '\n');
        std::cin >> choice;
    }
    if (choice == 1){currentInstance = new TextHandler();}
    else {currentInstance = new BinaryHandler();}
    currentInstance->create(args);
    unsavedChanges = true;
}

void Handler::save()
{
    std::cout<< typeid(*currentInstance).name();
    currentInstance->save();
    unsavedChanges = false;
}

void Handler::saveAs(std::vector <std::string> args)
{
    currentInstance->saveAs(args);
    unsavedChanges = false;
}

void Handler::dither()
{
    currentInstance->dither();
    unsavedChanges = true;
}

void Handler::crop(std::vector<std::string> args)
{
    currentInstance->crop(args);
    unsavedChanges = true;
}

void Handler::resize(std::vector<std::string> args)
{
    currentInstance->resize(args);
    unsavedChanges = true;
}