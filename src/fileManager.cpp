#include "../inc/fileManager.h"

 FileManager::FileManager() {}

 FileManager& FileManager::getInstance(){
    static FileManager instance;
    return instance;
}

///
/// @param args - command arguments
void FileManager::openFile(std::vector<std::string> args) {
    currentPath = args.at(0);
}

void FileManager::getFileType() {

    //read file to find the magic number

    Image& image = Image::getInstance();

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

    if (type == 49)      { image.setType(1); return; }
    else if (type == 50) { image.setType(2); return; }
    else if (type == 51) { image.setType(3); return; }
    else if (type == 52) { image.setType(4); return; }
    else if (type == 53) { image.setType(5); return; }
    else if (type == 54) { image.setType(6); return; }
    else {
        throw std::runtime_error("Error: Unrecognised magic number when opening the file.");
    }
}

void FileManager::load()
{
    //load file depending on the magic number

    Image& image = Image::getInstance();

    int type = image.getType();

    if ((type == 1) || (type == 2) || (type == 3)){
        loadText();
    }
    else if (type == 4) {
        loadBinaryPBM();
    }
    else if (type == 5 || type == 6){
        loadBinary();
    }
    else {
        throw std::runtime_error("Error: Cannot open file.");
    }
}

void FileManager::loadText()
{
    //load text file

    Image& image = Image::getInstance();
    std::vector <int> imageGrid;

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
    int type = image.getType();
    if (type == 1) {
        endOfHeader = headerProcessorText(2, file);
    }
    else {
        endOfHeader = headerProcessorText(3, file);
    }

    std::stringstream lineStream;
    std::string word;
    int number;

    for (int i = endOfHeader + 1; i < file.size(); i++)
    {
        lineStream << file.at(i);
        while (!lineStream.eof())
        {
            lineStream >> word;

            if (std::stringstream(word) >> number) {
                imageGrid.push_back(number);
                word = "";
            }
        }
        lineStream.clear();
    }

    image.setPixels(imageGrid);
    imageGrid.clear();

}

void FileManager::loadBinaryPBM(){

    //load binary PBM file

    Image& image = Image::getInstance();
    std::vector<int> imageGrid;

    std::stringstream file;
    int endOfHeader;
    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::in | std::ios::binary);

    if (!fileStream.good()) {
        throw std::runtime_error("Error: Could not open file.\n");
    }

    //read the whole file into the file stringstream
    file << fileStream.rdbuf();

    endOfHeader = headerProcessorBinary(2, file);
    file.seekg(endOfHeader);
    int pixelCount;

    if ((image.getWidth() * image.getHeight()) % 8 == 0){
        pixelCount = (image.getWidth() * image.getHeight()) / 8;
    }
    else {
        pixelCount = (image.getWidth() * image.getHeight()) / 8 + 1;
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

    image.setPixels(imageGrid);
    imageGrid.clear();

    return;
}

void FileManager::loadBinary()
{

    //load binary non-PBM file

    Image& image = Image::getInstance();
    std::vector<int> imageGrid;

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
    endOfHeader = headerProcessorBinary(3, file);

    //skip the file header
    file.seekg(endOfHeader);

    //calculate pixel count according to file type
    int type = image.getType();
    int pixelCount = (type == 5) ? (image.getWidth() * image.getHeight()) : (3 * image.getWidth() * image.getHeight());

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

    image.setPixels(imageGrid);

    imageGrid.clear();

    return;
}

