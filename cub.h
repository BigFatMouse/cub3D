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

#define ERR_CODE_0 "Malloc error"
#define ERR_CODE_1 "Not valid file"

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

typedef	struct	s_scene
{
	int			i_width;
	int			i_height;
	int			m_width;
	int			m_height;
	int			ceill_color;
	int			floor_color;
	int			spr_num;
	char		*tex_north_file;
	char		*tex_south_file;
	char		*tex_west_file;
	char		*tex_east_file;
	double		pos_x;
	double		pos_y;
	int			**map;
}				t_scene;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
}				t_sprite;

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
	t_data		*texnorth_img;
	t_data		*texsouth_img;
	t_data		*texwest_img;
	t_data		*texeast_img;
	t_data		*sprite_img;
	t_mlx		*mlx;
	t_scene		*scene;
	t_var		*var;
	t_sprite	*sprite;
}				t_all;

#endif