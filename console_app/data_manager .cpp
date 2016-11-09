#include "data_manager.h"
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

void SwallowData(const QJsonObject &json, Node &data)
{
    for (QJsonObject::const_iterator it=json.begin() ;it != json.end() ;it++) {
        qDebug()<<"key:"<<it.key();
        Node new_child;
        new_child.name_ = it.key().toStdString();
        data.child_.push_back(new_child);
        if ((*it).isArray()) {
            SwallowData((*it).toObject(), data.child_.back());
            qDebug()<<"Array";
            qDebug()<<(*it).type();
        }

        else if ((*it).isString()) {
            data.child_.back().value_ = (*it).toString();
            qDebug()<<"String:"<<(*it).toString();
            qDebug()<<(*it).type();

        }
        else {
            qDebug()<<"Other";
        }

}

int DataManager::ReadFromFile(const std::string &file_path, Node &data)
{
    // Read JSON file
    QFile file(file_path.c_str());
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();

    // Parse document
    QJsonDocument doc(QJsonDocument::fromJson(rawData));

    // Get JSON object
    QJsonObject json = doc.object();
    uint32_t cpt= 0;
    for (QJsonObject::iterator it= json.begin();it != json.end();it++,cpt++) {
        qDebug()<<"key:"<<json.keys().at(cpt);
        if ((*it).isArray()) {
            qDebug()<<"Array";
            qDebug()<<(*it).type();

        }

        else if ((*it).isString()) {
            qDebug()<<"String:"<<(*it).toString();
            qDebug()<<(*it).type();

        }
        else {
            qDebug()<<"Other";
        }
    }

    QJsonArray profile_array=json["profile"].toArray();
    for (QJsonArray::iterator profile_it = profile_array.begin(); profile_it !=profile_array.end(); profile_it++) {
             QJsonObject profile_object = (*profile_it).toObject();
        }

    return 0;
}
