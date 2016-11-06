##
## Makefile for Makefile in /home/montav_c/rendu/cpp_babel/Server/BabelServer/BabelServer/Unix
## 
## Made by Cedric MONTAVON
## Login   <montav_c@epitech.eu>
## 
## Started on  Sat Nov  5 16:52:52 2016 Cedric MONTAVON
## Last update Sun Nov  6 16:03:22 2016 Cedric MONTAVON
##

SRC			= ../Common/Sources/main.cpp \
			../Common/Sources/Mallocator.cpp \
			../Common/Sources/Message.cpp \
			../Common/Sources/AUser.cpp \
			../Common/Sources/LinUser.cpp \
			../Common/Sources/UserManager.cpp \
			Sources/Unix.cpp

OBJ 		= $(SRC:.cpp=.o)

NAME 		= babel_server

CXXFLAGS 	= -I./Headers/ -W -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
