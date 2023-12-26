# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 14:39:00 by thepaqui          #+#    #+#              #
#    Updated: 2023/12/26 15:47:04 by thepaqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Matrix

CC= c++

CCFLAGS= -Wall -Wextra -Werror -std=c++2a

SRCS=	main.cpp

OBJS= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re