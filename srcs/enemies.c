/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Create enmies in a linked list
void	create_enemy(int row, int col, int id, game_data *game)
{
	t_enemy	*e;

	e = ft_calloc(sizeof(t_enemy), 1);
	if (e == NULL)
		exit(EXIT_FAILURE);
	e->xy_last[0] = row;
	e->xy_last[1] = col;
	e->direction = 1;
	e->xy[0] = row;
	e->xy[1] = col;
	e->cont = 0;
	e->id = id;
	e->d = 1;
	if (game->enemies == NULL)
		game->enemies = ft_lstnew(e);
	else
		ft_lstadd_front(&game->enemies, ft_lstnew(e));
}

void	init_enemies(game_data *game)
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

int	is_it_safe(int x, int y, game_data *game)
{
	if (x < 1 || y < 1 || x >= game->rows || y >= (game->col - 1))
		return (0);
	if (game->map[x][y] == '0')
		return (1);
	return (0);
}

void	aux_move_enemy(int sig, int new_xy[2], int trig, int id, \
game_data *game)
{
	int	*new;
	int	cons;

	new = &new_xy[1];
	cons = new_xy[0];
	if (trig == 0)
	{
		new = &new_xy[0];
		cons = new_xy[1];
	}
	if (sig == 0)
		(*new)++;
	else
		(*new)--;
	if (trig == 0 && is_it_safe(*new, cons, game) == 0 || 
		trig == 1 && is_it_safe(cons, *new, game) == 0)
	{
		if (sig == 0)
			(*new)--;
		else
			(*new)++;
		game->enemy->d = id;
	}
}

void	enemy_collision(t_enemy *enemy, int row, int col, game_data *game)
{
	char	**m;

	m = game->map;
	if (m[row + 1][col] == 'P' || m[row - 1][col] == 'P')
		game->player->nl--;
	if (((m[row + 1][col - 1] == 'P' && m[row][col - 1] == '0' ) ||
	(m[row + 1][col + 1] == 'P' && m[row][col + 1] == '0' )) && \
	m[row + 1][col] == '0')
		game->player->nl--;
	if (m[row][col - 1] == 'P' || m[row][col + 1] == 'P')
		game->player->nl--;
	if (((m[row - 1][col - 1] == 'P' && m[row][col - 1] == '0' ) ||
	(m[row - 1][col + 1] == 'P' && m[row][col + 1] == '0' )) && \
	m[row - 1][col] == '0')
		game->player->nl--;
}

// determina a velocidade com a qual os inimigos se movem
void	enemies(game_data *game)
{
	t_list	*enemy_node;

	enemy_node = game->enemies;
	while (enemy_node)
	{
		game->enemy = (t_enemy *)(enemy_node->content);
		game->enemy->cont++;
		if (game->enemy->xy_last[1] < game->enemy->xy[1])
			draw_block((game->enemy->xy[1] - game->pic) * BPX, 
			(game->enemy->xy[0] - game->pil) * BPX, game->sprites->e[0], game);
		else
			draw_block((game->enemy->xy[1] - game->pic) * BPX, (game->enemy->xy[0] 
			- game->pil) * BPX, game->sprites->e[1], game);
		// determina a velocidade com a qual os inimigos se movem
		if (game->enemy->cont >= 30)
		{
			enemy_collision(game->enemy, game->enemy->xy[0], game->enemy->xy[1], game);
			move_enemies(game->enemy, game);
		}
		enemy_node = enemy_node->next;
	}
}
