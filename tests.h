#ifndef TESTS_H
#define TESTS_H

#include "geometry.h"
#include "utility.h"
#include <vector>
#include <string>

void writeTestToFile(const std::string& filename, const std::vector<Circle>& circles, const std::vector<Square>& squares, const std::vector<std::pair<int, int>>& testEdgesID);
void loadTest(const std::string& filename, std::vector<Circle>& circles, std::vector<Square>& squares, std::vector<std::pair<int, int>>& testEdgesID);

#endif
