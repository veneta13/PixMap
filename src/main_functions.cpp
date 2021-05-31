#include "../inc/main_functions.h"

void inputLineHandler (std::string& inputLine)
{
    int count = 0;
    int start, finish;
    for (int i = 0; i < inputLine.length(); i++)
    {
        if (inputLine[i] == '"') {
            count ++;

            if (count == 1){
                start = i;
            }
            else {
                finish = i;
            }
        }
    }

    if (count == 0) {
        return;
    }
    
    if (count == 2) {
        for (int i = start + 1; i < finish; i++)
        {
            if (inputLine[i] == ' ') {
                inputLine[i] = '*';
            }
        }
        return;
    }
    
    throw std::invalid_argument("Error: File path is invalid. \nHint: Check the number of quotes.");
    return;
}