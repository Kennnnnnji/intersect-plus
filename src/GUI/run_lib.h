#ifndef RUN_LIB_H
#define RUN_LIB_H

#include <string>
#include <vector>

using namespace std;

void split(const string& s, vector<std::string>& sv, const char delim);

class run_lib
{
public:
    run_lib();
    int run3(int argc, char** argv);
};

#endif // RUN_LIB_H
