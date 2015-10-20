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
        static std::string  conn_policy_;

        void _check_connection();

    protected :
        std::string table_ = "";
        std::vector<std::string>  pkeys_ = {};
        std::vector<std::string>  fields_ = {};

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

        static void set_connection_config(std::string);

        pqxx::result select(where, group_by = {}, order_by = {}, limit = {});
    };

}
}

#endif	/* TABLE_HPP */

