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
    void validateNew();

    public:
        
    Command(std::string name);

    std::string getName() const;

    std::vector<std::string> getArgs() const;

    int getArgCount() const;

    void addArguments(std::vector<std::string> args);
};

#endif


