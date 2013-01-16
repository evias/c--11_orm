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

    table::set_connection_data("localhost", "db_evias", "postgres", "sesamopen");

    /* Uncomment to test the breaking condition:
     * - Primary key "field_4" is not listed in fields.
    table t_errpkeys("table3", {"field_1", "field_2", "field_3"}, {"field_4"});
     */

    table t_nopkey("table_nopkey",
            {"firstname", "lastname", "email"});
    table t_pkeys("table_pkeys",
            {"user_id", "email", "firstname"},
            {"user_id"});

    auto stmt = statement<select,from,where>(std::tuple<select,from,where>{
        select{"firstname", "lastname"},
        from{"user_obj"},
        where{"email LIKE 'bart%'"}
    });

    pqxx::result res = stmt.execute("localhost", "db_evias", "postgres", "sesamopen");

    std::cout << "Result for query: '" << res.query() << "'"
              << std::endl;
    for (auto row : res) {
        std::cout << "My type is: " << typeid(row).name() << std::endl;

        std::cout << row["firstname"] << " " << row["lastname"] << std::endl;
    }

    std::cout << "Hello, world!" << std::endl;

    return 0;
}

