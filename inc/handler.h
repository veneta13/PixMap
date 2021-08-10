#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

#include "fileManager.h"
#include "netpbm.h"

class Handler {

    Handler* currentInstance;
    FileManager* fileManager;

    void getFileType();

    public:

    Handler();
    virtual ~Handler();

    void open(std::vector<std::string> args);
    void close();
    virtual void create(std::vector<std::string> args);

    virtual void save() = 0;
    virtual void exit() = 0;
    virtual void dither() = 0;
    virtual void crop() = 0;
    virtual void resize() = 0;

};


#endif
