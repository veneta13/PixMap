#include "../inc/validator.h"

Validator::Validator(){}

Validator& Validator::getInstance()
{
    static Validator instance;
    return instance;
}

void Validator::validateName(std::string name) {
    //change command name to upper case
    nameToUpper(name);

    //check if the name is available
    for (int i = 0; i < validCommandNames.size(); i++) {
        if (validCommandNames[i] == name) {return;}
    }
    
    throw std::invalid_argument("Error: Command name is invalid. \nHint: Check spelling.");
}

void Validator::nameToUpper(std::string& name) {
    // change lowercase letters to uppercase
    for (int i = 0; i < name.length(); i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            name[i] = char(int(name[i]) - ('a' - 'A'));
        }
    }
}

void Validator::validateArguments(std::string name, std::vector <std::string> args) {
    //checks if the argument count is correct for this command

    if (name == "EXIT" || name == "CLOSE" || name == "SAVE" || name == "DITHER") {
        if (args.size() != 0) {throw std::invalid_argument("Error: This command requires no arguments.");
    }
    else if (name == "OPEN" || name == "SAVEAS") {
        if (args.size() != 1) {throw std::invalid_argument("Error: This command requires one argument.");}
    }
    else if (name == "RESIZE")  {
        if (args.size() != 1 && args.size() != 2) {
            throw std::invalid_argument("Error: This command requires 1 (%) or 2 (size) arguments.");} 
        else {validateResize(args);}
    }
    else if (name == "NEW") {
        if (args.size() != 3) {throw std::invalid_argument("Error: This command requires 3 arguments.");} 
        else {validateNew(args);}
    }
    else if (name == "CROP") {
            if (args.size() != 4) {throw std::invalid_argument("Error: This command requires 4 arguments.");} 
            else {validateCrop(args);}
        }
    }
}

void Validator::validateResize(std::vector <std::string> args) {
    if (args.size() == 1) {
        //if only 1 argument is passed, then it is percentage
        //validate that resize percentage is an integer
        for (int i = 0; i < args[0].length(); i++) {
            if (!isdigit(args[0][i])) {
                throw std::invalid_argument("Error: Resize % must be an integer.");
            }
        }
    } 
    else{
        //if two arguments are passed, then they are width and height
        //width and height must be integers
        for (int i = 0; i < args[0].length(); i++) 
        {
            if (!isdigit(args[0][i])) {
                throw std::invalid_argument("Error: New image size must be in integers.");
            }
        }
        for (int i = 0; i < args[1].length(); i++) 
        {
             if (!isdigit(args[1][i])) {
                throw std::invalid_argument("Error: New image size must be in integers.");
            }
        }
    }
}

void Validator::validateNew(std::vector <std::string> args) {
    //validate width
    for (int i = 0; i < args[0].length(); i++) {
        if (!isdigit(args[0][i])) {
            throw std::invalid_argument("Error: Width must be an integer.");
        }
    }
    //valiidate height
    for (int i = 0; i < args[1].length(); i++) {
        if (!isdigit(args[1][i])) {
            throw std::invalid_argument("Error: Height must be an integer.");
        }
    }

    //validate color
    if (args[2][0] != '#' || args[2].length() != 7) {
        throw std::invalid_argument("Error: Third argument must be a color.\nHint: Format: #FFFFFF");
    }

    //validate hex color values
    for (int i = 1; i < 7; i++) 
    {
        if (isdigit(args[2][i]) 
           ||(args[2][i] >= 'A' && args[2][i] <= 'F') 
           ||(args[2][i] >= 'a' && args[2][i] <= 'f')) 
                {continue;} 
        else { throw std::invalid_argument("Error: Third argument must be a color.\nHint: Choose a valid hexadecimal color.");}
    }

}

void Validator::validateCrop(std::vector <std::string> args) {
    //validate crop rectangle dimensions
    for (int j = 0; j < 4; j++) 
    {
        for (int i = 0; i < args[j].length(); i++) 
        {
                if (!isdigit(args[j][i])) {throw std::invalid_argument("Error: The arguments must be integers.");}
            
        }
    }
}