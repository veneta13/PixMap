#include "../inc/command.h"

Command::Command(std::string name) : name(name)
{
    //create object via constructor and validate name
    validateName(); 
}

Command::Command(const Command &c) //copy constructor
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
    //return arguments
    return args;
}

int Command::getArgCount() const
{
    //return argument count
    return this->args.size();
}

void Command::printCommand() const
{
    std::cout << name << "\n";
    for (int i = 0; i < this->args.size(); i++)
    {
        std::cout << args[i] << "\n";
    }
}

void Command::addArguments(std::vector<std::string> args)
{   
    //add arguments and validate them
    this->args = args;
    validateArgs();
}

void Command::setName(std::string name)
{
    this->name = name;
}

void Command::nameToUpper()
{ 
    // change lowercase letters to uppercase
    for (int i = 0; i < this->name.length(); i++) 
    {
        if (this->name[i] >= 'a' && this->name[i] <= 'z'){
            this->name[i] = char( int(this->name[i]) - ('a' - 'A'));
        }
    }
}

void Command::validateName()
{   
    //list available command names
    std::string validCommandNames[] = {"EXIT", "CLOSE", "SAVE", "OPEN", "SAVEAS",
                                       "NEW", "DITHER", "CROP", "RESIZE" };
    bool commandNameNotValid = false;

    //change command name to upper case
    nameToUpper(); 

    //check if the name is available
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
    //check if the argument count is correct for this command
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
            //check if the argument is valid
            validateOpenSaveAs(); 
            return;
        }
    }

    if (name == "RESIZE") {
        if (args.size() != 1 && args.size() != 2) {
            throw std::invalid_argument("Error: This command requires 1 (%) or 2 (size) arguments.");
        }
        else {
            //check if the arguments are valid
            validateResize(); 
            return;
        }
    }
    
    if (name == "NEW") {
        if (args.size() != 3) {
            throw std::invalid_argument("Error: This command requires 3 arguments.");
        }
        else {
            //check if the arguments are valid
            validateNew(); 
            return;
        }
    }

    if (name == "CROP") {
        if (args.size() != 4){
            throw std::invalid_argument("Error: This command requires 4 arguments.");
        }
        else {
            //check if the arguments are valid
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
        //change * to empty space in file path
        args[0][position]=' ';
        position=args[0].find_first_of("*",position+1);
    }
}

void Command::validateResize()
{
    if (args.size() == 1) {
        for (int i = 0; i < args[0].length(); i++)
        {   
            //validate resize percentage
            if (!isdigit(args[0][i])){
                throw std::invalid_argument("Error: Resize % must be an integer.");
            }
        }
    }
    else 
    {
        for (int i = 0; i < args[0].length(); i++)
        {   
            //validate new image width
            if (!isdigit(args[0][i])){
                throw std::invalid_argument("Error: New image size must be in integers.");
            }
        }

        for (int i = 0; i < args[1].length(); i++)
        {   
            //validate new image height
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
        //validate new image size
        if (!isdigit(args[0][i])){
            throw std::invalid_argument("Error: First argument must be an integer.");
        }
    }

    for (int i = 0; i < args[1].length(); i++)
    {   
        //validate new image size
        if (!isdigit(args[1][i])){
            throw std::invalid_argument("Error: Second argument must be an integer.");
        }
    }
    
    if (args[2][0] != '#' || args[2].length() != 7) { 
        //validate color
        throw std::invalid_argument("Error: Third argument must be a color.\nHint: Format: #FFFFFF");
    }

    for (int i = 1; i < 7; i++)
    {   
        //validate hex color values
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
    //validate crop rectangle dimensions
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < args[j].length(); i++)
        {
            if (!isdigit(args[j][i])){
                throw std::invalid_argument("Error: The arguments must be integers.");
            }
        }
    }
}