#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>

using namespace std;

static int filter(const struct dirent* dir_ent)
{
    if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) return 0;
    std::string fname = dir_ent->d_name;

    if (fname.find("main.cpp") == std::string::npos) return 0;

    return 1;
}



int main()
{
    struct dirent **namelist;


    std::vector<std::string> v;
    std::vector<std::string>::iterator  it;

    n = scandir( dir_path , &namelist, *filter, alphasort );

    for (int i=0; i<n; i++) {
        std::string fname = namelist[i]->d_name;

        v.push_back(fname);

        free(namelist[i]);
    }
    free(namelist);

return 0;
}
