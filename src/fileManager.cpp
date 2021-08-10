#include "../inc/fileManager.h"

static FileManager& FileManager::getInstance(){
    static FileManager instance;
    return instance;
}

int FileManager::openFile(std::vector<std::string> args) {
    currentPath = args.at(0);
//    loadFileIntoMemory();
//    std::cout << "\nSuccessfully opened the file.\n";
    return getFileType();
}

int FileManager::getFileType() {

    //read file to find the magic number
    std::fstream fileStream;
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

    if (type == 49)      { return 1; }
    else if (type == 50) { return 2; }
    else if (type == 51) { return 3; }
    else if (type == 52) { return 4; }
    else if (type == 53) { return 5; }
    else if (type == 54) { return 6; }
    else {
        throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
    }
}

void FileManager::loadText()
{
    int endOfHeader;
    std::vector <std::string> file;

    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::in);
    if (!fileStream.good()) {
        throw std::runtime_error("Error: Could not open file.\n");
    }

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

    //for PBM file only search for 2 numbers in the header
    if (getFileType() == 1) {
        endOfHeader = headerProcessorText(2);
    }
    else {
        endOfHeader = headerProcessorText(3);
    }

    std::stringstream line;
    std::string word;
    int number;

    for (int i = endOfHeader + 1; i < file.size(); i++)
    {
        line << file.at(i);
        while (!line.eof())
        {
            line >> word;

            if (std::stringstream(word) >> number) {
                imageGrid.push_back(number);
                word = "";
            }
        }
        line.clear();
    }
}

void FileManager::loadBinaryPBM()
{
    std::stringstream file;
    int endOfHeader;
    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::in | std::ios::binary);

    if (!fileStream.good()) {
        throw std::runtime_error("Error: Could not open file.\n");
    }

    //read the whole file into the file stringstream
    file << fileStream.rdbuf();

    endOfHeader = headerProcessor(2);
    file.seekg(endOfHeader);
    int pixelCount;

    if ((width * height) % 8 == 0){
        pixelCount = (width * height) / 8;
    }
    else {
        pixelCount = (width * height) / 8 + 1;
    }

    char *pixelGrid = new char[pixelCount];
    file.read(pixelGrid, pixelCount);

    for (int i = 0; i < pixelCount; i++)
    {
        std::int8_t number = pixelGrid[i];
        getBinaryNumbers(imageGrid, number);
    }

    delete[] pixelGrid;
    fileStream.close();
    return;
}

void FileManager::loadBinary()
{
    std::stringstream file;
    int endOfHeader;
    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::in | std::ios::binary);

    if (!fileStream.good()) {
        throw std::runtime_error("Error: Could not open file.\n");
    }

    //read the whole file into the file stringstream
    file << fileStream.rdbuf();

    //find the end of the file header
    endOfHeader = headerProcessor(3);

    //skip the file header
    file.seekg(endOfHeader);

    //calculate pixel count according to file type
    int pixelCount = (type == 5) ? width * height : 3 * width * height;

    char *pixelGrid = new char[pixelCount];

    //read the pixels into pixelGrid
    file.read(pixelGrid, pixelCount);
    for (int i = 0; i < pixelCount; i++)
    {
        unsigned char p = pixelGrid[i];
        imageGrid.push_back((int) p);
    }

    delete[] pixelGrid;
    fileStream.close();
    return;
}

int FileManager::headerProcessorText(int headerNumberCount) {
    //find the header of the file via counting the numbers
    //ASCII files implementation
    int numbersInHeader = 0;
    std::stringstream line;
    std::string word;
    int number;
    for (int i = 0; i < file.size(); i++) {
        line << file.at(i);
        while (!line.eof()) {
            line >> word;
            if (std::stringstream(word) >> number && numbersInHeader == 0) {
                width = number;
                word = "";
                numbersInHeader++;
            } else if (std::stringstream(word) >> number && numbersInHeader == 1) {
                height = number;
                word = "";
                numbersInHeader++;
            } else if (std::stringstream(word) >> number && numbersInHeader == 2) {
                max = number;
                word = "";
                numbersInHeader++;
            }
            if (numbersInHeader == headerNumberCount) {
                return i;
            }
        }
        line.clear();
    }

    throw std::runtime_error("Error: Could not recognise the numbers in the header.");
    return -1;
}

