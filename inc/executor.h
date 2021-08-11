#ifndef EXECUTOR_
#define EXECUTOR_

#include "inc.h"
#include "commandReader.h"
#include "handler.h"

/**
 * @class Executor
 * @brief Creates commands and executes them.
 *
 * Uses Handler to execute commands.
 * Uses CommandHandler to create commands.
 * Keeps track of possible unsaved changes.
 */
class Executor {

    bool unsavedChanges = false;

    Handler* handler;

    CommandReader* commandReader;

    void log();
    void commandHandler(std::shared_ptr<Command> command);

    public:

    Executor();
    void execute();
};

#endif