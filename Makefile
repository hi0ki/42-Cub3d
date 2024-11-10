CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	$(addprefix mandatory/, gnl/get_next_line.c gnl/get_next_line_utils.c \
			libft_utils/ft_arraylen.c libft_utils/ft_free_array.c libft_utils/ft_put.c libft_utils/ft_split.c libft_utils/ft_strtrim.c\
			libft_utils/ft_substr.c libft_utils/ft_strchr.c libft_utils/_strlen.c libft_utils/_strjoin.c libft_utils/ft_atoi.c libft_utils/ft_strcmp.c\
			parsing/parsing1.c parsing/parsing2.c parsing/parsing3.c parsing/parsing0.c parsing/move_player.c \
			parsing/check/check_map.c parsing/check/che_map_utils.c parsing/check/check_utils.c\
			parsing/draw_map.c\
			raycasting/raycasting_utils.c raycasting/raycasting.c raycasting/utils.c\
			texturing.c \
			main.c)

BONUS_SRCS =    $(addprefix bonus/, gnl/get_next_line.c gnl/get_next_line_utils.c \
				libft_utils/ft_arraylen.c libft_utils/ft_free_array.c libft_utils/ft_put.c libft_utils/ft_split.c libft_utils/ft_strtrim.c\
				libft_utils/ft_substr.c libft_utils/ft_strchr.c libft_utils/_strlen.c libft_utils/_strjoin.c libft_utils/ft_atoi.c libft_utils/ft_strcmp.c\
				libft_utils/ft_lstadd_back_bonus.c libft_utils/ft_lstnew_bonus.c\
				parsing/parsing1.c parsing/parsing2.c parsing/parsing3.c parsing/parsing0.c parsing/move_player.c parsing/move_utils.c \
				parsing/check/check_map.c parsing/check/che_map_utils.c parsing/check/check_utils.c\
				parsing/draw/draw_map.c  parsing/draw/draw_utils.c parsing/draw/draw_minimap.c\
				raycasting/raycasting_utils.c raycasting/raycasting.c raycasting/utils.c\
				texturing.c \
				main.c)

MLX 	    = 	MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
HEADER_M	= 	mandatory/gnl/get_next_line.h mandatory/include/types.h mandatory/include/cub3d.h  
HEADER_B	= 	bonus/gnl/get_next_line.h bonus/include/types.h bonus/include/cub3d.h 
OBJS	    =	$(SRCS:.c=.o)
BONUS_OBJS  =   $(BONUS_SRCS:.c=.o)
NAME        =   cub3d
BONUS_NAME  =   cub3d_bonus

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_M)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(HEADER_B)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(MLX)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus