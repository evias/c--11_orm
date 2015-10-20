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

#ifndef FOR_EACH_HPP
#define	FOR_EACH_HPP

#include <algorithm>
#include <tuple>

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

    /* Copy semantic for_each */
    template <typename _functor_t,
              typename ... _args_t>
    void for_each( std::tuple<_args_t...>& tup, _functor_t&& f)
    {
       for_each_helper(std::forward<_functor_t>(f),
                       typename make_indexes<_args_t...>::type(),
                       std::forward<std::tuple<_args_t...>>(tup) );
    };

    /* Move semantic for_each */
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
     *         static_assert("std::is_arithmetic<_arg_t>::value");
     *         sum_ += arg;
     *     };
     *
     *     int sum_ = 0;
     * };
     *
     * tuple<int,string,double> tu = make_tuple(1, "test", 4.20);
     * for_each(tu, func_sum());
     */
    struct func_store_to_string
    {
        template <typename _arg_t>
        void operator()(_arg_t& arg)
        {
            if (! std::is_class<_arg_t>::value)
                throw std::exception();

            str_ += " " + (std::string) arg;
        }

        static std::string str_;
    };

}
}

#endif	/* FOR_EACH_HPP */
