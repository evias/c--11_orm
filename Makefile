TARGET=c++11_orm

JUNK_DIR=build
SRC_DIR=lib

CXX = g++-4.7
CXX_OPTS = --std=c++0x -Ilib/ -I/usr/include
PQXX_OPTS = -L/usr/lib -lpqxx -lpq

CORE = build/main.o
ORM_OBJECTS = build/user.o

# Makefile rules
clean :
	rm -f ${JUNK_DIR}/*.o
	rm -f ${TARGET}

all : buildLib
	@echo " "
	@echo " - build of C++11-ORM example application."
	${CXX} ${CXX_OPTS} ${LINK_OPTS} -c main.cpp -o build/main.o
	@echo " "
	@echo " - Link ./${TARGET} executable file."
	${CXX} ${ORM_OBJECTS} ${CORE} -o ${TARGET} ${PQXX_OPTS}
	@chmod 764 ${TARGET}

buildLib :
	@echo " "
	@echo " - build of C++11-ORM ${SRC_DIR}/"
	${CXX} ${CXX_OPTS} -c ${SRC_DIR}/user.cpp -o build/user.o
