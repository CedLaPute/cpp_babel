SRC		= LinSocket.cpp \
		  ../Common/ASocket.cpp \
		  ../Common/Sources/main.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -I./Headers/ -I../Windows/Headers/ -I../Common/Headers/ -W -Wall -Wextra -Werror -std=c++11

NAME		= Babel

all:		$(NAME)

$(NAME): $(OBJ)
		g++ -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all
