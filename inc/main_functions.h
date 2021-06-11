#ifndef MAINFUNC
#define MAINFUNC

#include "inc.h"
#include "command.h"

void printInstruction(); //print command instructions
void inputLineHandler (std::string& inputLine); //prepare inputLine
Command createCommand (); //create command

#endif