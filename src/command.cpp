#include "../inc/command.h"

Command::Command(){
    validator = &Validator::getInstance();
}

///
/// @param name - the name of the command
void Command::setName(std::string name) {
    validator->validateName(name);
    this->name = name;
}

///
/// @param args - the command arguments
void Command::setArguments(std::vector <std::string> args) {
    this->args = args;
    validator->validateArguments(name, args);
    if (name == "OPEN" || name == "SAVEAS") {transformFilePath();}
}

///
/// @return count of the command arguments
int Command::argumentCount() const {
    return args.size();
}

void Command::transformFilePath() {
    //change * to empty space in file path
    int position = args.at(0).find_first_of("*");

    while (position != std::string::npos)
    {
        args[0][position] = ' ';
        position = args[0].find_first_of("*", position + 1);
    }
}

///
/// @return name of the command
std::string Command::tellName()
{
    return name;
}

///
/// @return command arguments
std::vector<std::string> Command::tellArguments()
{
    return args;
}

std::string Command::stringify() const {
    std::string stringCommand = name;

    for (int i = 0; i < args.size(); i++) 
    {
        stringCommand.append(" ");
        stringCommand.append(args[i]);
    }

    return stringCommand;
}



