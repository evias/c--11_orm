TARGET=c++11_orm

JUNK_DIR=build
SRC_DIR=lib

CXX = g++
CXX_OPTS = --std=c++0x -Ilib/ -I/usr/include
PQXX_OPTS = -L/usr/lib -lpqxx -lpq

CORE = build/main.o \
	build/test.o \
	build/test_suite.o

ORM_OBJECTS = build/eviasorm.o

TEST_OBJECTS = build/sql_queries.o

# Makefile rules
clean :
	rm -f ${JUNK_DIR}/*.o
	rm -f ${TARGET}

all : buildLib buildTests
	@echo " "
	@echo " - build of C++11-ORM test suite application."
	${CXX} ${CXX_OPTS} ${LINK_OPTS} -c main.cpp -o build/main.o
	@echo " "
	@echo " - Link ./${TARGET} executable file."
	${CXX} ${ORM_OBJECTS} ${TEST_OBJECTS} ${CORE} -o ${TARGET} ${PQXX_OPTS}
	@chmod 764 ${TARGET}

buildLib :
	@echo " "
	@echo " - build of C++11-ORM ${SRC_DIR}/"
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/eviasorm.cpp -o build/eviasorm.o

buildTests :
	@echo " "
	${CXX} ${CXX_OPTS} -c test/test.cpp -o build/test.o
	${CXX} ${CXX_OPTS} -c test/test_suite.cpp -o build/test_suite.o
	${CXX} ${CXX_OPTS} -c test/sql_queries.cpp -o build/sql_queries.o
