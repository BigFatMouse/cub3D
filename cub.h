#ifndef CUB_H
# define CUB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx/mlx.h"

#define img_width 640
#define img_height 480
#define map_width 24
#define map_height 24
#define tex_width 64
#define tex_height 64

typedef struct  s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}               t_mlx;

typedef struct  s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}               t_data;

typedef	struct	s_parce
{
	int			m_width;
	int			m_height;
}				t_parce;

typedef	struct	s_var
{
	int			map_x;
	int			map_y;
	int			side;
	int			hit;
	double		delta_distx;
	double		delta_disty;
	double		side_distx;
	double		side_disty;
	double		ray_dirx;
	double		ray_diry;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		step_x;
	double		step_y;
	double		draw_start;
	double		draw_end;
	double		plane_x;
	double		plane_y;
	double		old_dir_x;
	double		old_plane_x;
	double		move_speed;
	double		rot_speed;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double		step;	
}				t_var;

typedef struct	s_all
{
	t_data		*data;
	t_data		*tex_north;
	t_data		*tex_south;
	t_data		*tex_west;
	t_data		*tex_east;
	t_mlx		*mlx;
	t_parce		*parce;
	t_var		*var;
}				t_all;

#endif