/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*path_sprite(char *s_name, int i)
{
	char	*nbr;
	char	*str1;
	char	*str2;

	nbr = ft_itoa(i);
	str1 = ft_strjoin("./textures/", s_name);
	str2 = ft_strjoin(str1, "/");
	if (str1 != NULL)
		free(str1);
	str1 = ft_strjoin(str2, s_name);
	if (str2 != NULL)
		free(str2);
	str2 = ft_strjoin(str1, "_");
	if (str1 != NULL)
		free(str1);
	str1 = ft_strjoin(str2, nbr);
	if (str2 != NULL)
		free(str2);
	str2 = ft_strjoin(str1, ".xpm");
	if (str1 != NULL)
		free(str1);
	if (nbr != NULL)
		free(nbr);
	return (str2);
}

static void	aux_load_sprite(int i_d[2], int s_type, char *path, t_game *game)
{
	if (s_type == 1)
		game->sprites->p[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 2)
		game->sprites->tr[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 5)
		game->sprites->bg[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 6)
		game->sprites->gt[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 7)
		game->sprites->c[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 8)
		game->sprites->s[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
	else if (s_type == 10)
		game->sprites->e[i_d[0]] = mlx_xpm_file_to_image(game->mlx, 
				path, &i_d[1], &i_d[1]);
}

void	load_sprite(char *s_name, int s_nbr, int s_type, t_game *game)
{
	char		*path;
	int			i_d[2];
	int			fd;

	i_d[1] = BPX;
	i_d[0] = -1;
	while (++i_d[0] < s_nbr)
	{
		path = path_sprite(s_name, (i_d[0] + 1));
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Erro.\nNao foi possivel abrir uma imagem\n");
			free(path);
			free_to_all(game);
			exit (EXIT_SUCCESS);
		}
		close(fd);
		aux_load_sprite(i_d, s_type, path, game);
		free(path);
	}
}

void	init_sprites(t_game *game)
{
	load_sprite("player", 1, 1, game);
	load_sprite("tile_rock", 37, 2, game);
	load_sprite("background", 1, 5, game);
	load_sprite("gate", 1, 6, game);
	load_sprite("coin", 10, 7, game);
	load_sprite("scroll", 4, 8, game);
	load_sprite("enemy", 2, 10, game);
}
