/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_struct(t_game *game)
{
	game->player = ft_calloc(sizeof(t_player), 1);
	game->sprites = ft_calloc(sizeof(t_sprites), 1);
	game->coin = ft_calloc(sizeof(t_coin), 1);
	verify_alloc(game->player, game);
	verify_alloc(game->sprites, game);
	verify_alloc(game->coin, game);
	game->img = NULL;
	game->enemies = NULL;
	game->map = NULL;
	game->visible_map = NULL;
	game->cont = 0;
	game->frame_count = 0;
	game->last_time = 0;
	game->elapsed_time = 0;
	game->moves = 0;
	game->coin->max_frame = MCF;
	game->coin->current_frame = 0;
	game->width = 0;
	game->height = 0;
	game->exit[0] = 0;
	game->exit[1] = 0;
}

void	init_enemies(t_game *game)
{
	int	rows;
	int	cols;
	int	id;

	id = 0;
	rows = -1;
	game->e = 0;
	while (game->map[++rows])
	{
		cols = -1;
		while (game->map[rows][++cols])
		{
			if (game->map[rows][cols] == 'M')
			{
				game->e++;
				if (id == 4)
					id = 0;
				create_enemy(rows, cols, id++, game);
			}
		}
	}
}

// General loop of the game
static int	game_loop(t_game *game)
{
	game->current_time = millitimestamp();
	game->elapsed_time = (game->current_time - game->last_time) * 1000;
	game->frame_count++;
	if (game->elapsed_time >= 1000000 / 30)
	{
		fps(game);
		if (mlx_clear_window(game->mlx, game->mlx_win) == 1)
			ft_printf("clear window success\n");
		background(game);
		wall(game);
		item(game);
		enemies(game);
		player(game);
		show_debug(game);
		process_map(game);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf ("Invalid number of arguments\n");
		return (1);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		mlx_destroy_display(game.mlx);
	mlx_get_screen_size(game.mlx, &game.width, &game.height);
	game.mlx_win = mlx_new_window(game.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_TITLE);
	init_struct(&game);
	init_player(&game);
	init_map(argv[1], &game);
	init_sprites(&game);
	init_enemies(&game);
	hook_register(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_to_all(&game);
	exit(EXIT_SUCCESS);
}
