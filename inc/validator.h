#ifndef VALIDATOR
#define VALIDATOR

#include "inc.h"

class Validator{
    Validator();

    std::vector<std::string> validCommandNames ={"EXIT",   "CLOSE",  "SAVE",
                                                 "OPEN",   "SAVEAS", "NEW",
                                                 "DITHER", "CROP",   "RESIZE"};

    void nameToUpper(std::string& name);
    void validateResize(std::vector <std::string> args); //validate arguments for resize
    void validateNew(std::vector <std::string> args); //validate arguments for new
    void validateCrop(std::vector <std::string> args); //validate arguments for crop

    public:
    static Validator& getInstance();
    Validator(Validator const&) = delete;
    void operator=(Validator const&) = delete;
    void validateName(std::string& name);
    void validateArguments(std::string name, std::vector <std::string> args); //check if arguments are valid
};

#endif 