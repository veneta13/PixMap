#ifndef TEXTHANDLER
#define TEXTHANDLER

#include "handler.h"

class TextHandler : private Handler {
    NetPBM* myFile = nullptr;
    fileStruct fileProperties;

    NetPBM* createInstances(int type);

    public:
    TextHandler();
    ~TextHandler();

    void open();
};

#endif