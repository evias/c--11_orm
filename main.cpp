/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on January 15, 2013, 9:57 AM
 */

#include <iostream>
#include <tuple>
#include <string>
#include <typeinfo>
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

    std::cout << "Hello, world!" << std::endl;

    /* Uncomment to test the breaking condition:
     * - Primary key "field_4" is not listed in fields.
    table t_errpkeys("table3", {"field_1", "field_2", "field_3"}, {"field_4"});
     */

    table::set_connection_config("host=localhost dbname=db_evias user=postgres password=sesamopen");

    table users("user_obj", std::vector<std::string>{
        "id_user",
        "firstname",
        "lastname",
        "email",
        "date_created",
        "date_updated"});

    users.select(where{});

    std::cout << "Goodbye, world!" << std::endl;

    return 0;
}

