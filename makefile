# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pderksen <pderksen@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/10 16:40:14 by pderksen      #+#    #+#                  #
#    Updated: 2022/05/10 16:41:01 by pderksen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-
NAME := pipex

CC := gcc

ifndef DEBUG
CFLAGS := -Wall -Wextra -Werror
else
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
endif

SRCS := main.c 
HEADERFILES := pipex.h

LIBFT := libft/libft.a

all: $(NAME)

$(NAME) : $(SRCS) $(LIBFT)
		$(CC) $(CFLAGS) -o $@ $^

$(LIBFT) :
	$(MAKE) -C libft

clean :
	$(MAKE) clean -C libft 

fclean :
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re : fclean all

.PHONY : all, clean, fclean, re
