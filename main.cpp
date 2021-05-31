#include "inc/inc.h"
#include "inc/command.h"
#include "inc/main_functions.h"

using std::cin;
using std::cout;

int main()
{
    std::string inputLine;
    std::string commandName;

    std::string argument;
    std::vector<std::string> args;
    bool validCommand = true;

    while (validCommand)
    {
        try {
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


            //DEBUG
            std::cout << command.getName();
            std::cout << command.getArgs().at(0);
            //-----------------------------------------------!
        }
        catch (std::exception &e) {
            cout << e.what();
        }
        
    }
    return 0;
}