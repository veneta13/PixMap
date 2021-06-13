#include "../inc/executor_functions.h"

int headerProcessor(int& width, int& height, int& max, std::stringstream& file, int maxNumInH) 
{   //find the header of the file via counting the numbers /binary files implementation
    int numbersInHeader = 0;
    std::string word;
    int endOfHeader = 0;
    while (file >> word && numbersInHeader < maxNumInH)
    {
        bool isNumber = true;
        for (int i = 0; i < word.length(); i++)
        {
            if (!std::isdigit(word[i]))
            {
                isNumber = false;
            }
        }
        if (isNumber)
        {
            if (numbersInHeader == 0)
            {
                width = std::stoi(word);
            }
            else if (numbersInHeader == 1)
            {
                height = std::stoi(word);
                endOfHeader = file.tellg();
            }
            else
            {
                max = std::stoi(word);
                endOfHeader = file.tellg();
            }
            numbersInHeader++;
        }
    }
    endOfHeader++;
    return endOfHeader;
}

int headerProcessorText(int& width, int& height, int& max, std::vector<std::string>& file, int maxNumInH)
{   //find the header of the file via counting the numbers / ASCII files implementation
    int numbersInHeader = 0;
    std::stringstream line;
    std::string word;
    int number;
    for (int i = 0; i < file.size(); i++)
    {
        line << file.at(i);
        while (!line.eof()) {
            line >> word;
            if (std::stringstream(word) >> number && numbersInHeader == 0)
            {
                width = number;
                word = "";
                numbersInHeader++;
            }
            else if (std::stringstream(word) >> number && numbersInHeader == 1)
            {
                height = number;
                word = "";
                numbersInHeader++;
            }
            else if (std::stringstream(word) >> number && numbersInHeader == 2)
            {
                max = number;
                word = "";
                numbersInHeader++;
            }
            if (numbersInHeader == maxNumInH){
                return i;
            }
        }
        line.clear();
    }
    throw std::runtime_error("Error: Could not recognise the numbers in the header.");
    return -1;
}

void getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number){
    if (number == 0){
        return;
    }
    if (number > number/2){
       allPixels.push_back(1);
    }
    else {
        allPixels.push_back(0);
    }
    getBinaryNumbers(allPixels, number/2);
    return;
}

void loadImageGrid(int endOfHeader, std::vector<std::string>& file, std::vector<int>& imageGrid)
{
    std::stringstream line;
    std::string word;
    int number;
    for (int i = endOfHeader + 1; i < file.size(); i++)
    {
        line << file.at(i);
        while (!line.eof()) 
        {
            line >> word; 
            if (std::stringstream(word) >> number){
                imageGrid.push_back(number);
                word = "";
            }
        }
        line.clear();
    }
}