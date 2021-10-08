SRCS            = main.cpp

OBJS            = $(SRCS:.cpp=.o)

NAME            = cont.out
NAME_TEST		= cont_test.out

CC				= clang++
RM				= rm -f

CFLAGS  		= -Wall -Wextra -Werror -std=c++98 

%.o:		%.cpp
			$(CC) $(FLAGS) -o $@ -c $<

all:         $(NAME) $(NAME_TEST)

$(NAME):	$(OBJS) containers/vector.hpp containers/stack.hpp utility.hpp containers/map.hpp
			$(CC) -DSTL=0 -o $(NAME) $(CFLAGS) $(SRCS)

$(NAME_TEST):	$(OBJS) containers/vector.hpp containers/stack.hpp utility.hpp containers/map.hpp
				$(CC) -DSTL=1 $(CFLAGS) -o $(NAME_TEST) $(SRCS)


clean:
			$(RM) $(OBJS) 

fclean:     clean
			$(RM) $(NAME) $(NAME_TEST)

re:			fclean all