int FileManager::headerProcessorBinary(int headerNumberCount) {
    //find the header of the file via counting the numbers
    // binary files implementation
    int numbersInHeader = 0;
    std::string word;
    int endOfHeader = 0;
    while (file >> word && numbersInHeader < headerNumberCount) {
        bool isNumber = true;
        for (int i = 0; i < word.length(); i++) {
            if (!std::isdigit(word[i])) {
                isNumber = false;
            }
        }
        if (isNumber) {
            if (numbersInHeader == 0) {
                width = std::stoi(word);
            } else if (numbersInHeader == 1) {
                height = std::stoi(word);
                endOfHeader = file.tellg();
            } else {
                max = std::stoi(word);
                endOfHeader = file.tellg();
            }
            numbersInHeader++;
        }
    }
    endOfHeader++;
    return endOfHeader;
}

void FileManager::getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number) {
    if (number / 2 != 0) {
        getBinaryNumbers(allPixels, number / 2);
    }
    allPixels.push_back(number % 2);
}

int FileManager::closeFile() {

    //ask to save unsaved changes
    if (unsavedChanges) {
        return 1;
    }

    //clear file associated values
    currentPath.clear();
    imageGrid.clear();
    unsavedChanges = false;
    std::cout << "\nSuccessfully closed the file.\n";
    return 0;
}

void fileManager::closeFile() {

    //ask to save unsaved changes
    if (unsavedChanges) {
        std::cout << "Would you like to save the changes?\ny - yes\nother - no\n";
        char temp;
        std::cin >> temp;
        if (temp == 'y') {
            saveFile();
        }
    }

    currentPath.clear();
    unsavedChanges = false;
    std::cout << "\nSuccessfully closed the file.\n";
}

void FileManager::saveTextFile(int type)
{
    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::out | std::ios::trunc);

    if (!fileStream.good())
    {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //write header information into the file
    std::string temp;
    temp = "P" + std::to_string(type) + "\n";
    fileStream << temp;
    temp.clear();
    fileStream << (width) << " ";
    fileStream << (height) << "\n";

    //if the file is PBM don't include max value
    if (type != 1) {fileStream << max << "\n";}

    //save pixels into the file
    for (int i = 0; i < height; i++) {

        //if the file is PPM save all 3 colors
        if (type == 3) {
            for (int j = 0; j < width * 3; j += 3) {
                fileStream << imageGrid.at(i * width * 3 + j) << " ";
                fileStream << imageGrid.at(i * width * 3 + j + 1) << " ";
                fileStream << imageGrid.at(i * width * 3 + j + 2) << " ";
            }
        }
        else{
            for (int j = 0; j < (imageGrid.size() / height); j++) {
                fileStream << imageGrid.at(i * width + j) << " ";
            }
        }
        fileStream << "\n";
    }

    fileStream.close();
    unsavedChanges = false;
    std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
}

void FileManager::saveBinaryFile(int type)
{
    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::out | std::ios::trunc);

    if (!fileStream.good()) {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //save header information as ASCII
    std::string temp;
    temp = "P" + std::to_string(type) + " ";
    fileStream << temp;
    temp.clear();

    fileStream << (width) << " ";
    fileStream << (height) << " ";

    //if the file is PBM don't include max
    if (type != 4) { fileStream << max << " ";}
    fileStream.close();

    fileStream.open(currentPath, std::ios::out | std::ios::app | std::ios::binary);

    //save file body as binary
    if (!fileStream.good()) {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //cast values to char and save to file
    for (int i = 0; i < imageGrid.size(); i++) {
        fileStream.write((char *) &(imageGrid[i]), sizeof(char));
    }

    fileStream.close();
    unsavedChanges = false;
    std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
}

void FileManager::newFile(std::vector<std::string> args) {
    //update file path
    currentPath = commandArguments.at(2);
    std::cout << "Choose file type:\n1 - PBM\n2 - PGM\n3 - PPM\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        Pbm* pbm = new Pbm();
        pbm->createFile(currentPath);
        imageGrid = pbm->returnImage();
        std::cout << "\nSuccessfully created a new PBM file.\n";
    }
    else if (choice == 2) {
        createInstances(choice);
        pgm->createFile(currentPath);
        imageGrid = pgm->returnImage();
        std::cout << "\nSuccessfully created a new PGM file.\n";
    }
    else if (choice == 3) {
        createInstances(choice);
        ppm->createFile(currentPath);
        imageGrid = ppm->returnImage();
        std::cout << "\nSuccessfully created a new PPM file.\n";
    }
    else {throw std::runtime_error("Error: Invalid file choice.");}
}

fileStruct FileManager::getFile() {
    fileStruct file;
    file.height = this->height;
    file.width = this->width;
    file.max = this->max;
    file.pixels = this->pixels;
    return file;
}