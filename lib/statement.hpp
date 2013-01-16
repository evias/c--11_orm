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

namespace evias {
namespace dbo {

    /**
     * std::tuple foreach implementation, allows iterating
     * over a tuple with the for_each algorithm. Provided
     * functor must take a template argument. (An example
     * functor would be func_store_to_string which is also
     * implemented below.)
     *
     * Meta programming allows working with easily configured
     * statement<> instances.
     *
     * This implementation can be used for any tuple declared.
     * The index_tuple & make_indexes(_impl) implementations
     * are used by the foreach implementation.
     *
     * In the implementation, you will find that the index_tuple
     * and make_indexes class templates are used to iterate through
     * the tuple content while the for_each implementation basically
     * executes a functor with the current iteration item.
     */
    /* Primary templates */
    template <int ...>
    struct index_tuple
    {};

    template <int at_idx,
              typename _tup_ix_t,
              typename ... _types_t>
    struct make_indexes_impl;

    /* Template specializations */
    template <int at_idx,
              int ... _idx_t,
              typename _type,
              typename ... _types_t>
    struct make_indexes_impl<at_idx, index_tuple<_idx_t...>, _type, _types_t...>
    {
        typedef typename make_indexes_impl<at_idx + 1,
                                           index_tuple<_idx_t..., at_idx>,
                                           _types_t...>::type               type;
    };

    template <int at_idx,
              int ... _idx_t>
    struct make_indexes_impl<at_idx, index_tuple<_idx_t...> >
    {
        typedef index_tuple<_idx_t...> type;
    };

    template <typename ... _types_t>
    struct make_indexes
        : make_indexes_impl<0, index_tuple<>, _types_t...>
    {
    };

    /* for_each implementation */
    template <typename _functor_t,
              typename _last_t>
    void for_each_impl(_functor_t&& f, _last_t&& last)
    {
        f(last);
    };

    template <typename _functor_t,
              typename _first_t,
              typename ... _rest_t>
    void for_each_impl(_functor_t&& f, _first_t&& first, _rest_t&&...rest)
    {
        f(first);
        for_each_impl( std::forward<_functor_t>(f), rest...);
    };

    template <typename _functor_t,
              int ... _idx_t,
              typename ... _args_t>
    void for_each_helper( _functor_t&& f, index_tuple<_idx_t...>, std::tuple<_args_t...>&& tup)
    {
        for_each_impl( std::forward<_functor_t>(f), std::forward<_args_t>(std::get<_idx_t>(tup))...);
    };

    template <typename _functor_t,
              typename ... _args_t>
    void for_each( std::tuple<_args_t...>& tup, _functor_t&& f)
    {
       for_each_helper(std::forward<_functor_t>(f),
                       typename make_indexes<_args_t...>::type(),
                       std::forward<std::tuple<_args_t...>>(tup) );
    };

    template <typename _functor_t,
              typename ... _args_t>
    void for_each( std::tuple<_args_t...>&& tup, _functor_t&& f)
    {
       for_each_helper(std::forward<_functor_t>(f),
                       typename make_indexes<_args_t...>::type(),
                       std::forward<std::tuple<_args_t...>>(tup) );
    };

    /**
     * Functor for storing string value
     *
     * This functor is used by the statement<> template structure
     * to concatenate each registered part's string content.
     *
     * This functor also represents an example functor to be passed
     * to the for_each implementation above. You can used static_assert
     * to make sure the types that are provided correspond to your needs.
     * Such as it is describe in the example below.
     *
     * @example
     * struct func_sum
     * {
     *     template <typename _arg_t>
     *     void operator()(_arg_t& arg)
     *     {
     *         static_assert(std::is_arithmetic<_arg_t>::value == true);
     *         sum_ += arg;
     *     };
     *
     *     int sum_ = 0;
     * };
     */
    struct func_store_to_string
    {
        template <typename _arg_t>
        void operator()(_arg_t& arg)
        {
            str_ += " " + (std::string) arg;
        }

        static std::string str_;
    };

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

        statement<_parts_t...>& operator=(const statement<_parts_t...>& rhs)
        {
            parts_ = rhs.parts_;
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