///
/// @param headerNumberCount - number of the numbers in the header, 2 or 3
/// @param file - the file as a vector of strings
/// @return the position of the last symbol of the header
int FileManager::headerProcessorText(int headerNumberCount, std::vector<std::string>& file) {

    //find the header of the file via counting the numbers
    //ASCII files implementation

    Image& image = Image::getInstance();

    int numbersInHeader = 0;
    std::stringstream line;
    std::string word;
    int number;

    for (int i = 0; i < file.size(); i++)
    {
        line << file.at(i);
        while (!line.eof())
        {
            line >> word;
            if (std::stringstream(word) >> number && numbersInHeader == 0) {
                image.setWidth(number);
                word = "";
                numbersInHeader++;
            } else if (std::stringstream(word) >> number && numbersInHeader == 1) {
                image.setHeight(number);
                word = "";
                numbersInHeader++;
            } else if (std::stringstream(word) >> number && numbersInHeader == 2) {
                image.setMax(number);
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

///
/// @param headerNumberCount - number of the numbers in the header, 2 or 3
/// @param file - the file as a reference to a stringstream
/// @return the position of the last symbol of the header
int FileManager::headerProcessorBinary(int headerNumberCount, std::stringstream& file) {
    //find the header of the file via counting the numbers
    // binary files implementation

    Image& image = Image::getInstance();

    int numbersInHeader = 0;
    std::string word;
    int endOfHeader = 0;
    while (file >> word && numbersInHeader < headerNumberCount)
    {
        bool isNumber = true;
        for (int i = 0; i < word.length(); i++)
        {
            if (!std::isdigit(word[i]))
            {
                isNumber = false;
            }
        }

        if (isNumber) {
            if (numbersInHeader == 0)
            {
                image.setWidth(std::stoi(word));
            }
            else if (numbersInHeader == 1) {
                image.setHeight(std::stoi(word));
                endOfHeader = file.tellg();
            }
            else {
                image.setMax(std::stoi(word));
                endOfHeader = file.tellg();
            }
            numbersInHeader++;
        }
    }
    endOfHeader++;
    return endOfHeader;
}

///
/// @param allPixels - the file as a vector of integers
/// @param number - current number
void FileManager::getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number) {
    if (number / 2 != 0) {
        getBinaryNumbers(allPixels, number / 2);
    }
    allPixels.push_back(number % 2);
}

void FileManager::closeFile() {
    //clear file associated values
    currentPath.clear();
    std::cout << "\nSuccessfully closed the file.\n";
}

void FileManager::saveTextFile()
{
    //save the text image into a file

    Image& image = Image::getInstance();

    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::out | std::ios::trunc);

    if (!fileStream.good())
    {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //write header information into the file
    std::string temp;
    temp = "P" + std::to_string(image.getType()) + "\n";
    fileStream << temp;
    temp.clear();
    fileStream << (image.getWidth()) << " ";
    fileStream << (image.getHeight()) << "\n";

    int type = image.getType();

    //if the file is PBM don't include max value
    if (type != 1) {fileStream << image.getMax() << "\n";}

    //save pixels into the file
    for (int i = 0; i < image.getHeight(); i++)
    {
        //if the file is PPM save all 3 colors
        if (type == 3) {
            for (int j = 0; j < image.getWidth() * 3; j += 3)
            {
                fileStream << image.getPixels().at(i * image.getWidth() * 3 + j) << " ";
                fileStream << image.getPixels().at(i * image.getWidth() * 3 + j + 1) << " ";
                fileStream << image.getPixels().at(i * image.getWidth() * 3 + j + 2) << " ";
            }
        }
        else{
            for (int j = 0; j < (image.getPixels().size() / image.getHeight()); j++) {
                fileStream << image.getPixels().at(i * image.getWidth() + j) << " ";
            }
        }
        fileStream << "\n";
    }

    fileStream.close();
    std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
}

void FileManager::saveBinaryFile()
{

    //save the finary image into a file

    Image& image = Image::getInstance();

    std::fstream fileStream;
    fileStream.open(currentPath, std::ios::out | std::ios::trunc);

    if (!fileStream.good()) {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //save header information as ASCII
    std::string temp;
    temp = "P" + std::to_string(image.getType()) + " ";
    fileStream << temp;
    temp.clear();

    fileStream << (image.getWidth()) << " ";
    fileStream << (image.getHeight()) << " ";

    int type = image.getType();

    //if the file is PBM don't include max
    if (type != 4) { fileStream << image.getMax() << " ";}
    fileStream.close();

    fileStream.open(currentPath, std::ios::out | std::ios::app | std::ios::binary);

    //save file body as binary
    if (!fileStream.good()) {
        throw std::runtime_error
            ("Error: Could not open the file.\nHint: Check if you have loaded the file via open.");
    }

    //cast values to char and save to file
    for (int i = 0; i < image.getPixels().size(); i++) {
        fileStream.write((char *) &(image.getPixels().at(i)), sizeof(char));
    }

    fileStream.close();
    std::cout << "\nSuccessfully saved the changes to " << currentPath << ".\n";
}

///
/// @param args - command arguments
void FileManager::newFile(std::vector<std::string> args) {
    currentPath = args.at(2);
}