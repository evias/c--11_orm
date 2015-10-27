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

#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include "test.hpp"

#include <initializer_list>
#include <string>
#include <vector>

namespace evias {
namespace unit_test {

    enum message_t {
        INFO = 0,
        ERROR
    };

    class suite
    {
        std::vector<test*>   tests_;
        std::vector<suite*>  suites_;

        std::string name_;

    public :

        suite(std::string);
        suite(std::string, std::initializer_list<suite*>);
        suite(std::string, std::initializer_list<test*>);

        bool run();
        void print(std::string, message_t);

        std::string getName() throw();
        void setName(std::string) throw();
        void addSuite(suite*);

    private:
        bool run_tests();
    };

}
}

#endif  /* TEST_SUITE_HPP */

