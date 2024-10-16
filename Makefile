# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchissal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 12:36:20 by dchissal          #+#    #+#              #
#    Updated: 2024/06/12 12:36:27 by dchissal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            := fdf
BONUSNAME       := fdf_bonus
CC              := cc
RM              := rm -f
FLAGS           := -Wall -Wextra -Werror
DEBUG           := -g

HEADDIR         := ./includes/
HEADLIST        := fdf.h
HEADERS         := $(addprefix ${HEADDIR}, ${HEADLIST})

SRCSDIR         := ./src/
SRCSLIST        := main.c \
                    ft_ajust_map1.c \
                    ft_ajust_map2.c \
                    ft_define_color.c \
                    ft_draw_map1.c \
                    ft_draw_map2.c \
                    ft_draw_matriz1.c \
                    ft_draw_matriz2.c \
                    ft_project_iso.c  \
                    ft_strtok.c       \
                    my_img.c
SRCS            := $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR         := ./obj/
OBJSLIST        := ${SRCSLIST:.c=.o}
OBJS            := $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR        := ./libft/
LIBFT           := ${LIBFTDIR}libft.a

MLXDIR          := ./minilibx-linux/
MLX             := ${MLXDIR}libmlx.a

LIBS            := -L${LIBFTDIR} -L${MLXDIR} -lft -lmlx -lXext -lX11 -lm
INCS            := -I${HEADDIR} -I${LIBFTDIR} -I${MLXDIR}

${NAME}:        ${MLX} ${LIBFT} ${OBJSDIR} ${OBJS}
		${CC} ${OBJS} -o ${NAME} ${LIBS} ${INCS}

${LIBFT}:
		make -C ${LIBFTDIR}

${MLX}:
		git submodule init
		git submodule update
		make -C ${MLXDIR}

${OBJSDIR}%.o: ${SRCSDIR}%.c ${HEADERS}
		@${CC} ${INCS} -c $< -o $@

${OBJSDIR}:
		mkdir -p ${OBJSDIR}

${OBJSDIRBONUS}:
		mkdir -p ${OBJSDIRBONUS}


all: ${NAME}

clean:
		@${RM} -r ${OBJSDIR}
		@${RM} -r ${OBJSDIRBONUS}
		make -C ${LIBFTDIR} clean
		make -C ${MLXDIR} clean

fclean: clean
		@${RM} ${NAME}
		@${RM} ${BONUSNAME}
		make -C ${LIBFTDIR} fclean

re: fclean all

.PHONY: all clean fclean re 
