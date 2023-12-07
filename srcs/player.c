/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_player(game_data *game)
{
	game->player->nl = NBR_LIFE;
	game->player_out = 0;
	game->player->col_q = 0;
	game->player->col_collected = 0;
	game->player->init_xy[0] = 0;
	game->player->init_xy[1] = 0;
	game->player->collectable_pos[0] = 0;
	game->player->collectable_pos[1] = 0;
}

void	aux_move(int xy[2], int rem_xy[2], int t, game_data *game)
{
	if (t == 1)
		check_coin_position(game, xy[0] + rem_xy[0] - game->pil, xy[1] \
		+ rem_xy[1] - game->pic);
	if (game->map[xy[0] + rem_xy[0]][xy[1] + rem_xy[1]] != '1' &&
		game->map[xy[0] + rem_xy[0]][xy[1] + rem_xy[1]] != 'M')
	{
		game->map[xy[0]][xy[1]] = '0';
		game->map[xy[0] + rem_xy[0]][xy[1] + rem_xy[1]] = 'P';
	}
	if (rem_xy[0] != 0)
		game->player->xy[0] = xy[0] + rem_xy[0];
	else
		game->player->xy[1] = xy[1] + rem_xy[1];
	game->moves++;
}

static void	move_y(game_data *game)
{
	int			xy[2];
	int			rem_xy[2];

	rem_xy[0] = 0;
	rem_xy[1] = -1;
	xy[0] = game->player->xy[0];
	xy[1] = game->player->xy[1];
	if (game->player->ac[0] == 1 && game->visible_map[xy[0] - \
	game->pil][xy[1] - 1 - game->pic] != '1')
	{
		if (game->visible_map[xy[0] - game->pil][xy[1] - 1 - \
		game->pic] == 'E' && game->player->col_collected == game->player->col_q)
			aux_move(xy, rem_xy, 0, game);
		else if (!(game->visible_map[xy[0] - game->pil][xy[1] - \
		1 - game->pic] == 'E' || \
		game->visible_map[xy[0] - game->pil][xy[1] - 1 - game->pic] == '1'))
			aux_move(xy, rem_xy, 1, game);
	}
	else if (game->player->ac[0] == 2)
		aux_move_y(xy, rem_xy, game);
}

static void	move_x(game_data *game)
{
	int			xy[2];
	int			rem_xy[2];

	rem_xy[0] = -1;
	rem_xy[1] = 0;
	xy[0] = game->player->xy[0];
	xy[1] = game->player->xy[1];
	if (game->player->ac[0] == 10)
	{
		if (game->visible_map[xy[0] - 1 - game->pil][xy[1] - \
		game->pic] == 'E' && 
		game->player->col_collected == game->player->col_q)
			aux_move(xy, rem_xy, 0, game);
		else if (!(game->visible_map[xy[0] - 1 - game->pil][xy[1] - \
		game->pic] == 'E' || game->visible_map[xy[0] - 1 - \
		game->pil][xy[1] - game->pic] == '1'))
			aux_move(xy, rem_xy, 1, game);
	}
	else if (game->player->ac[0] == 4)
		aux_move_x(xy, rem_xy, game);
}

//main function player
void	player(game_data *game)
{
	if (game->player->nl <= 0)
	{
		ft_printf("Game Over\n");
		mlx_loop_end(game->mlx);
	}
	actual_position(game);
	move_y(game);
	move_x(game);
	game->player->ac[0] = 0;
}
