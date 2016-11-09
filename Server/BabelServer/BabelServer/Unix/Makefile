##
## Makefile for Makefile in /home/montav_c/rendu/cpp_babel/Server/BabelServer/BabelServer/Unix
## 
## Made by Cedric MONTAVON
## Login   <montav_c@epitech.eu>
## 
## Started on  Sat Nov  5 16:52:52 2016 Cedric MONTAVON
## Last update Wed Nov  9 13:33:05 2016 Cedric MONTAVON
##

SRC			= ../Common/main.cpp \
			../Common/Buffer.cpp \
			../Common/Command.cpp \
			../Common/User.cpp \
			../Common/UserManager.cpp \
			../Common/ASocket.cpp \
			../Common/SocketManager.cpp \
			LinSocket.cpp 

OBJ 		= $(SRC:.cpp=.o)

NAME 		= babel_server

CXXFLAGS 	= -W -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
