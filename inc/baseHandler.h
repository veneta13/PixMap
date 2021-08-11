#ifndef PROJECT_BASEHANDLER_H
#define PROJECT_BASEHANDLER_H

#include "inc.h"
#include "fileManager.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"
#include "image.h"

class BaseHandler {

public:

    BaseHandler();
    virtual ~BaseHandler();

    virtual void open(std::vector<std::string> args) = 0;
    virtual void save() = 0;
    virtual void saveAs(std::vector<std::string> args) = 0;
    virtual void create(std::vector<std::string> args) = 0;
    virtual void dither() = 0;
    virtual void crop(std::vector<std::string> args) = 0;
    virtual void resize(std::vector<std::string> args) = 0;
};


#endif