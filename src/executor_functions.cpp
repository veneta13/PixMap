#include "../inc/executor_functions.h"

int headerProcessor(int& width, int& height, int& max, std::stringstream& file, int maxNumInH) 
{
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
            }
            else
            {
                max = std::stoi(word);
                endOfHeader = file.tellg();
            }
            numbersInHeader++;
        }
    }
    return endOfHeader;
}
