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

#include "test.hpp"

using namespace evias;
using namespace unit_test;

test_exception::test_exception(std::string m)
    : msg_(m)
{
}

const char* test_exception::what()
    const throw()
{
    return msg_.c_str();
}

test::test(std::string n)
        : name_(n)
{
}

void test::setName(std::string n)
{
    name_ = n;
}

std::string test::getName()
{
    return name_;
}

bool test::operator()()
{
    throw test_exception("Please overload operator().");
}
