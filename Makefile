TARGET=c++11_orm

JUNK_DIR=build
SRC_DIR=lib

CXX = g++-4.7
CXX_OPTS = --std=c++0x -Ilib/ -c

CORE = build/main.o

ORM_OBJECTS =

# Makefile rules
clean :
	rm -f ${JUNK_DIR}/*.o
	rm -f ${TARGET}

all : buildLib
	@echo " "
	@echo " - build C++11 ORM example application."
	${CXX} ${CXX_OPTS} main.cpp -o build/main.o
	${CXX} -o ${TARGET} ${CORE} ${ORM_OBJECTS}
	@chmod 764 ${TARGET}

buildLib :
	@echo " "
