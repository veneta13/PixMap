#include "../inc/executor.h"

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
    this->commandName.clear();
    this->commandArguments.clear();

    this->commandName = command.getName();
    for (int i = 0; i < command.getArgCount(); i++)
    {
        this->commandArguments.push_back(command.getArgs().at(i));
    }
    execute();
}

Executor::~Executor ()
{
    delete pbm;
    delete pgm;
    delete ppm;
    pbm = nullptr;
    pgm = nullptr;
    ppm = nullptr;
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
        saveFile();
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
    unsavedChanges = false;
    std::cout << "\nSuccessfully closed the file.\n";
}

void Executor::saveFile()
{
    int fileType = getFileType();
    if (fileType == 1 || fileType == 2 || fileType == 3) {
        fileStream.open(commandArguments.at(0), std::ios::out | std::ios::trunc);
        if (fileStream.good()) {

            std::string temp;
            temp = "P" + std::to_string(fileType) + "\n";
            fileStream >> temp;
            temp.clear();

            fileStream >> height;
            fileStream >> width;
            if (fileType != 1) {
                fileStream >> max;
            }

            for (int i = 0; i < imageGrid.size(); i++) 
            {
                fileStream >> imageGrid.at(i);
            }

            fileStream.close();
            std::cout << "\nSuccessfully saved the changes to " << commandArguments.at(0) << ".\n";
            return;
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }
    }
    else if (fileType == 4 || fileType == 5 || fileType == 6)
    {
        fileStream.open(commandArguments.at(0), std::ios::out | std::ios::trunc);
        if (fileStream.good()) {

            std::string temp;
            temp = "P" + std::to_string(fileType) + "\n";
            fileStream >> temp;
            temp.clear();

            fileStream >> height;
            fileStream >> width;
            if (fileType != 4) {
                fileStream >> max;
            }
            fileStream.close();
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }

        fileStream.open(commandArguments.at(0), std::ios::out | std::ios::app | std::ios::binary);
        if (fileStream.good()){
            for (int i = 0; i < imageGrid.size(); i++) 
            {
                fileStream.write((char*)&(imageGrid[i]), sizeof(imageGrid[i]));
            }
            fileStream.close();
            std::cout << "\nSuccessfully saved the changes to " << commandArguments.at(0) << ".\n";
            return;
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }
    }
    throw std::runtime_error("Error: Unrecognised magic number when saving the file.");
}

void Executor::openFile()
{
    loadFileIntoMemory();
    int type = getFileType();
    createInstances(type);
    std::cout << "\nSuccessfully opened the file.\n";
}

void Executor::newFile()
{
    std::cout << "Choose ";
}

void Executor::ditherFile()
{
    if (getFileType() == 1 || getFileType() == 4){
        pbm->ditherImage();
    }
    else if (getFileType() == 2 || getFileType() == 5){
        pgm->ditherImage();
    }
    else {
        ppm->ditherImage();
    }
    unsavedChanges = true;
}

void Executor::cropFile()
{
    int temp1 = std::stoi(commandArguments.at(0));
    int temp2 = std::stoi(commandArguments.at(1));
    int temp3 = std::stoi(commandArguments.at(2));
    int temp4 = std::stoi(commandArguments.at(3));

    if (getFileType() == 1 || getFileType() == 4){
        pbm->cropImage(temp1, temp2, temp3, temp4);
    }
    else if (getFileType() == 2 || getFileType() == 5){
        pgm->cropImage(temp1, temp2, temp3, temp4);
    }
    else {
        ppm->cropImage(temp1, temp2, temp3, temp4);
    }
    unsavedChanges = true;
}

void Executor::resizeFile()
{
    if (commandArguments.size() == 1) {
        int percentage = std::stoi(commandArguments.at(0));

        if (getFileType() == 1 || getFileType() == 4){
            pbm->resizeImage(percentage);
        }
        else if (getFileType() == 2 || getFileType() == 5){
            pgm->resizeImage(percentage);
        }
        else {
            ppm->resizeImage(percentage);
        }
    }
    else {
        int width = std::stoi(commandArguments.at(0));
        int height = std::stoi(commandArguments.at(1));

        if (getFileType() == 1 || getFileType() == 4){
            pbm->resizeImage( width,  height);
        }
        else if (getFileType() == 2 || getFileType() == 5){
            pgm->resizeImage( width,  height);
        }
        else {
            ppm->resizeImage( width,  height);
        }
    }
    
    unsavedChanges = true;
}

