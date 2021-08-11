#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

#include "inc.h"
#include "fileManager.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"
#include "image.h"
#include "textHandler.h"
#include "binaryHandler.h"

class Handler {

    BaseHandler* currentInstance;

    bool unsavedChanges;
    void getFileType();

protected:

    FileManager* fileManager;

    public:

    Handler();
    virtual ~Handler();

    void open(std::vector<std::string> args);
    void close();
    void create(std::vector<std::string> args);

    void save();
    void saveAs(std::vector<std::string> args);
    void dither();
    void crop(std::vector<std::string> args);
    void resize(std::vector<std::string> args);

};


#endif
