/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>

# define WINDOW_TITLE		"so_long"
# define WINDOW_WIDTH 		1024
# define WINDOW_HEIGHT		768
# define BPX 				64
# define HPX 				20
# define MPX 				1
# define MCF 				10 //MAX COIN FRAME
# define EHPX 				10
# define NBR_LIFE 			3
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
# define HUD_LM 			920

/*
	pp	= pixel position [0] = rows (x) | [1] = cols (y)
	tl	= tick life
	nl	= number life
	d	= direction 0 = left | 1 = right
	ac	= action code
	tll	= top left
	tr	= top right
	bl	= bottom left
	br	= bottom right
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
}		t_player;

/*
	p	= player 		sprite
	tr	= tile rock 	sprite
	bg	= background 	sprite
	gt	= gate			sprite
	c	= coin			sprite
	s	= scroll 		sprite
	e	= ennemy		sprite
*/

typedef struct s_sprites
{
	void	*p[1];
	void	*tr[38];
	void	*bg[1];
	void	*gt[1];
	void	*c[10];
	void	*s[4];
	void	*e[2];
}				t_sprites;

typedef struct s_coin
{
	int	current_frame;
	int	max_frame;
}				t_coin;

/// @brief Enemy structure
/*
	alive		= dead (0) or alive (1)
	move		= move(1) or not (0)
	ta			= tick attack
	td			= tick dead
	direction	= direction (0 left, 1 right)
	mi			= move interval
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

//	go		= global offset
//	po		= player offset
//	e		= quantidade de enemies
//	rl		= row limit
//	cl		= col limit
//	e		= number of enemies
//	enemy	= enemy node
//	enemies	= enemies list
typedef struct game_struct
{
	long long	frame_count;
	long long	last_time;
	long long	elapsed_time;
	long long	current_time;

	void		*img;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	char		**visible_map;
	int			cont;
	int			width;
	int			height;
	int			rl;
	int			cl;
	int			trig;
	int			col;
	int			rows;
	int			exit[2];
	int			e;
	int			moves;
	int			player_out;
	int			pic;
	int			pil;
	t_sprites	*sprites;
	t_player	*player;
	t_enemy		*enemy;
	t_list		*enemies;
	t_coin		*coin;

}			t_game;

int			main(int argc, char **argv);
int			check_file(char *map);
void		init_struct(t_game *game);
void		init_window(t_game *game);
void		ft_clearlst(t_list **lst);

//		hook.c
int			close_hook(int keycode, t_game *game);
void		hook_register(t_game *game);
int			keyup_hook(int keycode, t_game *game);
int			keydown_hook(int keycode, t_game *game);

//		hoo_k2.c
void		set_action(int keycode, t_game *game);
void		unset_action(int keycode, t_game *game);
int			get_action_keycode(int keycode);

//		enemies
void		init_enemies(t_game *game);
void		create_enemy(int row, int col, int id, t_game *game);
void		enemies(t_game *game);
//void		move_enemies(t_game *game);
void		move_enemies(t_game *game);
void		enemy_collision(int row, int col, t_game *game);
void		move_enemy_4(t_game *game);
void		init_camera(t_game *game);
void		aux_move_enemy(int sig, int new_xy[2], int trig_id[2], \
t_game *game);
int			is_it_safe(int x, int y, t_game *game);

//		player.c
void		player(t_game *game);
void		init_player(t_game *game);
void		player_position(t_game *game);

//		player_2.c
void		check_coin_position(t_game *game, int x, int y);
void		actual_position(t_game *game);
void		player_going_out(t_game *game);
void		aux_move_y(int xy[2], int rem_xy[2], t_game *game);
void		aux_move(int xy[2], int rem_xy[2], int t, t_game *game);

//		spites.c
void		init_sprites(t_game *game);
void		load_sprite(char *s_name, int s_nbr, int s_type, t_game *game);
char		*path_sprite(char *s_name, int i);
void		destroy_sprites(t_game *game);
void		aux_move_x(int xy[2], int rem_xy[2], t_game *game);

//		treatnig_loop
void		item(t_game *game);
void		scroll(t_game *game);

//		fps
long long	millitimestamp(void);
void		fps(t_game *game);

void		print_issue(t_game *game);

void		init_visible_map(t_game *game);
void		process_map(t_game *game);

//		put_on_screen.c
void		show_debug(t_game *game);
void		draw_block(int x, int y, void *sprite, t_game *game);
void		show_coins(t_game *game);
void		show_life(t_game *game);
void		show_moves(t_game *game);

//		free.c
void		free_enemy_list(t_list *enemy_list);
void		free_enemy_list(t_list *enemy_list);
void		free_to_all(t_game *game);
void		check_null(void **pointer);

//		aux.c
int			decimal_para_binario(int decimal);
void		verify_alloc(void *alloc, t_game *game);
void		aux_move_enemy_1(int new_xy[2], int trig_id[2], t_game *game);
void		aux_move_enemy_2(int new_xy[2], int trig_id[2], t_game *game);
//		wall
void		wall(t_game *game);
void		aux_wall_2(char **m, int r, int c, t_game *game);
void		background(t_game *game);

//			MAP
int			init_map(char *path, t_game *game);
void		free_map(char **map);
void		aux_find_pic(t_game *game, int trigger);
void		can_collect_all(char **map_copy, t_game *game, int y, int x);
void		can_reach_exit(char **map_copy, t_game *game, int y, int x);
void		freeTempMap(t_game *game, char **tempMap);
int			path_check(char *str, t_game *game);
char		**createTempMap(t_game *game);
char		**create_map(char *path);
void		init_visible_map(t_game *game);
int			check_rows_cols(t_game *game);
int			check_pce(t_game *game);
int			check_wall(t_game *game);
int			check_obstacles_or_not(t_game *game);
int			check_rectangular_map(t_game *game);

//			Get Next Line
int			get_lines(char *map);

#endif