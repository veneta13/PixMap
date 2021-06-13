/*
    For the Command class, I used the Command behavioral design pattern
    to separate the user input from the execution of the command.
*/
#ifndef COMMANDH
#define COMMANDH

#include "inc.h"

class Command
{
    std::string name;
    std::vector<std::string> args;

    void nameToUpper(); // Convert name to upper case
    void validateName(); //check if name is a valid command
    void validateArgs(); //check if arguments are valid
    void validateOpenSaveAs(); //validate arguments for open and save as
    void validateResize(); //validate arguments for resize
    void validateNew(); //validate arguments for new
    void validateCrop(); //validate arguments for crop
    void setName(std::string name);

    public:
        
    Command(std::string name); //construct

    Command(const Command &c); //copy constructor

    std::string getName() const; //return name

    std::vector<std::string> getArgs() const; //return arguments

    int getArgCount() const; //return number of arguments

    void addArguments(std::vector<std::string> args); //add arguments

    void printCommand() const; //print command
};

#endif


