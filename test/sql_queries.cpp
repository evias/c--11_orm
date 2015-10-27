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

#include "sql_queries.hpp"

#include <iostream>

using namespace evias;
using namespace unit_test;

/**
 * Class test_select_query
 *
 * Features Covered:
 * - SQL SELECT query generation
 **/

test_select_query::test_select_query(std::string n)
    : test(n)
{
}

bool test_select_query::operator()()
{
    using namespace evias::dbo;

    typedef std::tuple<select,from,where> tuple_base_t;
    statement<select,from,where> base_stmt(tuple_base_t
    {
        select{"firstname", "lastname"},
        from{"users_table"},
        where{"email = 'gsaive@evias.be'"}
    });
    std::string result = (std::string) base_stmt;

    if (result != " SELECT firstname, lastname FROM users_table WHERE email = 'gsaive@evias.be'")
        return false;

    return true;
}

/**
 * Class test_update_query
 *
 * Features Covered:
 * - SQL UPDATE query generation
 **/

test_update_query::test_update_query(std::string n)
    : test(n)
{
}

bool test_update_query::operator()()
{
    using namespace evias::dbo;

    typedef std::tuple<update,where> tuple_base_t;
    statement<update,where> base_stmt(tuple_base_t
    {
        update{"users_table", "firstname = 'greg'", "lastname = 'no'"},
        where{"email = 'gsaive@evias.be'"}
    });
    std::string result = (std::string) base_stmt;

    if (result != " UPDATE users_table SET firstname = 'greg', lastname = 'no' WHERE email = 'gsaive@evias.be'")
        return false;

    return true;
}
