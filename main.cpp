#include "inc/inc.h"
#include "inc/command.h"
#include "inc/executor.h"
#include "inc/main_functions.h"

using std::cin;
using std::cout;

int main()
{
    printInstruction();
    try {
        Command command = createCommand();
        Executor executor (command);
        while (executor.code != 0)
        {
            command = createCommand();
            executor.newCommand(command);
        }
    }
    catch (std::exception &e) {
        cout << e.what();
    }
    
    return 0;
}