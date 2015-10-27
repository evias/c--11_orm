/**
 * LICENSE
 *
 Copyright 2015 Grégory Saive (greg@evias.be)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 *
**/

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

