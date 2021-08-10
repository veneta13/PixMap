//
// Created by user on 07.08.2021 г..
//

#include "../inc/binaryExecutor.h"

BinaryExecutor::BinaryExecutor() {

}

BinaryExecutor::save() {
    else if (type == 4 || type == 5 || type == 6) {
        fileStream.open(currentPath, std::ios::out | std::ios::trunc);
        if (fileStream.good()) {
            //save header information
            std::string temp;
            temp = "P" + std::to_string(type) + " ";
            fileStream << temp;
            temp.clear();

            fileStream << (width) << " ";
            fileStream << (height) << " ";
            if (type != 4) {
                //if the file is PBM don't include max
                fileStream << max << " ";
            }
            fileStream.close();
        } else {
            throw std::runtime_error(
                    "Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }

        fileStream.open(currentPath, std::ios::out | std::ios::app | std::ios::binary);
        if (fileStream.good()) {
            for (int i = 0; i < imageGrid.size(); i++) {
                //cast values to char and save to file
                fileStream.write((char *) &(imageGrid[i]), sizeof(char));
            }
            fileStream.close();
            std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
            return;
        } else {
            throw std::runtime_error(
                    "Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }
    }
}

void Executor::execute() {

    if (commandName.compare("EXIT") == 0){
        return;
    }
    else if (commandName.compare("CLOSE") == 0){
        closeFile();
    }
    else if (commandName.compare("SAVE") == 0){
        saveFile();
    }
    else if (commandName.compare("OPEN") == 0){
        imageGrid.clear();
        openFile();
    }
    else if (commandName.compare("SAVEAS") == 0){
        currentPath = commandArguments.at(0);
        saveFile();
    }
    else if (commandName.compare("NEW") == 0){
        imageGrid.clear();
        newFile();
    }
    else if (commandName.compare("DITHER") == 0){
        ditherFile();
    }
    else if (commandName.compare("CROP") == 0){
        cropFile();
    }
    else if (commandName.compare("RESIZE") == 0){
        resizeFile();
    }
    else {
        throw std::runtime_error("Error: Could not execute the command.");
    }
}


void Executor::closeFile() {

    //ask to save unsaved changes
    if (unsavedChanges) {
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {saveFile();}
    }

    //clear file associated values
    command = nullptr;
    currentPath.clear();
    imageGrid.clear();
    unsavedChanges = false;
    std::cout << "\nSuccessfully closed the file.\n";
}

void Executor::saveFile() {
    //TODO in derived
}

void Executor::openFile() {

    //update file path
    currentPath = commandArguments.at(0);

    getFileType();
    loadFileIntoMemory();
    createInstances(type);

    std::cout << "\nSuccessfully opened the file.\n";
}

void Executor::newFile() {
    //update file path
    currentPath = commandArguments.at(2);
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

void Executor::getFileType() {
    //read file to find the magic number
    fileStream.open(currentPath, std::ios::in);
    char c = fileStream.get();
    char next = fileStream.peek();
    //find the P_ magic number
    while (c != 'P' && next != EOF) {
        c = fileStream.get();
    }
    c = fileStream.get();
    int type = (int) c;
    fileStream.close();

    if (type == 49) { this->type = 1; }
    else if (type == 50) { this->type = 2; }
    else if (type == 51) { this->type = 3; }
    else if (type == 52) { this->type = 4; }
    else if (type == 53) { this->type = 5; }
    else if (type == 54) { this->type = 6; }
    else {
        throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
    }
}

void Executor::loadFileIntoMemory() {
    //ASCII files
    if (type == 1 || type == 2 || type == 3) {
        int endOfHeader;
        std::vector <std::string> file;

        fileStream.open(currentPath, std::ios::in);
        if (fileStream.good()) {

            //save lines in the file
            std::string line;
            while (std::getline(fileStream, line)) {
                file.push_back(line);
            }
            fileStream.close();

            //remove comments
            for (int i = 0; i < file.size(); i++) {
                if (file.at(i).find('#') != std::string::npos) {
                    int position = file.at(i).find('#');
                    file.at(i) = file.at(i).substr(0, position);
                    if (file.at(i).find_first_not_of(' ') == std::string::npos) {
                        //if the line is empty delete
                        file.erase(file.begin() + i);
                        i--;
                    }
                }
            }
            //find header
            if (type == 1) {
                //for PBM file only search for 2 numbers in the header
                endOfHeader = headerProcessorText(width, height, max, file, 2);
            } else {
                endOfHeader = headerProcessorText(width, height, max, file, 3);
            }
            //load file pixels into imageGrid
            loadImageGrid(endOfHeader, file, imageGrid);
        } else {
            throw std::runtime_error("Error: Could not open file.\n");
        }
        return;
    }

    //Binary files
    if (type == 4 || type == 5 || type == 6) {
        std::stringstream file;
        int endOfHeader;
        fileStream.open(currentPath, std::ios::in | std::ios::binary);

        if (fileStream.good()) {
            //read the whole file into the file stringstream
            file << fileStream.rdbuf();

            if (type == 4) {
                //if the file is PBM
                endOfHeader = headerProcessor(width, height, max, file, 2);
                file.seekg(endOfHeader);
                int pixelCount = ((width * height) % 8 == 0) ? (width * height) / 8 : (width * height) / 8 + 1;
                char *pixelGrid = new char[pixelCount];
                file.read(pixelGrid, pixelCount);
                for (int i = 0; i < pixelCount; i++) {
                    std::int8_t number = pixelGrid[i];
                    getBinaryNumbers(imageGrid, number);
                }
                delete[] pixelGrid;
                fileStream.close();
                return;
            } else {
                //find the end of the file header
                endOfHeader = headerProcessor(width, height, max, file, 3);
                //skip the file header
                file.seekg(endOfHeader);
                //calculate pixel count according to file type
                int pixelCount = (type == 5) ? width * height : 3 * width * height;
                char *pixelGrid = new char[pixelCount];
                //read the pixels into pixelGrid
                file.read(pixelGrid, pixelCount);
                for (int i = 0; i < pixelCount; i++) {
                    unsigned char p = pixelGrid[i];
                    //save each pixel as number in imageGrid
                    imageGrid.push_back((int) p);
                }
                delete[] pixelGrid;
                fileStream.close();
                return;
            }
        } else {
            throw std::runtime_error("Error: Could not open file.\n");
        }
    }
    throw std::runtime_error("Error: Error loading the file into memory.\n");
}

void Executor::createInstances(int type) {
    //create instances of the image classes
    if (type == 1 || type == 4) { pbm = new Pbm(height, width, imageGrid); }
    else if (type == 2 || type == 5) { pgm = new Pgm(height, width, max, imageGrid); }
    else (type == 3 || type == 6)
    { ppm = new Ppm(height, width, max, imageGrid); }
}

void Executor::log(int type)
{
    if (type == 1){
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
}