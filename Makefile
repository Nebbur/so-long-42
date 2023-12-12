.SILENT:

NAME = so_long

CC = cc
CFLAGS = -O3 -g -Wall -Wextra -Werror -g
MLXFLAGS = -L ./minilibx -lm -lmlx -Ilmlx -lXext -lX11 #-fsanitize=address
RM = rm -rf

INCS	= ./includes
SRCS_DIR= ./srcs
OBJS_DIR= ./obj

SRCF    = so_long fps map map_process map_checker map_checker_2 player enemies enemies_2 aux \
			free hook hook_2 player_2 put_on_screen sprites sprites_2 treating_loop wall wall_2

SRCS= $(addprefix ${SRCS_DIR}/, $(addsuffix .c, ${SRCF}))
OBJS= $(addprefix ${OBJS_DIR}/, $(addsuffix .o, ${SRCF}))

LIBFT = libft/libft.a
MINILIBX = minilibx/libmlx.a

all: deps $(NAME)

deps:
	$(MAKE) -C ./libft
	#$(MAKE) -C ./minilibx

$(NAME): $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	${CC} ${CFLAGS} -I${INCS} -c $< -o $@

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

clean:
	${RM} ${OBJS_DIR}
	printf "clean\033[0;32m  [OK]\n\033[0m"
	$(MAKE) -C libft clean

fclean:	clean
	$(MAKE) -C libft fclean
	${RM} $(LIBFT)
	${RM}	${NAME}
	printf "fclean\033[0;32m [OK]\n\033[0m"

re: fclean all
