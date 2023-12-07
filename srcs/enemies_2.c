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
void	move_enemy_1(t_enemy *e, game_data *game)
{
	int	new_xy[2];

	e->cont = 0;
	new_xy[0] = e->xy[0];
	new_xy[1] = e->xy[1];
	if (e->d <= 1)
		aux_move_enemy(0, new_xy, 1, 2, game);
	if (e->d == 2)
		aux_move_enemy(1, new_xy, 0, 3, game);
	if (e->d >= 3 && e->d <= 4)
		aux_move_enemy(1, new_xy, 1, 5, game);
	if (e->d >= 5 && e->d <= 6)
		aux_move_enemy(0, new_xy, 0, 7, game);
	if (e->d >= 7 && e->d <= 8)
		aux_move_enemy(0, new_xy, 1, 9, game);
	if (e->d == 9)
		aux_move_enemy(1, new_xy, 0, 0, game);
	if (e->d == 10)
		e->d = 1;
	e->d++;
	if (is_it_safe(new_xy[0], new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
}

// mover no sentido do relogio
void	move_enemy_2(t_enemy *e, game_data *game)
{
	int	new_xy[2];

	e->cont = 0;
	new_xy[0] = e->xy[0];
	new_xy[1] = e->xy[1];
	if (e->d <= 1)
		aux_move_enemy(1, new_xy, 1, 2, game);
	if (e->d == 2)
		aux_move_enemy(1, new_xy, 0, 3, game);
	if (e->d >= 3 && e->d <= 4)
		aux_move_enemy(0, new_xy, 1, 5, game);
	if (e->d >= 5 && e->d <= 6)
		aux_move_enemy(0, new_xy, 0, 7, game);
	if (e->d >= 7 && e->d <= 8)
		aux_move_enemy(1, new_xy, 1, 9, game);
	if (e->d == 9)
		aux_move_enemy(1, new_xy, 0, 0, game);
	if (e->d == 10)
		e->d = 1;
	e->d++;
	if (is_it_safe(new_xy[0], new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
}

// mover verticalmente
void	move_enemy_3(t_enemy *e, game_data *game)
{
	int	new_xy[2];

	e->cont = 0;
	new_xy[0] = e->xy[0];
	new_xy[1] = e->xy[1];
	if (game->map[e->xy[0] - 1][e->xy[1]] != '0')
		e->d = 0;
	else if (game->map[e->xy[0] + 1][e->xy[1]] != '0')
		e->d = 1;
	if (e->d == 1 && is_it_safe(--new_xy[0], new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
	else if (e->d == 0 && is_it_safe(++new_xy[0], new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
}

// mover horizontalmente
void	move_enemy_4(t_enemy *e, game_data *game)
{
	int	new_xy[2];

	e->cont = 0;
	new_xy[0] = e->xy[0];
	new_xy[1] = e->xy[1];
	if (game->map[e->xy[0]][e->xy[1] - 1] != '0')
		e->d = 0;
	else if (game->map[e->xy[0]][e->xy[1] + 1] != '0')
		e->d = 1;
	if (e->d == 1 && is_it_safe(new_xy[0], --new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
	else if (e->d == 0 && is_it_safe(new_xy[0], ++new_xy[1], game) == 1)
	{
		game->map[e->xy[0]][e->xy[1]] = '0';
		e->xy[0] = new_xy[0];
		e->xy[1] = new_xy[1];
		game->map[e->xy[0]][e->xy[1]] = 'M';
	}
}

void	move_enemies(t_enemy *enemy, game_data *game)
{
	enemy->xy_last[0] = enemy->xy[0];
	enemy->xy_last[1] = enemy->xy[1];
	if (enemy->id == 0)
		move_enemy_1(enemy, game);
	if (enemy->id == 1)
		move_enemy_2(enemy, game);
	if (enemy->id == 2)
		move_enemy_3(enemy, game);
	if (enemy->id == 3)
		move_enemy_4(enemy, game);
}
