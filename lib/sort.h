#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

template<class Type>
using Vector = std::vector<Type>;
using String = std::string;

static const String TEST_PATH = "cpp.txt";

void qsort_recursive(String & raw);