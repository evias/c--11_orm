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

#ifndef SQL_QUERIES_HPP
#define SQL_QUERIES_HPP

#include "test.hpp"
#include <string>

/* Test specific headers */
#include "query.hpp"
#include "statement.hpp"

namespace evias {
namespace unit_test {

/**
 * Features covered:
 *  - Basic SELECT Query Generation
 *  -XXX Basic INSERT Query Generation
 *  -XXX Basic UPDATE Query Generation
 *  -XXX Basic DELETE Query Generation
 **/

/**
 * Class test_select_query
 *
 * Unitary test covers SELECT SQL query
 * generation with several parameters.
 **/
    class test_select_query
        : public test
    {
    protected:
        std::string name_;

    public:
        test_select_query(std::string);
        bool operator()() final override;
    };

/**
 * Class test_update_query
 *
 * Unitary test covers UPDATE SQL query
 * generation with several parameters.
 **/
    class test_update_query
        : public test
    {
    protected:
        std::string name_;

    public:
        test_update_query(std::string);
        bool operator()() final override;
    };
}
}

#endif  /* SQL_QUERIES_HPP */
