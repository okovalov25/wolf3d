/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:16:12 by okovalov          #+#    #+#             */
/*   Updated: 2017/04/17 13:42:03 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <mlx.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <math.h>
# define SW 1280
# define SH 800

typedef struct		s_raycast
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	int			wrldmap[24][24];
	double		movespeed;
	double		rotspeed;
	double		planex;
	double		planey;
	double		sidedistx;
	double		sidedisty;
	double		perpwalldist;
	int			hit;
	int			stepx;
	int			stepy;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			mapx;
	int			mapy;
	double		raydirx;
	double		raydiry;
	double		camerax;
	double		rayposx;
	double		rayposy;
	double		deltadistx;
	double		deltadisty;
	int			texx;
	int			texy;
	double		floorxwall;
	double		floorywall;
	double		distwall;
	double		distplayer;
	double		currentdist;
	double		weight;
	double		currentfloorx;
	double		currentfloory;
	int			floortexx;
	int			floortexy;
}					t_ray;

typedef struct		s_txtr
{
	char		*ln;
	void		*file;
	int			bpp;
	int			sl;
	int			nd;
}					t_tr;

typedef struct		s_allparm
{
	void		*mlx;
	void		*win;
	void		*img;
	int			bpp;
	int			sl;
	int			nd;
	char		*line;
	int			color;
	char		r;
	char		g;
	char		b;
	t_ray		*rc;
	t_tr		*txr;
	int			tw;
	int			flg;
}					t_prm;

void				textureget(t_prm *param);
void				wnd(t_prm *param);
void				clclt(t_prm *param);
void				clr(t_prm *param);
int					key(int keycode, t_prm *param);
int					exit_x(void *par);
void				getmap(int i, char *line, t_prm *param);
void				setprm(t_prm *param);
void				moovex(int keycode, t_prm *param);
void				moovey(int keycode, t_prm *param);
void				moovexm(t_prm *param);
void				key2(t_prm *param);
void				floordrw(int x, int y, t_prm *param);
void				floorcl(int x, int y, t_prm *param);
void				walldrw(int texnum, int x, int y, t_prm *param);
void				startprm(t_prm *param);
int					clcltprm(int texnum, t_prm *param);
void				hit(t_prm *param);

#endif
