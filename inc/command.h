#ifndef COMMAND_
#define COMMAND_

#include "inc.h"
#include "validator.h"

/**
 * @Class Command
 * @brief Keeps command name and arguments.
 */
class Command {
    
    std::string name;
    std::vector <std::string> args;
    Validator* validator = nullptr;

    void setName(std::string name);
    void setArguments(std::vector <std::string> args);

    void transformFilePath();

public:
    Command();
    std::string tellName();
    std::vector<std::string> tellArguments();

    int argumentCount() const;
    std::string stringify() const;

    friend class CommandReader;
};

#endif


