# eVias C++11 ORM

Some of the features may be buggy or their implementation may be incomplete.
This has started as a hobbie development, helping me for a faster development
of applications using C++/C++11.

This project illustrates the easiness of implementing a C++0x & PostgreSQL
object relational mapping pattern. The goal of this project is to provide
an easy to READ and WRITE public API. The Makefile provided with this project
builds into a binary file which you can then execute.

Compilation has been tested with g++-4.9 on a Ubuntu desktop PC.

Any help in compilation instructions for other platforms, or in debugging
execution of the test suite on any other operating system is highly appreciated.

## Requirements

* g++-4.7
* libpqxx-3.1
* libpqxx-dev [for compilation only]

## Use instructions

Compiling and linking the project

    make all

To execute the project binary, you execute the following
command :

    ./c++11_orm

Compiling your own projects with this library will be done simplier
than it is now. In fact, for now the library is not yet header-only
as you need to compile the lib/eviasorm.cpp file to take advantage
of the features.

This part of the Instructions will be updated once the library can
be easily integrated in other projects.

## Contribute

I would appreciate any contributions. This project is open source and
has no limit of extension. Any kind of module or concept may be added
to this small ORM package.

To contribute, you can use github.com's simple fork requests or you
can send me an email with a patch of your commit(s).


