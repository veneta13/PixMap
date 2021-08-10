#ifndef COMMANDH
#define COMMANDH

#include "inc.h"
#include "validator.h"

class Command {
    
    std::string name;
    std::vector <std::string> args;
    Validator* validator = nullptr;

    void setName(std::string name);
    void setArguments(std::vector <std::string> args);
    int argumentCount() const;

    void transformFilePath();

public:
    Command();
    std::string tellName();
    std::string stringify() const;

    friend class CommandReader;
};

#endif


