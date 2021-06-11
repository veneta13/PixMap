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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (imageGrid.size()/height); j++)
        {
            std::cout << imageGrid.at(i*width + j) << " ";
        }
        std::cout << "\n";
    }

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
        imageGrid.clear();
        openFile();
        return;
    }

    if (commandName.compare("SAVEAS") == 0){
        currentPath = commandArguments.at(0); 
        saveFile();
        return;
    }

    if (commandName.compare("NEW") == 0){
        imageGrid.clear();
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
    currentPath.clear();
    imageGrid.clear();
    unsavedChanges = false;
    std::cout << "\nSuccessfully closed the file.\n";
}

void Executor::saveFile()
{
    if (type == 1 || type == 2 || type == 3) {
        std::cout << currentPath;
        fileStream.open(currentPath, std::ios::out | std::ios::trunc);
        if (fileStream.good()) {
            std::string temp;
            temp = "P" + std::to_string(type) + "\n";
            fileStream << temp;
            temp.clear();
            fileStream << (width) << " ";
            fileStream << (height) << "\n";
            if (type != 1) {
                fileStream << max << "\n";
            }

            for (int i = 0; i < height; i++)
            {
                if (type == 3){
                for (int j = 0; j < width*3; j+=3)
                    {
                        fileStream << imageGrid.at(i*width*3 + j) << " ";
                        fileStream << imageGrid.at(i*width*3 + j+1) << " ";
                        fileStream << imageGrid.at(i*width*3 + j+2) << " ";
                    }
                }
                else{
                    for (int j = 0; j < (imageGrid.size()/height); j++)
                    {
                        fileStream << imageGrid.at(i*width + j) << " ";
                    }
                }
                fileStream << "\n";
            }
            fileStream.close();
            std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
            return;
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }
    }
    else if (type == 4 || type == 5 || type == 6)
    {
        fileStream.open(currentPath, std::ios::out | std::ios::trunc);
        if (fileStream.good()) {

            std::string temp;
            temp = "P" + std::to_string(type) + " ";
            fileStream << temp;
            temp.clear();

            fileStream << (width) << " ";
            fileStream << (height) << " ";
            if (type != 4) {
                fileStream << max << " ";
            }
            fileStream.close();
        }
        else {
            throw std::runtime_error("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
        }

        fileStream.open(currentPath, std::ios::out | std::ios::app | std::ios::binary);
        if (fileStream.good()){
            for (int i = 0; i < imageGrid.size(); i++) 
            {
                fileStream.write((char*)&(imageGrid[i]), sizeof(char));
            }
            fileStream.close();
            std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
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
    currentPath = commandArguments.at(0);
    getFileType();
    loadFileIntoMemory();
    createInstances(type);
    std::cout << "\nSuccessfully opened the file.\n";
}

void Executor::newFile()
{
    currentPath = commandArguments.at(2);
    std::cout << "Choose file type:\n1 - PBM\n2 - PGM\n3 - PPM\n";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        createInstances(choice);
        pbm->createFile(currentPath);
        std::cout << "\nSuccessfully created a new PBM file.\n";
        return;
    }
    else if ( choice == 2)
    {
        createInstances(choice);
        pgm->createFile(currentPath);
        std::cout << "\nSuccessfully created a new PGM file.\n";
        return;
    }
    else if ( choice == 3)
    {
        createInstances(choice);
        ppm->createFile(currentPath);
        std::cout << "\nSuccessfully created a new PPM file.\n";
        return;
    }
    else throw std::runtime_error("Error: Invalid file choice.");
}

void Executor::ditherFile()
{
    if (type == 1 || type == 4){
        pbm->ditherImage();
    }
    else if (type == 2 || type == 5){
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

    if (type == 1 || type == 4){
        pbm->cropImage(temp1, temp2, temp3, temp4);
    }
    else if (type == 2 || type == 5){
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

        if (type == 1 || type == 4){
            pbm->resizeImage(percentage);
        }
        else if (type == 2 || type == 5){
            pgm->resizeImage(percentage);
        }
        else {
            ppm->resizeImage(percentage);
        }
    }
    else {
        int width = std::stoi(commandArguments.at(0));
        int height = std::stoi(commandArguments.at(1));

        if (type == 1 || type == 4){
            pbm->resizeImage( width,  height);
        }
        else if (type == 2 || type == 5){
            pgm->resizeImage( width,  height);
        }
        else {
            ppm->resizeImage( width,  height);
        }
    }  
    unsavedChanges = true;
}

void Executor::getFileType()
{
    std::string fileType;
    fileStream.open(currentPath, std::ios::in);
    char c = fileStream.get();
    char next = fileStream.peek();
    while (c != 'P' && next != EOF)
    {
        std::cout << c << "\n";
        c = fileStream.get();
    }
    c = fileStream.get();
    int type = (int)c;
    fileStream.close();
    
    if (type == 49) {
        this->type = 1;
        return;
    }
    if (type == 50) {
        this->type = 2;
        return;
    }
    if (type == 51) {
       this->type = 3;
       return;
    }
    if (type == 52) {
        this->type = 4;
        return;
    }
    if (type == 53) {
        this->type = 5;
        return;
    }
    if (type == 54) {
        this->type = 6;
        return;
    }
    throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
}

void Executor::loadFileIntoMemory()
{
    //ASCII files
    if(type == 1 || type == 2 || type == 3) {
        int endOfHeader = 0;
        std::vector<std::string> file;

        fileStream.open(currentPath, std::ios::in);
        if (fileStream.good()) {

            //save lines in the file
            std::string line;
            while (std::getline(fileStream, line)) 
            {
                file.push_back(line);
            }
            fileStream.close();

            //remove comments
            for (int i = 0; i < file.size(); i++) {
                if (file.at(i).find('#') != std::string::npos){
                    int position = file.at(i).find('#');
                    file.at(i) = file.at(i).substr(0, position);
                    if (file.at(i).find_first_not_of(' ') == std::string::npos)
                    {
                        file.erase (file.begin() + i);
                        i--;
                    }
                }
            }

            //find header
            if (type == 1){
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

    //Binary files
    if (type == 4 || type == 5 || type == 6)
    {
        std::stringstream file;
        int endOfHeader = 0;
        fileStream.open(currentPath, std::ios::in | std::ios::binary);

        if (fileStream.good()) {
            file << fileStream.rdbuf();

            if (type == 4) {
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
                int pixelCount = (type == 5) ? width*height : 3*width*height;
                char* pixelGrid = new char[pixelCount];
                file.read(pixelGrid, pixelCount);
                for ( int i = 0; i < pixelCount; i++ ) 
                {
                    unsigned char p = pixelGrid[i];
                    std::cout << (int) p << std::endl;
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
    //create instances of the image classes
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