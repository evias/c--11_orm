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
#include <algorithm>
#include <stdexcept>
#include <pqxx/pqxx>
#include "row.hpp"
#include "query.hpp"
#include "statement.hpp"

namespace evias {
namespace dbo {

    using evias::dbo::select;
    using evias::dbo::from;
    using evias::dbo::where;

    using std::string;
    using std::vector;

    /**
     * Database table class
     **/
    class table
    {
        static string  conn_policy_;

        void _check_connection()
        {
            if (conn_policy_.empty())
                throw std::logic_error("Please initialize the connection policy.");

            if (conn_policy_.find("host") == string::npos
                || conn_policy_.find("dbname") == string::npos
                || conn_policy_.find("user") == string::npos
                || conn_policy_.find("password") == string::npos)
                throw std::logic_error(
                      "Wrong connection policy format: host, dbname, user, password are mandatory");
        }

    protected:
        string table_ = "";
        vector<string>  pkeys_ = {};
        vector<string>  fields_ = {};

    public:
        table() = default;
        virtual ~table() = default;

        /**
         * Table constructor
         *
         * @param std::string name  The database relation name
         * @param std::vector<std::string> fields   The fields names list
         **/
        table(string name, vector<string> fields)
            : table_(name), fields_(fields)
        {
            _check_connection();
        }

        /**
         * Table constructor
         * @param string name  The database relation name
         * @param vector<string> fields The fields names list
         * @param vector<string> pkeys  The primary keys names
         **/
        table(string name,
               vector<string> fields,
               vector<string> pkeys)
            : table_(name),
              fields_(fields),
              pkeys_(pkeys)
        {
            _check_connection();

            vector<string> intersection;
            std::for_each(pkeys.begin(), pkeys.end(), [&intersection,this] (std::string item) {
                for (auto it : this->fields_)
                    if (it == item) {
                        intersection.push_back(it);
                        break;
                    }
            });

            if (intersection.size() != pkeys.size())
                throw std::exception();
        }

        /**
         * Copy constructor
         * @param const table& rhs  The object to be copied
         **/
        table(const table& rhs)
            : table_(rhs.table_),
              fields_(rhs.fields_),
              pkeys_(rhs.pkeys_)
        {
            _check_connection();
        }

        /**
         * Move semantic constructor
         * @param table&& rval  Moved object (r-value)
         **/
        table(table&& rval)
            : table_(std::move(rval.table_)),
              fields_(std::move(rval.fields_)),
              pkeys_(std::move(rval.pkeys_))
        {
            _check_connection();
        }

        void set_connection_config(std::string p)
        {
            conn_policy_ = p;
        }

        pqxx::result select(where _where, group_by _group = {}, order_by _order = {}, limit _limit = {})
        {
            _check_connection();

            /* following line needed because of method name 'select' */
            using select = evias::dbo::select;

            select _select(fields_);
            evias::dbo::from   _from{table_};

            using tuple_t = std::tuple<select,from,where,group_by,order_by,limit>;
            using stmt_t  = statement<select,from,where,group_by,order_by,limit>;

            stmt_t::policy_ = conn_policy_;

            stmt_t my_stmt(tuple_t{
                _select, _from, _where,
                _group, _order, _limit});

            return my_stmt();
        }

        vector<string> get_fields()
        {
            return this->fields_;
        }

        vector<string> get_pkeys()
        {
            return pkeys_;
        }

        string get_table()
        {
            return table_;
        }
    };

}
}

#endif	/* TABLE_HPP */

