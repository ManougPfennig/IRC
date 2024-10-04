NAME = ircserv
SRCS =	main.cpp checkArgs.cpp utils.cpp Client.cpp ServerException.cpp \
		openServer.cpp serverLoop.cpp auth.cpp \
		USER.cpp NICK.cpp PASS.cpp cmdsParse.cpp Channel.cpp \
		PART.cpp JOIN.cpp broadcasts.cpp KICK.cpp MODE.cpp INVITE.cpp \
		cleans.cpp PRIVMSG.cpp
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