#include "../inc/textHandler.h"

TextHandler::TextHandler(){}

TextHandler::~TextHandler() {
    delete myFile;
    myFile = nullptr;
}

void TextHandler::open(std::vector<std::string> args) {
    FileManager* fileManager = &FileManager::getInstance();
    fileProperties.width = fileManager->getFile().width;
    fileProperties.height = fileManager->getFile().height;
    fileProperties.max = fileManager->getFile().max;
    fileProperties.pixels = fileManager->getFile().pixels;
    createInstances(fileManager->getFileType());
}

NetPBM* TextHandler::createInstances(int type) {
    //create instances of the image classes
    if (type == 1 || type == 4)      { myFile = new Pbm(height, width, imageGrid); }
    else if (type == 2 || type == 5) { myFile = new Pgm(height, width, max, imageGrid); }
    else (type == 3 || type == 6)    { myFile = new Ppm(height, width, max, imageGrid); }
}

void TextHandler::save() {
    FileManager* fileManager = &FileManager::getInstance();
    fileManager->saveTextFile();
}

void TextHandler::create(std::vector<std::string> args) {
    //update file path
    std::cout << "Choose file type:\n1 - PBM\n2 - PGM\n3 - PPM\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        /*
        use a PBM object to create a new file
        and save new file to imageGrid
        */
        createInstances(choice);
        pbm->createFile(currentPath);
        imageGrid = pbm->returnImage();
        std::cout << "\nSuccessfully created a new PBM file.\n";
        return;
    } else if (choice == 2) {
        /*
        use a PGM object to create a new file
        and save new file to imageGrid
        */
        createInstances(choice);
        pgm->createFile(currentPath);
        imageGrid = pgm->returnImage();
        std::cout << "\nSuccessfully created a new PGM file.\n";
        return;
    } else if (choice == 3) {
        /*
        use a PPM object to create a new file
        and save new file to imageGrid
        */
        createInstances(choice);
        ppm->createFile(currentPath);
        imageGrid = ppm->returnImage();
        std::cout << "\nSuccessfully created a new PPM file.\n";
        return;
    } else throw std::runtime_error("Error: Invalid file choice.");
}

void Executor::ditherFile() {
    //handle dithering via Dithering class
    if (type == 1 || type == 4) {
        pbm->ditherImage();
        imageGrid = pbm->returnImage();
    } else if (type == 2 || type == 5) {
        pgm->ditherImage();
        imageGrid = pgm->returnImage();
    } else {
        ppm->ditherImage();
        imageGrid = ppm->returnImage();
    }
    unsavedChanges = true;
}

void Executor::cropFile() {
    //cast arguments to integers
    int temp1 = std::stoi(commandArguments.at(0));
    int temp2 = std::stoi(commandArguments.at(1));
    int temp3 = std::stoi(commandArguments.at(2));
    int temp4 = std::stoi(commandArguments.at(3));

    //handle cropping via PBM/PGM/PPM class
    if (type == 1 || type == 4) {
        pbm->cropImage(temp1, temp2, temp3, temp4);
        imageGrid = pbm->returnImage();
    } else if (type == 2 || type == 5) {
        pgm->cropImage(temp1, temp2, temp3, temp4);
        imageGrid = pgm->returnImage();
    } else {
        ppm->cropImage(temp1, temp2, temp3, temp4);
        imageGrid = ppm->returnImage();
    }
    unsavedChanges = true;
}

void Executor::resizeFile() {
    //if one argument is provided resize by percentage
    if (commandArguments.size() == 1) {
        int percentage = std::stoi(commandArguments.at(0));

        if (type == 1 || type == 4) {
            pbm->resizeImage(percentage);
            imageGrid = pbm->returnImage();
            width = pbm->returnWidth();
            height = pbm->returnHeight();
        } else if (type == 2 || type == 5) {
            pgm->resizeImage(percentage);
            imageGrid = pgm->returnImage();
            width = pgm->returnWidth();
            height = pgm->returnHeight();
        } else {
            ppm->resizeImage(percentage);
            imageGrid = ppm->returnImage();
            width = ppm->returnWidth();
            height = ppm->returnHeight();
        }
    }
        //if two arguments are provided resize by sizes
    else {
        int width = std::stoi(commandArguments.at(0));
        int height = std::stoi(commandArguments.at(1));

        if (type == 1 || type == 4) {
            pbm->resizeImage(width, height);
            imageGrid = pbm->returnImage();
            this->width = pbm->returnWidth();
            this->height = pbm->returnHeight();
        } else if (type == 2 || type == 5) {
            pgm->resizeImage(width, height);
            imageGrid = pgm->returnImage();
            this->width = pgm->returnWidth();
            this->height = pgm->returnHeight();
        } else {
            ppm->resizeImage(width, height);
            imageGrid = ppm->returnImage();
            this->width = ppm->returnWidth();
            this->height = ppm->returnHeight();
        }
    }
    unsavedChanges = true;
}