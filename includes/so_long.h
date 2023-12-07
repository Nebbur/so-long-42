#ifndef SO_LONG_H
# define SO_LONG_H

#include "../minilibx/mlx.h"

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>

# define WINDOW_TITLE "so_long"
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define BPX 64
# define HPX 20
# define MPX 1
# define MCF 10 //MAX COIN FRAME
# define EHPX 10
# define NBR_LIFE 3
# define LETTER_KEY_LEFT	97
# define LETTER_KEY_RIGHT	100
# define LETTER_KEY_UP     	119
# define LETTER_KEY_DOWN	115
# define LETTER_KEY_ACTION	101
# define ARROW_KEY_LEFT	 	65361
# define ARROW_KEY_RIGHT	65363
# define ARROW_KEY_UP		65362
# define ARROW_KEY_DOWN		65364
# define SPACE_BAR			32
# define KEY_ESC			65307
# define HUD_LM 920

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/*
	pp = pixel position [0] = rows (x) | [1] = cols (y)
	tl = tick life
	nl = number life
	d = direction 0 = left | 1 = right
	ac = action code
	tll = top left
	tr = top right
	bl = bottom left
	br = bottom right
*/

typedef struct player_stt
{
	int	init_xy[2];
	int	xy[2];
	int	col_q;
	int	col_collected;
	int	exit_pos[2];
	int	collectable_pos[2];

	int	nl;
	int	d;
	int	ac[3];
}		player_st;

/*
	p	= player 		sprite
	tr	= tile rock 	sprite
	bg	= background 	sprite
	gt	= gate			sprite
	c	= coin			sprite
	s	= scroll 		sprite
	e	= ennemy		sprite
*/

typedef struct	s_sprites
{
	void	*p[1];
	void	*tr[38];
	void	*bg[1];
	void	*gt[1];
	void	*c[10];
	void	*s[4];
	void	*e[2];
}				t_sprites;

typedef struct	s_coin
{
	int	current_frame;
	int	max_frame;
}				t_coin;

/// @brief Enemy structure
/*
	alive : dead (0) or alive (1)
	move : move(1) or not (0)
	ta : tick attack
	td : tick dead
	direction : direction (0 left, 1 right)
	mi : move interval
*/

typedef struct s_enemy
{
	int			direction;
	int			xy[2];
	int			xy_last[2];
	int			d;
	int			id;
	int			cont;
}			t_enemy;

/*
	go = global offset
	po = player offset
	e = quantidade de enemies

	width e rows é igual
	height e col é igual
	tenho de ajustar isso, repeticao de variaveis
*/

typedef struct	game_struct
{
	long long	frame_count;
	long long	last_time;
	long long	elapsed_time;
	long long	current_time;

	int		cont;

	int		width;
	int		height;
	char	**map;
	char	**visible_map;
	
	int		rl; 			// row limit
	int		cl; 			// col limit
	int		trig;

	void 	*mlx;
    void 	*mlx_win;
	int		col;
	int		rows;
	int		exit[2];
	int		e;				//number of enemies
	int		moves;
	int		player_out;
	int		pic;
	int		pil;

	t_sprites	*sprites;
	player_st	*player;
	t_enemy		*enemy;		//enemy node
	t_list		*enemies;	//enemies list
	t_data		*img;
	t_coin		*coin;

}			game_data;

int			main(int argc, char **argv);
void 		rendering(game_data *game, char *path, int x, int y);
int 		check_file(char *map);
void    	init_struct(game_data *game);

void		init_window(game_data *game);

void		ft_clearlst(t_list **lst);

//		hook.c
int			close_hook(int keycode, game_data *game);
void		hook_register(game_data *game);
int			keyup_hook(int keycode, game_data *game);
int			keydown_hook(int keycode, game_data *game);

//		hoo_k2.c
void		set_action(int keycode, game_data *game);
void		unset_action(int keycode, game_data *game);
int			get_action_keycode(int keycode);

//		enemies
void		init_enemies(game_data *game);
void		create_enemy(int row, int col, int id, game_data *game);
void		enemies(game_data *game);
void		move_enemies(t_enemy *enemy, game_data * game);
void		enemy_collision(t_enemy *enemy, int row, int col, game_data *game);
void 		move_enemy_4(t_enemy *e, game_data *game);
void		init_camera(game_data *game);
void		aux_move_enemy(int sig, int new_xy[2], int trig, int id, game_data *game);
int			is_it_safe(int x, int y, game_data *game);

//		player.c
void		player(game_data *game);
void		player_position_onthemap(game_data *game);
void		init_player(game_data *game);
void		player_position(game_data *game);

//		player_2.c
void		check_coin_position(game_data *game, int x, int y);
void		actual_position(game_data *game);
void		player_going_out(game_data *game);
void		aux_move_y(int xy[2], int rem_xy[2], game_data *game);
void		aux_move(int xy[2], int rem_xy[2], int t, game_data *game);

//		spites.c
void		init_sprites(game_data *game);
void		load_sprite(char *s_name, int s_nbr, int s_type, game_data *game);
char		*path_sprite(char *s_name, int i);
void		destroy_sprites(game_data *game);
void		aux_move_x(int xy[2], int rem_xy[2], game_data *game);

//		treatnig_loop
void		item(game_data *game);
void		scroll(game_data *game);

//		fps
long long	millitimestamp(void);
void		fps(game_data *game);

void		print_issue(game_data *game);

void 		init_visible_map(game_data *game);
void		process_map(game_data *game);

//		put_on_screen.c
void		show_debug(game_data *game);
void		draw_block(int x, int y, void *sprite, game_data *game);
void		show_coins(game_data *game);
void		show_life(game_data *game);
void		show_moves(game_data *game);

//		free.c
void		free_enemy_list(t_list *enemy_list);
void		free_enemy_list(t_list *enemy_list);
void		free_to_all(game_data *game);
void		check_null(void **pointer);

//		aux.c
int			decimal_para_binario(int decimal);
void		verify_alloc(void *alloc, game_data *game);

//		wall
void		wall(game_data *game);
void		aux_wall_2(char **m, int r, int c, game_data *game);
void		background(game_data *game);

//			MAP
int			init_map(char *path, game_data *game);
void		free_map(char **map);
void		aux_find_pic(game_data *game, int pic, int trigger);
int			dist_two_points(int from_y, int to_y, game_data *game);
void		canCollectAll(char **map_copy, game_data *game, int y, int x);
void		canReachExit(char **map_copy, game_data *game, int y, int x);
void		freeTempMap(game_data *game, char **tempMap);
int			check_obstacles_or_not(game_data *game);
int			path_check(char *str, game_data *game);
int			check_rows_cols(game_data *game);
char		**createTempMap(game_data *game);
char		**create_map(char *path);
void		init_visible_map(game_data *game);

//			Get Next Line
int			get_lines(char *map);

#endif