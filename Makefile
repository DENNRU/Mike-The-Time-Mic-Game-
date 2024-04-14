##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## makefile
##

SRC 	=	$(wildcard src/*.cpp)

O	=	$(SRC:src/.cpp =.o)

N	=	 MikeTheTimeMike

LDFLAGS		= 	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -g

all:	$(N)

$(N):
	g++ -o $(N) $(O) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(N)

fclean: clean

re:	clean	all
