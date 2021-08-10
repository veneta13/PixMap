#ifndef BINARYEX
#define BINARYEX

#include "inc.h"
#include "fileManager.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"
#include "image.h"
#include "textHandler.h"
#include "binaryHandler.h"

class BinaryHandler {

    NetPBM* myFile = nullptr;

    void createInstances(int type);

    FileManager* fileManager;

public:
    BinaryHandler();
    ~BinaryHandler();

    void open(std::vector<std::string> args);
    void save();
    void create(std::vector<std::string> args);
    void dither();
    void crop(std::vector<std::string> args);
    void resize(std::vector<std::string> args);

};

#endif
