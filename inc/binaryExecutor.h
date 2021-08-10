#ifndef BINARYEX
#define BINARYEX

class BinaryExecutor : private Executor {

public:

    BinaryExecutor(Command command);
    ~BinaryExecutor();
};

#endif
