#ifndef COMMANDR
#define COMMANDR

#include "inc.h"
#include "command.h"

class CommandReader {
    CommandReader();
    std::shared_ptr<Command> createCommand();
    void inputLineHandler(std::string &inputLine);

    public:
    static CommandReader& getInstance();
    CommandReader(CommandReader const&) = delete;
    void operator=(CommandReader const&) = delete;
    std::shared_ptr<Command> newCommand();
};

#endif