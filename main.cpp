/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on January 15, 2013, 9:57 AM
 */

#include <iostream>

#include "user.hpp"

int main(int argc, char** argv)
{
    table::set_connection_config("host=localhost,dbname=db_evias,user=psqlu,password=opendev");

    std::cout << "Hello, world!" << std::endl;
    std::cout << dbo::user::fields.size() << std::endl;
    std::cout << "Goodbye, world!" << std::endl;

    return 0;
}

