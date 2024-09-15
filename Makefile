NAME = ircserv
SRCS = main.cpp checkArgs.cpp utils.cpp openServer.cpp ServerActor.cpp
FLAGS = -std=c++98 -pedantic -Wall -Wextra -Werror
OBJS = ${SRCS:.cpp=.o}

${NAME}: ${OBJS}
	c++ ${FLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all