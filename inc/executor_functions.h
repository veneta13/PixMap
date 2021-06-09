#ifndef __EXECUTOR_FUNCTIONS_H__
#define __EXECUTOR_FUNCTIONS_H__

#include "inc.h"

int headerProcessor(int& width, int& height, int& max, std::stringstream& file, int maxNumInH);
void getBinaryNumbers(std::vector<int> &allPixels, std::int8_t number);
int headerProcessorText(int& width, int& height, int& max, std::vector<std::string>& file, int maxNumInH);
void loadImageGrid( int endOfHeader, std::vector<std::string>& file, std::vector<int>& imageGrid);

#endif