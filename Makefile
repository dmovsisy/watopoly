CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
EXEC = watopoly
SRCS = $(wildcard *.cc)
OBJS = ${SRCS:.cc=.o}
DEPS = ${OBJS:.o=.d}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${EXEC}

-include ${DEPS}

.PHONY: clean

clean:
	rm -f ${OBJS} ${EXEC} ${DEPS}
