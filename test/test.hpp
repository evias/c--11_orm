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

#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <exception>
#include <functional>
#include <memory>

namespace evias {
namespace unit_test {

    class test_exception
        : public std::exception
    {
        std::string msg_;

    public:
        test_exception(std::string);
        const char* what() const throw();
    };

    class test
    {
    protected:
        std::string name_;

    public:
        test(std::string);

        std::string getName();
        void        setName(std::string);

        /**
         * operator() method is virtual to allow
         * execution from vector<test*>::iterator
         * instance. The "virtuality" makes sure the
         * overloaded version of operator() is called
         **/
        virtual bool operator()();
    };

}
}


#endif  /* TEST_HPP */
