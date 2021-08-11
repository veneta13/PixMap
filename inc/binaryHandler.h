#ifndef BINARYHANDLER_
#define BINARYHANDLER_

#include "baseHandler.h"

/**
 * @Class BinaryHandler
 * @brief Handles binary operations.
 *
 * Derived class of BaseHandler.
 */
class BinaryHandler : public BaseHandler{

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
    BinaryHandler();
    ~BinaryHandler();

    void open(std::vector<std::string> args);
    void save();
    void saveAs(std::vector<std::string> args);
    void create(std::vector<std::string> args);
    void dither();
    void crop(std::vector<std::string> args);
    void resize(std::vector<std::string> args);

};

#endif
