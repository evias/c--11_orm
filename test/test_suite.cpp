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

#include "test_suite.hpp"

#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace evias;
using namespace unit_test;

suite::suite(std::string n)
    : name_(n)
{

}

suite::suite(std::string n, std::initializer_list<suite*> suites)
    : name_(n), suites_(suites)
{
}

suite::suite(std::string n, std::initializer_list<test*> tests)
    : name_(n), tests_(tests)
{
}

bool suite::run()
{
    /* First run all sub-suites. */
    for (auto s : suites_) {

        std::cout << "Running test suite '" << s->getName() << "' ..."
                  << std::endl;

        s->run();

        std::cout << std::endl;
    }

    /* Then run stand-alone tests configured. */
    return run_tests();
}

bool suite::run_tests()
{
    bool failure = false;
    for (auto t : tests_) {
        message_t type;
        std::string res = "Result for '" + t->getName() + "':";

        try {
            if (! (*t)())
                throw test_exception("");

            type = INFO;
            res += " [SUCCESS]";
        }
        catch (test_exception e) {

            type = ERROR;
            res += " [FAILURE]";
            failure = true;
        }

        print(res, type);
    }

    return !failure;
}

void suite::print(std::string msg, message_t type)
{
    std::string prefix;
    switch(type) {
        case INFO:
            prefix = "[INFO]";
            break;
        default:
            prefix = "[ERROR]";
    }

    std::cout << prefix << " " << msg << std::endl;
}

void suite::setName(std::string n)
    throw()
{
    name_ = n;
}

std::string suite::getName()
    throw()
{
    return name_;
}

void suite::addSuite(suite* s)
{
    suites_.push_back(s);
}