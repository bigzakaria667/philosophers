# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 15:33:41 by zel-ghab          #+#    #+#              #
#    Updated: 2025/08/18 15:35:40 by zel-ghab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################################
## ARGUMENTS

NAME 		= philo
CC		= cc
CFLAGS		= -Wall -Wextra -Werror #-g3 -fsanitize=thread

###########################################
## SOURCES

SRC_FILES	= philo.c \
		source/parsing.c \
		source/initialisation.c \
		source/routine.c \
		source/doctor.c \
		source/utils.c

###########################################
## OBJECTS

OBJ_DIR = .cache
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

###########################################
## RULES

all : ${NAME}

${NAME} : ${OBJ_FILES}
	@echo "🛠️  Compiling libraries..."
	@${CC} ${CFLAGS} ${OBJ_FILES} -o ${NAME}
	@echo "✅ Compilation successful !"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${OBJ_DIR}
	@echo "🧹 Object files removed."

fclean : clean
	@rm -rf ${NAME}
	@echo "🧹 Everything is cleaned."

re : fclean all

.PHONY: all clean fclean re
