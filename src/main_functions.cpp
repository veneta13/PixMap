#include "../inc/main_functions.h"

void printInstruction()
{
    //write the instructions
    std::cout << "To use this program, you must enter the following instructions:\n"
              << " - open <path to pbm/pgm/ppm file >\n"
              << " - new <image width> <image height> <background color #XXXXXX format>\n"
              << " - save\n"
              << " - saveAs <path>\n"
              << " - dither\n"
              << " - crop <leftUpperCorner X> <leftUpperCorner Y> <rightBottomCorner X> <rightBottomCorner Y> \n"
              << " - resize <scaling percentage>\n"
              << " - resize <image width> <image height>\n"
              << " - close\n"
              << " - exit\n";
}

void inputLineHandler (std::string& inputLine)
{
    //count the number of quotes
    int count = 0;

    //mark the start and end of quote character pair
    int start, finish;

    //search for the quote character
    for (int i = 0; i < inputLine.length(); i++)
    {
        if (inputLine[i] == '"') {
            count ++

            //if quote character is found, save position
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
        /*
            Change whitespace character to * so 
            that the file path can be read as a single string
        */
        for (int i = start + 1; i < finish; i++)
        {
            if (inputLine[i] == ' ') {
                inputLine[i] = '*';
            }
        }
        return;
    }
    
    //if the quote character is not in a pair, the path is invalid
    throw std::invalid_argument("Error: File path is invalid. \nHint: Check the number of quotes.");
    return;
}

Command createCommand (){
    std::string inputLine;
    std::string commandName;

    std::string argument;
    std::vector<std::string> args;

    std::getline(std::cin, inputLine); //get input
    inputLineHandler(inputLine); //prepare inputLine
    std::stringstream commandStream(inputLine);
    
    commandStream >> commandName; //get the command name
    Command command (commandName); //if the command name is valid a command is created

    while (commandStream >> argument)
    {
        //save the words until the end of the line as arguments
        args.push_back(argument); 
    }

    if (args.size() != 0) 
    {
        //add arguments to the command
        command.addArguments(args);
    }

    return command; //return the command
}