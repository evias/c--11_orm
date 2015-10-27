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
#include "test/test.hpp"
#include "test/test_suite.hpp"
#include "test/sql_queries.hpp"

using namespace std;
using namespace evias;

int main(int argc, char** argv)
{
    using unit_test::test_select_query;
    using unit_test::test_update_query;

    auto test_suite = new unit_test::suite("SQL Queries Generation & Parsing", {
        new test_select_query("Basic SQL SELECT Query Generation"),
        new test_update_query("Basic SQL UPDATE Query Generation")
    });

    test_suite->run();
    delete test_suite;

    return 0;
}

