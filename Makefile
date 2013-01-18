TARGET=c++11_orm

JUNK_DIR=build
SRC_DIR=lib

CXX = g++-4.7
CXX_OPTS = --std=c++0x -Ilib/ -I/usr/include
PQXX_OPTS = -L/usr/lib -lpqxx -lpq

CORE = build/main.o
ORM_OBJECTS = build/statement.o build/row.o build/table.o

# Makefile rules
clean :
	rm -f ${JUNK_DIR}/*.o
	rm -f ${TARGET}

all : buildLib
	@echo " "
	@echo " - build C++11 ORM example application."
	${CXX} ${CXX_OPTS} ${LINK_OPTS} -c main.cpp -o build/main.o
	${CXX} ${ORM_OBJECTS} ${CORE} -o ${TARGET} ${PQXX_OPTS}
	@chmod 764 ${TARGET}

buildLib :
	@echo " "
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/for_each.cpp -o build/statement.o
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/row.cpp -o build/row.o
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/table.cpp -o build/table.o
