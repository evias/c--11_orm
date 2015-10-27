/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on January 15, 2013, 9:57 AM
 */

#include <iostream>

#include "table.hpp"
#include "user.hpp"

using namespace evias::dbo;
using namespace std;

int main(int argc, char** argv)
{
    table::set_connection_config("host=localhost,dbname=db_evias,user=psqlu,password=opendev");

    user *u = new user();

    cout << "Hello, world!" << endl;

    vector<string> fields = u->get_fields();
    for_each(fields.begin(), fields.end(), [] (string item) {
        cout << item << endl;
    });

    cout << "Goodbye, world!" << endl;

    delete u;
    return 0;
}