int Executor::getFileType()
{
    std::string fileType;
    fileStream.open(commandArguments.at(0), std::ios::in);
    char c = fileStream.get();
    while (c != 'P')
    {
        c = fileStream.get();
    }
    c = fileStream.get();
    int type = (int)c;

    fileStream.close();
    
    if (type == 49) {
        return 1;
    }
    if (type == 50) {
        return 2;
    }
    if (type == 51) {
        return 3;
    }
    if (type == 52) {
        return 4;
    }
    if (type == 53) {
        return 5;
    }
    if (type == 54) {
        return 6;
    }
    throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
}

void Executor::loadFileIntoMemory()
{
    int fileType = getFileType();
    if(fileType == 1 || fileType == 2 || fileType == 3) {
        int endOfHeader = 0;
        std::vector<std::string> file;

        fileStream.open(commandArguments.at(0), std::ios::in);
        if (fileStream.good()) {
            std::string line;
            while (std::getline(fileStream, line)) 
            {
                file.push_back(line);
            }
            fileStream.close();
            for (int i = 0; i < file.size(); i++) {
                if (file.at(i).find('#') != std::string::npos){
                    int position = file.at(i).find('#');
                    std::string comment = "";
                    comment.append(std::to_string(i));
                    comment.append(file.at(i).substr(position+1));
                    file.at(i) = file.at(i).substr(0, position);
                }
            std::cout << file[i]<< std::endl;
            }
            if (fileType == 1){
                endOfHeader = headerProcessorText(width, height, max, file, 2);
            }
            else{
                endOfHeader = headerProcessorText(width, height, max, file, 3);
            }
            loadImageGrid(endOfHeader, file, imageGrid);
        }
        else {
            throw std::runtime_error("Error: Could not open file.\n");
        }
        return;
    }
    if (fileType == 4 || fileType == 5 || fileType == 6)
    {
        std::stringstream file;
        int endOfHeader = 0;
        fileStream.open(commandArguments.at(0), std::ios::in | std::ios::binary);

        if (fileStream.good()) {
            file << fileStream.rdbuf();

            if (fileType == 4) {
                endOfHeader = headerProcessor(width, height, max, file, 2);
                file.seekg(endOfHeader);
                int pixelCount = ((width * height) % 8 == 0) ? (width*height)/8 : (width*height)/8 + 1;
                char* pixelGrid = new char[pixelCount];
                file.read(pixelGrid, pixelCount);
                std::vector<int> allPixels;
                for ( int i = 0; i < pixelCount; i++ ) 
                {
                    std::int8_t number = pixelGrid[i];
                    getBinaryNumbers(allPixels, number);
                }
                delete[] pixelGrid;
                fileStream.close();
                return;
            }
            else{
                endOfHeader = headerProcessor(width, height, max, file, 3);
                file.seekg(endOfHeader);
                int pixelCount = (fileType == 5) ? width*height : 3*width*height;
                char* pixelGrid = new char[pixelCount];
                file.read(pixelGrid, pixelCount);
                for ( int i = 0; i < pixelCount; i++ ) 
                {
                    unsigned char p = pixelGrid[i];
                    imageGrid.push_back((int) p);
                }
                delete[] pixelGrid;
                fileStream.close();
                return;
            } 
        }
        else {
            throw std::runtime_error("Error: Could not open file.\n");
        }
    }
    throw std::runtime_error("Error: Error loading the file into memory.\n");
}

void Executor::createInstances(int type)
{
    if (type == 1 || type == 4)
    {
        pbm = new Pbm(width, height, imageGrid);
        return;
    }

    if (type == 2 || type == 5)
    {
        pgm = new Pgm(width, height, max, imageGrid);
        return;
    }

    if (type == 3 || type == 6)
    {
        ppm = new Ppm(width, height, max, imageGrid);
        return;
    }
}