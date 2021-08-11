#include "../inc/commandReader.h"

CommandReader::CommandReader(){}

///
/// @return the only instance of the CommandReader class
CommandReader& CommandReader::getInstance()
{
    static CommandReader instance;
    return instance;
}

///
/// @return pointer to a command object
std::shared_ptr<Command> CommandReader::newCommand() {
    return createCommand();
}

///
/// @param inputLine - console input
void CommandReader::inputLineHandler(std::string &inputLine) {
    
    //count the number of quotes
    int count = 0;

    //mark the start and end of quote character pair
    int start, finish;

    //search for the quote character
    for (int i = 0; i < inputLine.length(); i++) 
    {
        if (inputLine[i] == '"') {
            count++;
            if (count == 1) {start = i;} 
            else {finish = i;}
        }
    }

    //If there are 2 quotes,change whitespace character to * so 
    //that the file path can be read as a single string
    if (count == 0) {return;}
    else if (count == 2) {
        for (int i = start + 1; i < finish; i++) 
        {
            if (inputLine[i] == ' ') {inputLine[i] = '*';}
        }
    }
    else {
        throw std::invalid_argument("Error: File path is invalid. \nHint: Check the number of quotes.");
    }
}

///
/// @return pointer to a command object
std::shared_ptr<Command> CommandReader::createCommand() {

    std::shared_ptr<Command> command = std::shared_ptr<Command>(new Command);

    std::string inputLine;
    std::string currentConsoleWord;

    std::string argument;
    std::vector <std::string> args;

    //enter in the console
    std::cin.sync();
    std::getline(std::cin, inputLine); 
    inputLineHandler(inputLine);
    std::stringstream commandStream(inputLine);

    commandStream >> currentConsoleWord;
    command->setName(currentConsoleWord);

    //save the words until the end of the line as arguments
    while (commandStream >> currentConsoleWord)
    {
        args.push_back(currentConsoleWord);
    }

    if (args.size() != 0) {
        command->setArguments(args);
    }

    return command; //return the command
}