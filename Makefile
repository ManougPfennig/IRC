NAME = ircserv
SRCS =	main.cpp checkArgs.cpp utils.cpp Client.cpp ServerException.cpp \
		openServer.cpp serverLoop.cpp messageParsing.cpp clientRegistration.cpp
FLAGS = -std=c++98 -pedantic -Wall -Wextra -Werror -g3 #-fsanitize=address
OBJS = ${SRCS:.cpp=.o}

${NAME}: ${OBJS}
	c++ ${FLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all