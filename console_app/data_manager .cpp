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
    for (QJsonObject::const_iterator it=json.constBegin() ;it != json.constEnd() ;it++) {
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
            data.child_.back().value_.push_back((*it).toString().toStdString());
            qDebug()<<"String:"<<(*it).toString();
            qDebug()<<(*it).type();

        }
        else {
            qDebug()<<"Other";
        }
    }
}

int DataManager::ReadFromFile(const std::string &file_path)
{
    return ReadFromFile(file_path, root_);
}

int DataManager::ReadFromArray(const QJsonArray &json_array, Node &data)
{
    for (QJsonArray::const_iterator it_array = json_array.constBegin(); it_array!=json_array.constEnd(); it_array++) {
        Node node_to_fill;
        if ((*it_array).isArray()) {
            std::cout<<"[\t\n";
            QJsonArray array = (*it_array).toArray();
            ReadFromArray(array, data);
            std::cout<<"\t]\n";

        }
        else if ((*it_array).isString()) {
            std::cout<<(*it_array).toString().toStdString()<<"\n";
            node_to_fill.value_.push_back((*it_array).toString().toStdString());
            //qDebug()<<"String:"<<(*it_array).toString();
            //qDebug()<<(*it_array).type();

        }
        else {
            //qDebug()<<"Object";
            std::cout<<"{\t\n";
            ReadFromObject((*it_array).toObject(), data);

            std::cout<<"}\t\n";

        }
        data.child_.push_back(node_to_fill);
         //qDebug()<<"Array it String:"<<(*it_array).toString();
    }
    return 0;
}

int DataManager::ReadFromObject(const QJsonObject &json, Node &data)
{
    uint32_t cpt= 0;
    qDebug()<<"ReadFromObject:";
    if (json.isEmpty()) {
        qDebug()<<"isEmpty";
    }
    for (QJsonObject::const_iterator it= json.constBegin();it != json.constEnd();it++,cpt++) {
        //qDebug()<<"key:"<<json.keys().at(cpt);
        std::cout<<">>"<<QString(json.keys().at(cpt)).toStdString()<<'\t';
        Node node_to_fill;
        node_to_fill.name_=QString(json.keys().at(cpt)).toStdString();

        if ((*it).isArray()) {
            //qDebug()<<"Array";
            std::cout<<"[\t\n";
            QJsonArray array = (*it).toArray();
            ReadFromArray(array, node_to_fill);
            std::cout<<"\t]\n";

        }
        else if ((*it).isString()) {
            //qDebug()<<"String:"<<(*it).toString();
            std::cout<<(*it).toString().toStdString()<<"\n";
            node_to_fill.value_.push_back((*it).toString().toStdString());
            //qDebug()<<(*it).type();

        }
        else {
            //qDebug()<<"Object";
            std::cout<<"{\t\n";
            ReadFromObject((*it).toObject(), node_to_fill);
            std::cout<<"}\t\n";
        }
        data.child_.push_back(node_to_fill);
        std::cout<<"<<\n";
    }
    return 0;
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
    qDebug()<<"start parsing";
    ReadFromObject(json, data);
    /*uint32_t cpt= 0;
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
    }*/

    return 0;
}
