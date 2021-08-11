#include "../inc/binaryHandler.h"

BinaryHandler::BinaryHandler()
{
    fileManager = &FileManager::getInstance();
}

BinaryHandler::~BinaryHandler() {
    delete myFile;
    myFile = nullptr;
}

///
/// @param args - command arguments
void BinaryHandler::open(std::vector<std::string> args) {
    Image& image = Image::getInstance();
    FileManager* fileManager = &FileManager::getInstance();
    fileManager->getFileType();
    createInstances(image.getType());
    fileManager->load();
}

///
/// @param type - type of binary file; 4 - PBM, 5 - PGM , 6 - PPM
void BinaryHandler::createInstances(int type) {
    //create instances of the image classes
    if (type == 4 )      { myFile = new Pbm(); }
    else if (type == 5 ) { myFile = new Pgm(); }
    else                 { myFile = new Ppm(); }
}

void BinaryHandler::save() {
    FileManager* fileManager = &FileManager::getInstance();
    fileManager->saveBinaryFile();
}

/// @param args - command arguments
void BinaryHandler::saveAs(std::vector <std::string> args)
{
    FileManager* fileManager = &FileManager::getInstance();
    fileManager->openFile(args);
    fileManager->saveBinaryFile();
}

///
/// @param args - command arguments
void BinaryHandler::create(std::vector<std::string> args) {
    //update file path
    fileManager->newFile(args);

    std::cout << "Choose file type:\n1 - PBM\n2 - PGM\n3 - PPM\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        /*
        use a PBM object to create a new file
        and save new file to imageGrid
        */
        createInstances(4);
        myFile->createFile(args[4]);

    }
    else if (choice == 2) {
        /*
        use a PGM object to create a new file
        and save new file to imageGrid
        */
        createInstances(5);
        myFile->createFile(args[4]);
    }
    else if (choice == 3) {
        /*
        use a PPM object to create a new file
        and save new file to imageGrid
        */
        createInstances(6);
        myFile->createFile(args[4]);

    }
    else {throw std::runtime_error("Error: Invalid file choice.");}
}

void BinaryHandler::dither() {
    myFile->ditherImage();
}

///
/// @param args - command arguments
void BinaryHandler::crop(std::vector<std::string> args) {
    //cast arguments to integers
    int temp1 = std::stoi(args.at(0));
    int temp2 = std::stoi(args.at(1));
    int temp3 = std::stoi(args.at(2));
    int temp4 = std::stoi(args.at(3));

    //handle cropping via PBM/PGM/PPM class
    myFile->cropImage(temp1, temp2, temp3, temp4);
}

///
/// @param args - command arguments
void BinaryHandler::resize(std::vector<std::string> args) {
    //if one argument is provided resize by percentage
    if (args.size() == 1) {
        int percentage = std::stoi(args.at(0));
        myFile->resizeImage(percentage);
    }
        //if two arguments are provided resize by sizes
    else {
        int width = std::stoi(args.at(0));
        int height = std::stoi(args.at(1));
        myFile->resizeImage(width, height);
    }
}