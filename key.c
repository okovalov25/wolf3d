/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:27:37 by okovalov          #+#    #+#             */
/*   Updated: 2017/04/17 12:01:51 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		key2(t_prm *param)
{
	if (param->flg == 1 && (((int)param->rc->posx == 4
			&& (int)param->rc->posy == 12) || ((int)param->rc->posx == 6
			&& (int)param->rc->posy == 12)))
	{
		if (param->rc->wrldmap[5][12] == 5)
			param->rc->wrldmap[5][12] = 0;
		else
			param->rc->wrldmap[5][12] = 5;
	}
	else if (param->flg == 0 && (int)param->rc->posx == 21
			&& (int)param->rc->posy == 11)
	{
		param->flg = 1;
		param->rc->wrldmap[22][11] = 4;
	}
}

int			key(int keycode, t_prm *param)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == 49)
	{
		if (((int)param->rc->posx == 9 && (int)param->rc->posy == 6)
				|| ((int)param->rc->posx == 7 && (int)param->rc->posy == 6))
		{
			if (param->rc->wrldmap[8][6] == 3)
				param->rc->wrldmap[8][6] = 0;
			else
				param->rc->wrldmap[8][6] = 3;
		}
		else if (((int)param->rc->posx == 7 && (int)param->rc->posy == 17)
				|| ((int)param->rc->posx == 9 && (int)param->rc->posy == 17))
		{
			if (param->rc->wrldmap[8][17] == 3)
				param->rc->wrldmap[8][17] = 0;
			else
				param->rc->wrldmap[8][17] = 3;
		}
		key2(param);
	}
	moovey(keycode, param);
	moovex(keycode, param);
	return (1);
}

void		moovey(int keycode, t_prm *param)
{
	if (keycode == 126)
	{
		if (!(param->rc->wrldmap[(int)(param->rc->posx + param->rc->dirx
							* param->rc->movespeed)][(int)(param->rc->posy)]))
			param->rc->posx += param->rc->dirx * param->rc->movespeed;
		if (!(param->rc->wrldmap[(int)(param->rc->posx)][(int)(param->rc->posy
				+ param->rc->diry * param->rc->movespeed)]))
			param->rc->posy += param->rc->diry * param->rc->movespeed;
	}
	else if (keycode == 125)
	{
		if (!(param->rc->wrldmap[(int)(param->rc->posx - param->rc->dirx
							* param->rc->movespeed)][(int)(param->rc->posy)]))
			param->rc->posx -= param->rc->dirx * param->rc->movespeed;
		if (!(param->rc->wrldmap[(int)(param->rc->posx)][(int)(param->rc->posy
				- param->rc->diry * param->rc->movespeed)]))
			param->rc->posy -= param->rc->diry * param->rc->movespeed;
	}
}

void		moovexm(t_prm *param)
{
	double	olddirx;
	double	oldplanex;

	olddirx = param->rc->dirx;
	oldplanex = param->rc->planex;
	{
		param->rc->dirx = param->rc->dirx * cos(-param->rc->rotspeed)
			- param->rc->diry * sin(-param->rc->rotspeed);
		param->rc->diry = olddirx * sin(-param->rc->rotspeed)
			+ param->rc->diry * cos(-param->rc->rotspeed);
		param->rc->planex = param->rc->planex * cos(-param->rc->rotspeed)
			- param->rc->planey * sin(-param->rc->rotspeed);
		param->rc->planey = oldplanex * sin(-param->rc->rotspeed)
			+ param->rc->planey * cos(-param->rc->rotspeed);
	}
}

void		moovex(int keycode, t_prm *param)
{
	double	olddirx;
	double	oldplanex;

	olddirx = param->rc->dirx;
	oldplanex = param->rc->planex;
	if (keycode == 123)
	{
		param->rc->dirx = param->rc->dirx * cos(param->rc->rotspeed)
			- param->rc->diry * sin(param->rc->rotspeed);
		param->rc->diry = olddirx * sin(param->rc->rotspeed)
			+ param->rc->diry * cos(param->rc->rotspeed);
		param->rc->planex = param->rc->planex * cos(param->rc->rotspeed)
			- param->rc->planey * sin(param->rc->rotspeed);
		param->rc->planey = oldplanex * sin(param->rc->rotspeed)
			+ param->rc->planey * cos(param->rc->rotspeed);
	}
	else if (keycode == 124)
		moovexm(param);
	mlx_destroy_image(param->mlx, param->img);
	param->img = mlx_new_image(param->mlx, SW, SH);
	param->line = mlx_get_data_addr(param->img,
						&param->bpp, &param->sl, &param->nd);
	clclt(param);
}
