CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -MMD
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}

SOURCES = ${wildcard src/*.cpp}
OBJECTS = ${SOURCES:.cpp=.o}
DEPENDS = ${OBJECTS:.o=d}
EXEC = server

.PHONY : CLEAN

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}

main.o : block.o
	${CXX} ${CXXFLAGS} $^ -o $@


block.o : block.cpp
	${CXX} ${CXXFLAGS} -c $^

-include ${DEPENDS}

clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
