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
    // delete picture;
    // picture = nullptr;
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
    // delete picture;
    // picture = nullptr;
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

void Executor::openFile()
{
    loadFileIntoMemory();
}

void Executor::saveAsFile()
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

void Executor::newFile()
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

void Executor::ditherFile()
{
    //picture->ditherImage();
    unsavedChanges = true;
}

void Executor::cropFile()
{
    //picture->cropImage();
    unsavedChanges = true;
}

void Executor::resizeFile()
{
    //picture->resizeImage();
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
        // picture = new Pbm();
        return 1;
    }
    if (type == 50) {
        // picture = new Pgm();
        return 2;
    }
    if (type == 51) {
        // picture = new Ppm();
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