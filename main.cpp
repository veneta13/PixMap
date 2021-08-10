// GitHub repository link for the project:
// https://github.com/veneta13/PixMap

#include "inc/inc.h"
#include "inc/executor.h"

int main() {
    try 
    {
        Executor executor;
        executor.execute();
    }
    catch (std::exception &e) 
    {
        std::cout << e.what();
    }
    return 0;
}