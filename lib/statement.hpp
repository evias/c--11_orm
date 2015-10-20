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

#ifndef STATEMENT_HPP
#define	STATEMENT_HPP

#include <string>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <map>
#include <sstream>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <pqxx/pqxx>
#include "query.hpp"
#include "for_each.hpp"
#include "row.hpp"

namespace evias {
namespace dbo {

    /**
     * Statement build structure
     *
     * This structure can be used to concatenate several
     * statement parts such as select,from,where, etc.
     * You might find it useful to define a tuple typedef
     * for a better readability when initializing the statement.
     * As shown below in the examples, you can use the
     * tuple(initializer_list<>) constructor to build
     * the statement parts tuple.
     *
     * An operator string() method is provided for easy parts_
     * concatenation. Multiple instanciation methods are available
     * such that you can initialize the statement using an instanciated
     * tuple or using the tuple initializer list constructor. Both
     * ways provide an easy to read code.
     *
     * @examples
     * // Creation with tuple initializer_list constructor.
     * typedef std::tuple<select,from,where> tuple_base_t;
     * statement<select,from,where> base_stmt(tuple_base_t
     *   {
     *      select{"firstname", "lastname"},
     *      from{"users_table"},
     *      where{"email = 'gsaive@evias.be'"}
     *  });
     *  std::cout << (std::string) base_stmt << std::endl;
     *
     * typedef std::tuple<select,from,where, limit> tuple_base_limited_t;
     * statement<select,from,where, limit> base_limited_stmt(tuple_base_limited_t
     *   {
     *      select{"firstname", "lastname"},
     *      from{"users_table"},
     *      where{"email = 'gsaive@evias.be'"},
     *      limit{1}
     *  });
     *  std::cout << (std::string) base_limited_stmt << std::endl;
     *
     * // Creation with instanciated tuple.
     * std::tuple<update,from,where,limit> stmt_config{
     *     update{"firstname = 'greg'", "lastname = 'no'"},
     *     from{"users_table"},
     *     where{"email = 'gsaive@evias.be'"},
     *     limit{1}
     * };
     *
     * statement<update,from,where,limit> stmt_by_cp = stmt_config;
     **/
    template <typename ... _parts_t>
    class statement
    {
        std::tuple<_parts_t...> parts_;

    public:
        static std::string      policy_;

        statement(std::tuple<_parts_t...> list)
            : parts_(list)
        {
        }

        statement(const statement<_parts_t...>& rhs)
            : parts_(rhs.parts_)
        {
        }

        statement(statement&& stmt)
            : parts_(std::move(stmt.parts_))
        {
        }

        statement<_parts_t...>& operator=(const statement<_parts_t...>& rhs)
        {
            parts_ = rhs.parts_;
            return *this;
        }

        statement<_parts_t...>& operator=(statement<_parts_t...>&& rhs)
        {
            parts_ = std::move(rhs.parts_);
            return *this;
        }

        statement<_parts_t...>& operator=(std::tuple<_parts_t...> data)
        {
            parts_ = data;
            return *this;
        }

        operator std::string()
        {
            using evias::dbo::for_each;
            using evias::dbo::func_store_to_string;

            func_store_to_string::str_ = "";
            for_each(parts_, func_store_to_string());

            return func_store_to_string::str_;
        }

        pqxx::result operator()()
        {
            if (policy_.empty())
                throw std::logic_error("You have to set a connection policy.");

            time_t              timestamp;
            std::string         trxKey;
            std::stringstream   trxSeed;
            unsigned long       timeSeed;

            time (&timestamp);
            timeSeed= (unsigned long) timestamp;
            trxSeed << "__evias_dbo_statement_transaction_"
                    << timeSeed
                    << "__";
            trxKey  = trxSeed.str();

            pqxx::connection    db(policy_);
            pqxx::result        res;
            pqxx::transaction<> tr(db, trxKey);

            try {
                /* Calls operator std::string() */
                res = tr.exec((std::string) *this);
                tr.commit();
            }
            catch (const std::exception& e) {
                std::cerr << "-- caught an error.. aborting : " << e.what() << std::endl;
            }

            return res;
        };
    };

    template <typename ... _parts_t>
    std::string statement<_parts_t...>::policy_ = "";

}
}

#endif	/* STATEMENT_HPP */

