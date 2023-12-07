/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	aux_destroy_sprite(int i, int s_type, char *path, game_data *game)
{
	if (s_type == 1 && game->sprites->p[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->p[i]);
	else if (s_type == 2 && game->sprites->tr[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->tr[i]);
	else if (s_type == 5 && game->sprites->bg[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->bg[i]);
	else if (s_type == 6 && game->sprites->gt[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->gt[i]);
	else if (s_type == 7 && game->sprites->c[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->c[i]);
	else if (s_type == 8 && game->sprites->s[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->s[i]);
	else if (s_type == 10 && game->sprites->e[i] != NULL)
		mlx_destroy_image(game->mlx, game->sprites->e[i]);
}

void	destroy_sprite(char *s_name, int s_nbr, int s_type, game_data *game)
{
	char		*path;
	int			i;
	int			fd;
	int			d;

	d = BPX;
	i = -1;
	while (++i < s_nbr)
	{
		path = path_sprite(s_name, (i + 1));
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Erro.\nNao foi possivel abrir uma imagem\n");
			free(path);
			exit (EXIT_SUCCESS);
		}
		close(fd);
		aux_destroy_sprite(i, s_type, path, game);
		free(path);
	}
}

void	destroy_sprites(game_data *game)
{
	if (game->sprites != NULL)
	{
		destroy_sprite("player", 1, 1, game);
		destroy_sprite("tile_rock", 37, 2, game);
		destroy_sprite("background", 1, 5, game);
		destroy_sprite("gate", 1, 6, game);
		destroy_sprite("coin", 10, 7, game);
		destroy_sprite("scroll", 4, 8, game);
		destroy_sprite("enemy", 2, 10, game);
		free(game->sprites);
	}
}
