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

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	if (map != NULL)
		free(map);
}

char	**create_map(char *path)
{
	int		fd;
	int		i;
	int		j;
	char	**map;

	i = get_lines(path);
	map = (char **)calloc(i + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	j = -1;
	while (++j != i)
	{
		map[j] = get_next_line(fd);
		if (!map[j])
		{
			close(fd);
			return (NULL);
		}
	}
	map[j] = NULL;
	close(fd);
	return (map);
}

void	init_visible_map(t_game *game)
{
	int	i;

	i = -1;
	game->rl = WINDOW_HEIGHT / BPX;
	game->cl = WINDOW_WIDTH / BPX;
	if (game->rl > game->rows + 1)
		game->rl = game->rows + 1;
	game->visible_map = (char **)ft_calloc(game->rl + 1, sizeof(char *));
	if (game->visible_map == NULL)
		free_to_all(game);
	if (game->cl > game->col - 1)
		game->cl = game->col;
	while (++i < game->rl)
	{
		game->visible_map[i] = (char *)ft_calloc(game->cl + 1, sizeof(char));
		if (game->visible_map[i] == NULL)
			free_to_all(game);
	}
	game->visible_map[i] = NULL;
}

int	init_map(char *path, t_game *game)
{
	if (check_file(path) != 0)
	{
		free_to_all(game);
		exit (EXIT_FAILURE);
	}
	game->map = create_map(path);
	if (game->map == NULL)
		free_to_all(game);
	if (check_rectangular_map(game) != 0 || check_pce(game) != 0 || \
		check_rows_cols(game) != 0 || check_wall(game) != 0 || \
		check_obstacles_or_not(game) != 0 || path_check(path, game) != 0)
	{
		ft_printf("Error.\nMap's invalid.\n");
		free_to_all(game);
		exit (EXIT_FAILURE);
	}
	game->height = game->rows;
	game->width = game->col;
	init_visible_map(game);
	game->player->xy[0] = game->player->init_xy[0];
	game->player->xy[1] = game->player->init_xy[1];
	process_map(game);
	return (0);
}
