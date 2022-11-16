# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atouati <atouati@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 19:13:44 by atouati           #+#    #+#              #
#    Updated: 2022/11/16 00:17:32 by atouati          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c parser/handling_quotes.c \
			libft/ft_strjoin.c libft/ft_isdigit.c parser/expand.c parser/expand_2.c parser/util.c parser/util_2.c parser/handling_spaces.c parser/quotes.c parser/fill_stack.c \
			parser/dollar_func.c utils.c signal.c executor.c exec.c bin.c redir.c sepr.c run_builtins.c fd.c parser/strjoin.c \
			heredoc.c prompt.c
SRCS2 = libft/ft_memmove.c libft/ft_isalpha.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_strdup.c \
	libft/ft_isprint.c libft/ft_strcpy.c libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memcmp.c libft/ft_toupper.c \
	libft/ft_tolower.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_atoi.c libft/ft_strcat.c libft/ft_split.c \
	libft/ft_strncmp.c libft/ft_strncpy.c libft/ft_memchr.c libft/ft_calloc.c libft/ft_substr.c\
	libft/ft_strtrim.c libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c \
	libft/ft_putchar_fd.c libft/ft_strcmp.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
	libft/ft_memdel.c
	
	
BUILTINS = builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c \
		   builtins/unset.c env_func/ft_list_sort_env.c

		   	
CC	= cc
RM	= rm -f
NAME = minishell
#CFLAGS	= -Wall -Werror -Wextra


all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${SRCS} ${SRCS2} ${BUILTINS} -lreadline -L /Users/atouati/homebrew/opt/readline/lib -I /Users/atouati/homebrew/opt/readline/include -o ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

push:
	@git add .
	@git commit -m "messi"
	@git push
