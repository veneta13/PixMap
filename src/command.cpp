#include "../inc/command.h"

Command::Command(std::string name) : name(name)
{
    validateName();
}

std::string Command::getName() const
{
    return name;
}

std::vector<std::string> Command::getArgs() const
{
    return args;
}

int Command::getArgCount() const
{
    return this->args.size();
}

void Command::addArguments(std::vector<std::string> args)
{
    this->args = args;
    validateArgs();
}

void Command::nameToUpper()
{
    for (int i = 0; i < this->name.length(); i++)
    {
        if (this->name[i] >= 'a' && this->name[i] <= 'z'){
            this->name[i] = char( int(this->name[i]) - 32 );
        }
    }
}

void Command::validateName()
{
    std::string validCommandNames[] = {"EXIT", "CLOSE", "SAVE", "OPEN", "SAVEAS" , "NEW" };
    bool commandNameNotValid = false;

    nameToUpper();

    for (int i = 0; i < 6; i++)
    {
        if (validCommandNames[i] == this->name) {
        return;
        }      
    }

    throw std::invalid_argument ("Error: Command name is invalid. \nHint: Check spelling.");
}

void Command::validateArgs()
{
    if (name == "EXIT"  || name == "CLOSE" || name == "SAVE") {
        if (args.size() != 0) {
            throw std::invalid_argument("Error: This command requires no arguments.");
        }
        else {
            return;
        }
    }

    if (name == "OPEN"|| name == "SAVEAS") {
        if (args.size() != 1) {
            throw std::invalid_argument("Error: This command requires 1 argument.");
        }
        else {
            validateOpenSaveAs();
            return;
        }
    }
    
    if (name == "NEW") {
        if (args.size() != 3) {
            throw std::invalid_argument("Error: This command requires 3 arguments.");
        }
        else {
            validateNew();
            return;
        }
    }
}

void Command::validateOpenSaveAs()
{
    int position = args.at(0).find_first_of("*");
    while (position != std::string::npos)
    {
        args[0][position]=' ';
        position=args[0].find_first_of("*",position+1);
    }
}

void Command::validateNew()
{
    for (int i = 0; i < args[0].length(); i++)
    {
        if (!isdigit(args[0][i])){
            throw std::invalid_argument("Error: First argument must be a number.");
        }
    }

    for (int i = 0; i < args[1].length(); i++)
    {
        if (!isdigit(args[1][i])){
            throw std::invalid_argument("Error: Second argument must be a number.");
        }
    }

    if (args[2][0] != '#' || args[2].length() != 7) {
        throw std::invalid_argument("Error: Third argument must be a color.\nHint: Format: #FFFFFF");
    }

    for (int i = 1; i < 7; i++)
    {
        if (isdigit(args[2][i]) || 
            (args[2][i] >= 'A' && args[2][i] <= 'F') ||
            (args[2][i] >= 'a' && args[2][i] <= 'f'))
            {
                continue;
            }
        else{
            throw std::invalid_argument("Error: Third argument must be a color.\nHint: Choose a valid hexadecimal color.");
        }
    }
}
