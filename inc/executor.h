#include "../inc/inc.h"
#include "../inc/command.h"

class Executor {

    Command command;
    int commandIndex;
    std::string filePath;

    void getCommandIndex();
    void print message () const;
    void closeCurrentFile();

    public:
    Executor(Command command);
    Executor(const Executor &e);
    
    int returnCommandIndex() const;
    Command returnCommand() const;

    void execute();

};