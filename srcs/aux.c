/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	aux_move_enemy_2(int new_xy[2], int trig_id[2], t_game *game)
{
/* 	if (game->enemy->d <= 1)
		aux_move_enemy(1, new_xy, trig_id, game);
	if (game->enemy->d == 2)
	{
		trig_id[0] = 0;
		trig_id[1] = 3;
		aux_move_enemy(1, new_xy, trig_id, game);
	}
	if (game->enemy->d >= 3 && game->enemy->d <= 4)
	{
		trig_id[0] = 1;
		trig_id[1] = 5;
		aux_move_enemy(0, new_xy, trig_id, game);
	}
	if (game->enemy->d >= 5 && game->enemy->d <= 6)
	{
		trig_id[0] = 0;
		trig_id[1] = 7;
		aux_move_enemy(0, new_xy, trig_id, game);
	}
	trig_id[0] = 1;
	trig_id[1] = 9;
	if (game->enemy->d >= 7 && game->enemy->d <= 8)
		aux_move_enemy(1, new_xy, trig_id, game); */
}

void	aux_move_enemy_1(int new_xy[2], int trig_id[2], t_game *game)
{
/* 	if (game->enemy->d <= 1)
		aux_move_enemy(0, new_xy, trig_id, game);
	if (game->enemy->d == 2)
	{
		trig_id[0] = 0;
		trig_id[1] = 3;
		aux_move_enemy(1, new_xy, trig_id, game);
	}
	if (game->enemy->d >= 3 && game->enemy->d <= 4)
	{
		trig_id[0] = 1;
		trig_id[1] = 5;
		aux_move_enemy(1, new_xy, trig_id, game);
	}
	if (game->enemy->d >= 5 && game->enemy->d <= 6)
	{
		trig_id[0] = 0;
		trig_id[1] = 7;
		aux_move_enemy(0, new_xy, trig_id, game);
	}
	trig_id[0] = 1;
	trig_id[1] = 9;
	if (game->enemy->d >= 7 && game->enemy->d <= 8)
		aux_move_enemy(0, new_xy, trig_id, game); */
}

int	get_lines(char *map)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

void	verify_alloc(void *alloc, t_game *game)
{
	if (alloc == NULL)
	{
		free_to_all(game);
		ft_printf("Erro.\nFalha na alocação de memória.\n");
		exit(EXIT_FAILURE);
	}
}

/*
s_type = sprite_type | define se o sprite é um tile_lava, player, etc..
	1 = player
	2 = tile_rock
	3 = tile_lava
*/

// Função para converter decimal para binário e retornar como inteiro
int	decimal_para_binario(int decimal)
{
	int	binario;
	int	base;
	int	resto;

	base = 1;
	binario = 0;
	if (decimal == 0)
		return (0);
	while (decimal > 0)
	{
		resto = decimal % 2;
		binario = binario + resto * base;
		decimal = decimal / 2;
		base = base * 10;
	}
	return (binario);
}
