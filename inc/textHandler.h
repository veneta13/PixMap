#ifndef TEXTHANDLER_
#define TEXTHANDLER_

#include "baseHandler.h"

/**
 * @Class TextHandler
 * @brief Handles test operations.
 *
 * Derived class of BaseHandler.
 */
class TextHandler : public BaseHandler{

    /**
     * Keeps pointer to object of the classes, derived of NetPBM.
     */
    NetPBM* myFile = nullptr;

    /**
     * Keeps pointer to the FileManager object.
     */
    FileManager* fileManager;

    void createInstances(int type);

    public:
    TextHandler();
    ~TextHandler();

    void open(std::vector<std::string> args);
    void save();
    void saveAs(std::vector<std::string> args);
    void create(std::vector<std::string> args);
    void dither();
    void crop(std::vector<std::string> args);
    void resize(std::vector<std::string> args);

};

#endif