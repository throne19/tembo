#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <string>
#include "types.h"

class DataManager {
public:
    DataManager();
    ~DataManager();
    int ReadFromFile(const std::string &file_path, Node& data);

private:

};

#endif // _DATA_MANAGER_H_
