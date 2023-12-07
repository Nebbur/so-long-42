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

void	aux_move_y(int xy[2], int rem_xy[2], game_data *game)
{
	rem_xy[1] = 1;
	if (game->visible_map[xy[0] - game->pil][xy[1] + 1 - game->pic] == 'E' \
	&& game->player->col_collected == game->player->col_q)
		aux_move(xy, rem_xy, 0, game);
	else if (!(game->visible_map[xy[0] - game->pil][xy[1] + 1 - game->pic] \
	== 'E' || game->visible_map[xy[0] - game->pil][xy[1] + 1 - \
	game->pic] == '1'))
		aux_move(xy, rem_xy, 1, game);
}

void	aux_move_x(int xy[2], int rem_xy[2], game_data *game)
{
	rem_xy[0] = 1;
	rem_xy[1] = 0;
	if (game->visible_map[xy[0] + 1 - game->pil][xy[1] - \
	game->pic] == 'E' && game->player->col_collected == game->player->col_q)
		aux_move(xy, rem_xy, 0, game);
	else if (!(game->visible_map[xy[0] + 1 - game->pil][xy[1] - \
	game->pic] == 'E' || game->visible_map[xy[0] + 1 - \
	game->pil][xy[1] - game->pic] == '1'))
		aux_move(xy, rem_xy, 1, game);
}

void	check_coin_position(game_data *game, int x, int y)
{
	if (game->visible_map[x][y] == 'C')
		game->player->col_collected++;
}

void	actual_position(game_data *game)
{
	int	rows;
	int	cols;
	int	x;
	int	y;

	x = game->exit[0];
	y = game->exit[1];
	rows = -1;
	while (++rows < game->rl)
	{
		cols = -1;
		while (++cols <= game->cl)
		{
			if (game->map[x][y] == 'P')
				player_going_out(game);
			else if (game->visible_map[rows][cols] == 'P')
			{
				game->player->xy[0] = rows + game->pil;
				game->player->xy[1] = cols + game->pic;
				draw_block(cols * BPX,
					rows * BPX, game->sprites->p[0], game);
			}
		}
	}
}

void	player_going_out(game_data *game)
{
	mlx_loop_end(game->mlx);
}
