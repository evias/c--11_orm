TARGET=c++11_orm

JUNK_DIR=build
SRC_DIR=lib

CXX = g++-4.7
CXX_OPTS = --std=c++0x -Ilib/ -I/usr/include/pqxx
LINK_OPTS = -L/usr/lib -lpq -lpqxx

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
	${CXX} ${LINK_OPTS} ${ORM_OBJECTS} ${CORE} -o ${TARGET}
	@chmod 764 ${TARGET}

buildLib :
	@echo " "
	${CXX} ${CXX_OPTS} ${LINK_OPTS} -c ${SRC_DIR}/statement.cpp -o build/statement.o
	${CXX} ${CXX_OPTS} ${LINK_OPTS} -c ${SRC_DIR}/row.cpp -o build/row.o
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/table.cpp ${LINK_OPTS} -o build/table.o
