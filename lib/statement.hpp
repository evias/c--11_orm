/*
 * File:   query_factory.hpp
 * Author: greg
 *
 * Created on January 16, 2013, 10:23 AM
 */

#ifndef STATEMENT_HPP
#define	STATEMENT_HPP

#include <string>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <map>
#include "query.hpp"
#include "for_each.hpp"

namespace evias {
namespace dbo {

    using evias::dbo::for_each;
    using evias::dbo::func_store_to_string;

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
    struct statement
    {
        std::tuple<_parts_t...> parts_;

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
            func_store_to_string::str_ = "";
            for_each(parts_, func_store_to_string());

            return func_store_to_string::str_;
        }

        /* XXX execute(db_connector) */
    };

}
}

#endif	/* STATEMENT_HPP */

