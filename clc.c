/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:23:30 by okovalov          #+#    #+#             */
/*   Updated: 2017/04/17 13:28:33 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	startprm(t_prm *param)
{
	param->rc->rayposx = param->rc->posx;
	param->rc->rayposy = param->rc->posy;
	param->rc->raydirx = param->rc->dirx + param->rc->planex
		* param->rc->camerax;
	param->rc->raydiry = param->rc->diry + param->rc->planey
		* param->rc->camerax;
	param->rc->mapx = (int)param->rc->rayposx;
	param->rc->mapy = (int)param->rc->rayposy;
	param->rc->deltadistx = sqrt(1 + (param->rc->raydiry
		* param->rc->raydiry) / (param->rc->raydirx * param->rc->raydirx));
	param->rc->deltadisty = sqrt(1 + (param->rc->raydirx
		* param->rc->raydirx) / (param->rc->raydiry * param->rc->raydiry));
	param->rc->hit = 0;
	if (param->rc->raydirx < 0)
	{
		param->rc->stepx = -1;
		param->rc->sidedistx = (param->rc->rayposx - param->rc->mapx)
			* param->rc->deltadistx;
	}
	else
	{
		param->rc->stepx = 1;
		param->rc->sidedistx = (param->rc->mapx + 1.0 - param->rc->rayposx)
			* param->rc->deltadistx;
	}
}

int		clcltprm(int texnum, t_prm *param)
{
	if (param->rc->side == 0)
		param->rc->perpwalldist = (param->rc->mapx - param->rc->rayposx
			+ (1 - param->rc->stepx) / 2) / param->rc->raydirx;
	else
		param->rc->perpwalldist = (param->rc->mapy - param->rc->rayposy
			+ (1 - param->rc->stepy) / 2) / param->rc->raydiry;
	param->rc->lineheight = (int)(SH / param->rc->perpwalldist);
	param->rc->drawstart = -param->rc->lineheight / 2 + SH / 2;
	if (param->rc->drawstart < 0)
		param->rc->drawstart = 0;
	param->rc->drawend = param->rc->lineheight / 2 + SH / 2;
	if (param->rc->drawend >= SH)
		param->rc->drawend = SH - 1;
	texnum = param->rc->wrldmap[param->rc->mapx][param->rc->mapy] - 1;
	if (param->rc->side == 0)
		param->rc->wallx = param->rc->rayposy
			+ param->rc->perpwalldist * param->rc->raydiry;
	else
		param->rc->wallx = param->rc->rayposx
			+ param->rc->perpwalldist * param->rc->raydirx;
	return (texnum);
}

void	hit(t_prm *param)
{
	if (param->rc->raydiry > 0)
	{
		param->rc->stepy = 1;
		param->rc->sidedisty = (param->rc->mapy + 1.0 - param->rc->rayposy)
			* param->rc->deltadisty;
	}
	while (param->rc->hit == 0)
	{
		if (param->rc->sidedistx < param->rc->sidedisty)
		{
			param->rc->sidedistx += param->rc->deltadistx;
			param->rc->mapx += param->rc->stepx;
			param->rc->side = 0;
		}
		else
		{
			param->rc->sidedisty += param->rc->deltadisty;
			param->rc->mapy += param->rc->stepy;
			param->rc->side = 1;
		}
		if (param->rc->wrldmap[param->rc->mapx][param->rc->mapy] > 0)
			param->rc->hit = 1;
	}
}
