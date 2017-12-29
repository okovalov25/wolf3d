/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:14:49 by okovalov          #+#    #+#             */
/*   Updated: 2017/04/17 14:18:12 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void		clclt(t_prm *param)
{
	int		x;
	int		y;
	int		texnum;

	x = -1;
	y = 0;
	while (++x < SW)
	{
		param->rc->camerax = 2 * x / (double)SW - 1;
		startprm(param);
		if (param->rc->raydiry < 0)
		{
			param->rc->stepy = -1;
			param->rc->sidedisty = (param->rc->rayposy - param->rc->mapy)
				* param->rc->deltadisty;
		}
		hit(param);
		texnum = clcltprm(texnum, param);
		walldrw(texnum, x, y, param);
		floorcl(x, y, param);
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	mlx_hook(param->win, 2, 5, key, param);
	mlx_hook(param->win, 17, 1L << 17, exit_x, param);
	mlx_loop(param->mlx);
}

void		walldrw(int texnum, int x, int y, t_prm *param)
{
	int		d;

	param->rc->wallx -= floor((param->rc->wallx));
	param->rc->texx = (int)(param->rc->wallx * (double)(param->tw));
	if (param->rc->side == 0 && param->rc->raydirx > 0)
		param->rc->texx = param->tw - param->rc->texx - 1;
	if (param->rc->side == 1 && param->rc->raydiry < 0)
		param->rc->texx = param->tw - param->rc->texx - 1;
	y = param->rc->drawstart;
	while (y < param->rc->drawend)
	{
		d = y * 256 - SH * 128 + param->rc->lineheight * 128;
		param->rc->texy = ((d * param->tw) / param->rc->lineheight) / 256;
		param->line[4 * (SW * y + x)] = param->txr[texnum].ln[4
			* (param->tw * param->rc->texy + param->rc->texx)];
		param->line[(4 * (SW * y + x)) + 1] = param->txr[texnum].ln[(4
			* (param->tw * param->rc->texy + param->rc->texx)) + 1];
		param->line[(4 * (SW * y + x)) + 2] = param->txr[texnum].ln[(4
			* (param->tw * param->rc->texy + param->rc->texx)) + 2];
		y++;
	}
}

void		floordrw(int x, int y, t_prm *param)
{
	y = param->rc->drawend + 1;
	while (y < SH)
	{
		param->rc->currentdist = SH / (2.0 * y - SH);
		param->rc->weight = (param->rc->currentdist - param->rc->distplayer)
			/ (param->rc->distwall - param->rc->distplayer);
		param->rc->currentfloorx = param->rc->weight * param->rc->floorxwall
			+ (1.0 - param->rc->weight) * param->rc->posx;
		param->rc->currentfloory = param->rc->weight * param->rc->floorywall
			+ (1.0 - param->rc->weight) * param->rc->posy;
		param->rc->floortexx = (int)(param->rc->currentfloorx
			* param->tw) % param->tw;
		param->rc->floortexy = (int)(param->rc->currentfloory
			* param->tw) % param->tw;
		param->line[4 * (SW * y + x)] = (param->txr[5].ln[4 * (param->tw
		* param->rc->floortexy + param->rc->floortexx)] >> 1) & 8355711;
		param->line[(4 * (SW * y + x)) + 1] = (param->txr[5].ln[(4 * (param->tw
		* param->rc->floortexy + param->rc->floortexx)) + 1] >> 1) & 8355711;
		param->line[(4 * (SW * y + x)) + 2] = (param->txr[5].ln[(4 * (param->tw
		* param->rc->floortexy + param->rc->floortexx)) + 2] >> 1) & 8355711;
		param->line[4 * (SW * (SH - y) + x)] = 200;
		param->line[(4 * (SW * (SH - y) + x)) + 1] = 200;
		param->line[(4 * (SW * (SH - y) + x)) + 2] = 200;
		y++;
	}
}

void		floorcl(int x, int y, t_prm *param)
{
	if (param->rc->side == 0 && param->rc->raydirx > 0)
	{
		param->rc->floorxwall = param->rc->mapx;
		param->rc->floorywall = param->rc->mapy + param->rc->wallx;
	}
	else if (param->rc->side == 0 && param->rc->raydirx < 0)
	{
		param->rc->floorxwall = param->rc->mapx + 1.0;
		param->rc->floorywall = param->rc->mapy + param->rc->wallx;
	}
	else if (param->rc->side == 1 && param->rc->raydiry > 0)
	{
		param->rc->floorxwall = param->rc->mapx + param->rc->wallx;
		param->rc->floorywall = param->rc->mapy;
	}
	else
	{
		param->rc->floorxwall = param->rc->mapx + param->rc->wallx;
		param->rc->floorywall = param->rc->mapy + 1.0;
	}
	param->rc->distwall = param->rc->perpwalldist;
	param->rc->distplayer = 0.0;
	if (param->rc->drawend < 0)
		param->rc->drawend = SH;
	floordrw(x, y, param);
}
