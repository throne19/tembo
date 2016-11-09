#include <iostream>
#include "data_manager.h"
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello User! This is Tembo" << endl;
    DataManager manager;
    manager.ReadFromFile("../console_app/example_1.json");
    return 0;
}
