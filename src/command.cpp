#include "../inc/command.h"

Command::Command(std::string name) : name(name)
{
    validateName();
}

Command::Command(const Command &c)
{
    this->setName(c.getName());
    this->addArguments(c.getArgs());
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

void Command::setName(std::string name)
{
    this->name = name;
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
    std::string validCommandNames[] = {"EXIT", "CLOSE", "SAVE", "OPEN", "SAVEAS",
                                       "NEW", "DITHER", "CROP", "RESIZE" };
    bool commandNameNotValid = false;

    nameToUpper();

    for (int i = 0; i < 9; i++)
    {
        if (validCommandNames[i] == this->name) {
        return;
        }      
    }

    throw std::invalid_argument ("Error: Command name is invalid. \nHint: Check spelling.");
}

void Command::validateArgs()
{
    if (name == "EXIT"  || name == "CLOSE" || name == "SAVE" || name == "DITHER") {
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

    if (name == "RESIZE") {
        if (args.size() != 1 || args.size() != 2) {
            throw std::invalid_argument("Error: This command requires 1 (%) or 2 (size) arguments.");
        }
        else {
            validateResize();
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

    if (name == "CROP") {
        if (args.size() != 4){
            throw std::invalid_argument("Error: This command requires 4 arguments.");
        }
        else {
            validateCrop();
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

void Command::validateResize()
{
    if (args.size() == 1) {
        for (int i = 0; i < args[0].length(); i++)
        {
            if (!isdigit(args[0][i])){
                throw std::invalid_argument("Error: Resize % must be an integer.");
            }
        }
    }
    else 
    {
        for (int i = 0; i < args[0].length(); i++)
        {
            if (!isdigit(args[0][i])){
                throw std::invalid_argument("Error: New image size must be in integers.");
            }
        }

        for (int i = 0; i < args[1].length(); i++)
        {
            if (!isdigit(args[1][i])){
                throw std::invalid_argument("Error: New image size must be in integers.");
            }
        }
    }
    
}

void Command::validateNew()
{
    for (int i = 0; i < args[0].length(); i++)
    {
        if (!isdigit(args[0][i])){
            throw std::invalid_argument("Error: First argument must be an integer.");
        }
    }

    for (int i = 0; i < args[1].length(); i++)
    {
        if (!isdigit(args[1][i])){
            throw std::invalid_argument("Error: Second argument must be an integer.");
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

void Command::validateCrop()
{
    for (int j = 0; j < 4; i++)
    {
        for (int i = 0; i < args[j].length(); i++)
        {
            if (!isdigit(args[j][i])){
                throw std::invalid_argument("Error: The "<< j << "-th argument must be an integer.");
            }
        }
    }
}