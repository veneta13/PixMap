#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "inc.h"
#include "commandReader.h"
#include "handler.h"

class Executor {

    CommandReader* commandReader;
    void log();
    void commandHandler(std::shared_ptr<Command> command);

    public:
    Executor();
    void execute();
};

#endif