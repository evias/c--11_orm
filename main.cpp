/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on January 15, 2013, 9:57 AM
 */

#include <iostream>
#include <tuple>
#include <string>
#include "table.hpp"
#include "query.hpp"
#include "statement.hpp"

int main(int argc, char** argv)
{
    using evias::dbo::table;
    using evias::dbo::select;
    using evias::dbo::from;
    using evias::dbo::where;
    using evias::dbo::limit;
    using evias::dbo::statement;

    table::set_connection_data("localhost", "db_evias", "root", "");

    table t_nopkey("table_nopkey",
            {"firstname", "lastname", "email"});
    table t_pkeys("table_pkeys",
            {"user_id", "email", "firstname"},
            {"user_id"});

    /* Uncomment to test the breaking condition:
     * - Primary key "field_4" is not listed in fields.
    table t_errpkeys("table3", {"field_1", "field_2", "field_3"}, {"field_4"});
     */

    std::cout << "Hello, world!" << std::endl;

    return 0;
}

