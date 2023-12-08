/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_obstacles_or_not(t_game *game)
{
	char	**m;
	int		col;
	int		rows;

	m = game->map;
	rows = -1;
	while (rows < game->rows && m[++rows])
	{
		col = -1;
		while (col < game->col - 1 && m[rows][++col])
		{
			if (!(ft_strchr("PCEM10", m[rows][col])))
				return (1);
			else if (m[rows][col] == 'E')
			{
				game->player->exit_pos[0] = rows;
				game->player->exit_pos[1] = col;
			}
		}
	}
	return (0);
}

void	can_collect_all(char **map_copy, t_game *game, int y, int x)
{
	if (x < 1 || y < 1 || x > game->col || y > game->rows)
		return ;
	if (map_copy[y][x] == '\0' || map_copy[y][x] == '\n')
		return ;
	if (map_copy[y][x] == 'O' || map_copy[y][x] == '1')
		return ;
	if (map_copy[y][x] == 'E')
		return ;
	if (map_copy[y][x] == 'C')
		game->player->col_collected++;
	map_copy[y][x] = 'O';
	can_collect_all(map_copy, game, y - 1, x);
	can_collect_all(map_copy, game, y + 1, x);
	can_collect_all(map_copy, game, y, x - 1);
	can_collect_all(map_copy, game, y, x + 1);
}

void	can_reach_exit(char **map_copy, t_game *game, int y, int x)
{
	if (x < 1 || y < 1 || x > game->col || y > game->rows)
		return ;
	if (map_copy[y][x] == '\0' || map_copy[y][x] == '\n')
		return ;
	if (map_copy[y][x] == 'O' || map_copy[y][x] == '1')
		return ;
	map_copy[y][x] = 'O';
	can_reach_exit(map_copy, game, y - 1, x); 
	can_reach_exit(map_copy, game, y + 1, x); 
	can_reach_exit(map_copy, game, y, x - 1); 
	can_reach_exit(map_copy, game, y, x + 1);
}

int	path_check(char *str, t_game *game)
{
	char	**map_copy;

	map_copy = create_map(str);
	if (!map_copy)
		return (1);
	can_collect_all(map_copy, game, game->player->init_xy[0], \
	game->player->init_xy[1]);
	if (game->player->col_q != game->player->col_collected)
	{
		free_map(map_copy);
		return (1);
	}
	game->player->col_collected = 0;
	free_map(map_copy);
	map_copy = create_map(str);
	can_reach_exit(map_copy, game, game->player->init_xy[0], \
	game->player->init_xy[1]);
	if (map_copy[game->player->exit_pos[0]][game->player->exit_pos[1]] != 'O')
	{
		free_map(map_copy);
		return (1);
	}
	free_map(map_copy);
	return (0);
}
