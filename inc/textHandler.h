#ifndef TEXTHANDLER
#define TEXTHANDLER

#include "baseHandler.h"

class TextHandler : public BaseHandler{

    NetPBM* myFile = nullptr;

    void createInstances(int type);

    FileManager* fileManager;

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