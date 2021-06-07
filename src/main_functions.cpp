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

Command createCommand (){
    std::string inputLine;
    std::string commandName;

    std::string argument;
    std::vector<std::string> args;
    bool validCommand = true;

    std::getline(std::cin, inputLine);
        inputLineHandler(inputLine);
        std::stringstream commandStream(inputLine);
                
        commandStream >> commandName;
        Command command (commandName);

        while (commandStream >> argument)
        {
            args.push_back(argument);    
        }

        if (args.size() != 0) {
            command.addArguments(args);
        }
        return command;
}