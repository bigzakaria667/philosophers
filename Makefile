# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 13:57:27 by zel-ghab          #+#    #+#              #
#    Updated: 2025/07/29 19:08:45 by zel-ghab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 18:01:25 by zel-ghab          #+#    #+#              #
#    Updated: 2025/06/23 16:46:45 by zel-ghab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################################
## ARGUMENTS

NAME 		= philo
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g

###########################################
## SOURCES

SRC_FILES	= philo.c \
		parsing.c \
		initialisation.c \
		routine.c \
		states.c

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
