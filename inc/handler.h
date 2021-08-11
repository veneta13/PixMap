#ifndef HANDLER_
#define HANDLER_

#include "inc.h"
#include "fileManager.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"
#include "image.h"
#include "textHandler.h"
#include "binaryHandler.h"

/**
 * @class Handler
 * @brief Handles commands.
 *
 * Manages the instances of TextHandler and BinaryHandler depending
 * on the program input.
 */
class Handler {

    /**
     * pointer to an object of the derived classes of BaseHandler
     */
    BaseHandler* currentInstance;

protected:

    /**
     * pointer to FileManager
     */
    FileManager* fileManager;

    public:

    Handler();
    ~Handler();

    void open(std::vector<std::string> args);
    void close(bool unsavedChanges);
    void create(std::vector<std::string> args);

    void save();
    void saveAs(std::vector<std::string> args);
    void dither();
    void crop(std::vector<std::string> args);
    void resize(std::vector<std::string> args);

};


#endif
