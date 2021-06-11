#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "inc.h"
#include "command.h"
#include "netpbm.h"
#include "dithering.h"
#include "executor_functions.h"

class Executor {
    Pbm* pbm = nullptr;
    Pgm* pgm = nullptr;
    Ppm* ppm = nullptr;
    std::string commandName;
    std::vector<std::string> commandArguments;
    std::string currentPath; //path to opened file
    std::fstream fileStream; //file as file stream
    std::vector<int> imageGrid; //grid of the file pixels
    int height = 0;
    int width = 0;
    int max = 0;
    int type = 0; // type of the file (1 to 6)
    bool unsavedChanges = false;

    void execute(); //execute the command
    void exitFile();
    void closeFile();
    void saveFile();
    void openFile();
    void newFile();
    void ditherFile();
    void cropFile();
    void resizeFile();

    void getFileType(); //return integer with the file type (1 to 6)
    void loadFileIntoMemory(); //load from fileStream to imageGrid
    void createInstances(int type); //create objects of PBM, PGM and PPM

    public:

    int code = 1; //if code is 0 exit the program

    Executor(Command command);
    void newCommand (Command command); //change the command
    ~Executor();
};
#endif 