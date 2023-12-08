/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// mover no sentido contrario do relogio
void	move_enemy_1(t_game *game)
{
	int	new_xy[2];
	int	trig_id[2];

	trig_id[0] = 1;
	trig_id[1] = 2;
	game->enemy->cont = 0;
	new_xy[0] = game->enemy->xy[0];
	new_xy[1] = game->enemy->xy[1];
	aux_move_enemy_1(new_xy, trig_id, game);
	if (game->enemy->d == 9)
	{
		trig_id[0] = 0;
		trig_id[1] = 0;
		aux_move_enemy(1, new_xy, trig_id, game);
	}
	if (game->enemy->d == 10)
		game->enemy->d = 1;
	game->enemy->d++;
	if (is_it_safe(new_xy[0], new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
}

// mover no sentido do relogio
void	move_enemy_2(t_game *game)
{
	int	new_xy[2];
	int	trig_id[2];

	trig_id[0] = 1;
	trig_id[1] = 2;
	game->enemy->cont = 0;
	new_xy[0] = game->enemy->xy[0];
	new_xy[1] = game->enemy->xy[1];
	aux_move_enemy_2(new_xy, trig_id, game);
	if (game->enemy->d == 9)
	{
		trig_id[0] = 0;
		trig_id[1] = 0;
		aux_move_enemy(1, new_xy, trig_id, game);
	}
	if (game->enemy->d == 10)
		game->enemy->d = 1;
	game->enemy->d++;
	if (is_it_safe(new_xy[0], new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
}

// mover verticalmente
void	move_enemy_3(t_game *game)
{
	int	new_xy[2];

	game->enemy->cont = 0;
	new_xy[0] = game->enemy->xy[0];
	new_xy[1] = game->enemy->xy[1];
	if (game->map[game->enemy->xy[0] - 1][game->enemy->xy[1]] != '0')
		game->enemy->d = 0;
	else if (game->map[game->enemy->xy[0] + 1][game->enemy->xy[1]] != '0')
		game->enemy->d = 1;
	if (game->enemy->d == 1 && is_it_safe(--new_xy[0], new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
	else if (game->enemy->d == 0 && is_it_safe(++new_xy[0], \
	new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
}

// mover horizontalmente
void	move_enemy_4(t_game *game)
{
	int	new_xy[2];

	game->enemy->cont = 0;
	new_xy[0] = game->enemy->xy[0];
	new_xy[1] = game->enemy->xy[1];
	if (game->map[game->enemy->xy[0]][game->enemy->xy[1] - 1] != '0')
		game->enemy->d = 0;
	else if (game->map[game->enemy->xy[0]][game->enemy->xy[1] + 1] != '0')
		game->enemy->d = 1;
	if (game->enemy->d == 1 && is_it_safe(new_xy[0], --new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
	else if (game->enemy->d == 0 && is_it_safe(new_xy[0], \
	++new_xy[1], game) == 1)
	{
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = '0';
		game->enemy->xy[0] = new_xy[0];
		game->enemy->xy[1] = new_xy[1];
		game->map[game->enemy->xy[0]][game->enemy->xy[1]] = 'M';
	}
}

void	move_enemies(t_game *game)
{
	game->enemy->xy_last[0] = game->enemy->xy[0];
	game->enemy->xy_last[1] = game->enemy->xy[1];
	if (game->enemy->id == 0)
		move_enemy_1(game);
	if (game->enemy->id == 1)
		move_enemy_2(game);
	if (game->enemy->id == 2)
		move_enemy_3(game);
	if (game->enemy->id == 3)
		move_enemy_4(game);
}
