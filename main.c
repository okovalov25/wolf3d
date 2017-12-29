/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:51:41 by okovalov          #+#    #+#             */
/*   Updated: 2017/04/17 14:00:48 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wnd(t_prm *param)
{
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, SW, SH, "wolf3D");
	param->img = mlx_new_image(param->mlx, SW, SH);
	param->line = mlx_get_data_addr(param->img, &param->bpp,
								&param->sl, &param->nd);
	textureget(param);
	clclt(param);
}

void		setprm(t_prm *param)
{
	param->flg = 0;
	param->rc->posx = 14.0;
	param->rc->posy = 12;
	param->rc->dirx = -1.0;
	param->rc->diry = 0.0;
	param->rc->planex = 0.0;
	param->rc->planey = 0.66;
	param->rc->movespeed = 0.2;
	param->rc->rotspeed = 0.1;
}

void		textureget(t_prm *param)
{
	param->txr[0].file = mlx_xpm_file_to_image(param->mlx,
							"pics/colorstone.xpm", &param->tw, &param->tw);
	param->txr[0].ln = mlx_get_data_addr(param->txr[0].file, &param->txr[0].bpp,
							&param->txr[0].sl, &param->txr[0].nd);
	param->txr[1].file = mlx_xpm_file_to_image(param->mlx,
							"pics/redbrick.xpm", &param->tw, &param->tw);
	param->txr[1].ln = mlx_get_data_addr(param->txr[1].file, &param->txr[1].bpp,
							&param->txr[1].sl, &param->txr[1].nd);
	param->txr[2].file = mlx_xpm_file_to_image(param->mlx,
							"pics/wood.xpm", &param->tw, &param->tw);
	param->txr[2].ln = mlx_get_data_addr(param->txr[2].file, &param->txr[2].bpp,
							&param->txr[2].sl, &param->txr[2].nd);
	param->txr[3].file = mlx_xpm_file_to_image(param->mlx,
							"pics/bluestone.xpm", &param->tw, &param->tw);
	param->txr[3].ln = mlx_get_data_addr(param->txr[3].file, &param->txr[3].bpp,
							&param->txr[3].sl, &param->txr[3].nd);
	param->txr[4].file = mlx_xpm_file_to_image(param->mlx,
							"pics/eagle.xpm", &param->tw, &param->tw);
	param->txr[4].ln = mlx_get_data_addr(param->txr[4].file, &param->txr[4].bpp,
							&param->txr[4].sl, &param->txr[4].nd);
	param->txr[5].file = mlx_xpm_file_to_image(param->mlx,
							"pics/greystone.xpm", &param->tw, &param->tw);
	param->txr[5].ln = mlx_get_data_addr(param->txr[5].file, &param->txr[5].bpp,
							&param->txr[5].sl, &param->txr[5].nd);
}

void		getmap(int i, char *line, t_prm *param)
{
	int		j;

	i = -1;
	while (++i < 24)
	{
		j = -1;
		while (++j < 24)
		{
			if (*line == 44)
				line++;
			if (*line == 48)
				param->rc->wrldmap[i][j] = 0;
			else if (*line == 49)
				param->rc->wrldmap[i][j] = 1;
			else if (*line == 50)
				param->rc->wrldmap[i][j] = 2;
			else if (*line == 51)
				param->rc->wrldmap[i][j] = 3;
			else if (*line == 52)
				param->rc->wrldmap[i][j] = 4;
			else if (*line == 53)
				param->rc->wrldmap[i][j] = 5;
			line++;
		}
	}
}

int			main(void)
{
	t_prm	*param;
	int		fd;
	char	*line;
	int		i;

	i = -1;
	param = (t_prm*)malloc(sizeof(t_prm));
	param->rc = (t_ray*)malloc(sizeof(t_ray));
	param->txr = (t_tr*)malloc(sizeof(t_tr) * 6);
	fd = open("map", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Need map file\n");
		return (0);
	}
	get_next_line(fd, &line);
	getmap(i, line, param);
	free(line);
	setprm(param);
	ft_putstr("Move - arrows, space - open\n");
	wnd(param);
	return (1);
}
