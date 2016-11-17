#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <string>
#include "types.h"
#include <QJsonObject>

class DataManager {
public:
    DataManager();
    ~DataManager();
int ReadFromFile(const std::string &file_path);

private:
    int ReadFromFile(const std::string &file_path, Node &data);
    int ReadFromObject(const QJsonObject &json, Node &data);
    int ReadFromArray(const QJsonArray &json_array, Node &data);
    Node root_;
};

#endif // _DATA_MANAGER_H_
