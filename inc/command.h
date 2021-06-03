#ifndef COMMANDH
#define COMMANDH

#include "inc.h"

class Command
{
    std::string name;
    std::vector<std::string> args;

    void nameToUpper();
    void validateName();
    void validateArgs();
    void validateOpenSaveAs();
    void validateResize();
    void validateNew();
    void validateCrop();
    void setName(std::string name);

    public:
        
    Command(std::string name);

    Command(const Command &c);

    std::string getName() const;

    std::vector<std::string> getArgs() const;

    int getArgCount() const;

    void addArguments(std::vector<std::string> args);
};

#endif


