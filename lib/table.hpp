/*
 * File:   table.hpp
 * Author: greg
 *
 * Created on January 15, 2013, 10:22 AM
 */

#ifndef TABLE_HPP
#define	TABLE_HPP

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <pqxx/pqxx>
#include "row.hpp"
#include "query.hpp"

namespace evias {
namespace dbo {

    using evias::dbo::select;
    using evias::dbo::from;
    using evias::dbo::where;

    /**
     * Database table class
     **/
    class table
    {
    protected :
        std::string table_ = "";
        std::vector<std::string>  pkeys_ = {};
        std::vector<std::string>  fields_ = {};

        static std::string conn_policy_;

    public:
        table() = default;
        table(std::string,std::vector<std::string>);
        table(std::string,
              std::vector<std::string>,
              std::vector<std::string>);

        /* Copy & move semantic */
        table(const table&);
        table(table&&);

        virtual ~table();

        static void set_connection_data(std::string,std::string,std::string,std::string);

    };

}
}

#endif	/* TABLE_HPP */

