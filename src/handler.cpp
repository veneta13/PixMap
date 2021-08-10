#include "../inc/handler.h"

Handler::Handler() {
    currentInstance = this;
    fileManager = &FileManager::getInstance();
}

Handler::~Handler() {
    delete currentInstance;
}

void Handler::open(std::vector<std::string> args) {
    int type = fileManager->openFile();
    if (type < 4) {currentInstance = new TextHandler();}
    else {currentInstance = new BinaryHandler();}

    currentInstance->open(args);
}

void Handler::close()
{
    if (fileManager->closeFile() == -1){
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            currentInstance->save();
            fileManager->closeFile();
        }
    }
    delete currentInstance;
    currentInstance = this;
}

void Handler::create(std::vector<std::string> args)
{
    delete currentInstance;
    currentInstance = this;
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
    currentInstance->create();
}
