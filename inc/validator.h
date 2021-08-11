#ifndef VALIDATOR_
#define VALIDATOR_

#include "inc.h"

/**
 * @class Validator
 * @brief Validates commands before they are executed.
 */

class Validator{
    Validator();

    std::vector<std::string> validCommandNames ={"EXIT",   "CLOSE",  "SAVE",
                                                 "OPEN",   "SAVEAS", "NEW",
                                                 "DITHER", "CROP",   "RESIZE"};

    void nameToUpper(std::string& name);
    void validateResize(std::vector <std::string> args);
    void validateNew(std::vector <std::string> args);
    void validateCrop(std::vector <std::string> args);

    public:
    static Validator& getInstance();
    Validator(Validator const&) = delete;
    void operator=(Validator const&) = delete;
    void validateName(std::string& name);
    void validateArguments(std::string name, std::vector <std::string> args);
};

#endif 