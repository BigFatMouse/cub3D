#ifndef CUB_H
# define CUB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx/mlx.h"
#include "libft/libft.h"

// #define img_width 640
// #define img_height 480
// #define map_width 24
// #define map_height 24
// #define tex_width 64
// #define tex_height 64

#define ERR_CODE_0 "Error\nMalloc error"
#define ERR_CODE_1 "Error\nЗапомните твари, я не сломаюсь"
#define ERR_CODE_2 "Error\nResolution is invalid"
#define ERR_CODE_3 "Error\nTexture or sprite file does not exist"
#define ERR_CODE_4 "Error\nColor parameter is invalid"
#define ERR_CODE_5 "Error\nMap contains forbidden symbols"
#define ERR_CODE_6 "Error\nMap is not closed"
#define ERR_CODE_7 "Error\nThere must be one player on the map"
#define ERR_CODE_8 "Error\nCan not create screenshot"
#define ERR_CODE_9 "Error\nPut one or two argument to compile"
#define ERR_CODE_10 "Error\nTo save image enter '––save' as a second argument"
#define ERR_CODE_11 "Error\nResolution too large to save image"
#define ERR_CODE_12 "Error\nScene file is invalid"
#define ERR_CODE_13 "Error\nCan't open scene file"
#define ERR_CODE_14 "Error\nTexture file must hav .xpm"


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
	char		*sprite_file;
	double		pos_x;
	double		pos_y;
	char		**map;
}				t_scene;

typedef struct	s_parce
{
	int			r;
	int			c;
	int			f;
	int			s;
	int			no;
	int			so;
	int 		we;
	int			ea;
	int			player;
	int			screenshot;
}				t_parce;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef	struct	s_var
{
	int			map_x;
	int			map_y;
	int			side;
	int			hit;
	int			line_height;
	double		delta_distx;
	double		delta_disty;
	double		side_distx;
	double		side_disty;
	double		ray_dir_x;
	double		ray_dir_y;
	double		pos_x;
	double		pos_y;
	double		perp_wall_dist;
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
	double		asp_ratio;
	double		*z_buffer;
	double		transform_x;
	double		transform_y;
	double 		sprite_x;
	double 		sprite_y;
	double 		inv_det;
	int			sprite_screen_x;
	int			sprite_heght;
	int			sprite_width;
	int			draw_start_y;
	int			draw_start_x;
	int			draw_end_y;
	int			draw_end_x;
	int			stripe;
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
	t_parce		*flags;
}				t_all;

int				key_hook(int keycode, t_all *all);
void			rotate_left_right(t_all all, int keycode);
void			move_left_rigth(t_all *all, int keycode);
void			move_back_forward(t_all *all, int keycode);
void			put_sprites(t_all all);
int				close_func(void);
void			put_scene(t_all all);
void			skip_spaces(const char **str);
int				count_params(char const *s);
void			parce_r(const char *line, t_all *all);
void			parce_tex(char *line, t_all *all);
void			parce_color(const char *line, t_all *all);
char			**make_map(t_list **head, int size);
void			parcer(int fd, t_all *all);
void			struct_flags_init(t_all *all);
void			ft_error(char *str);
unsigned int	my_mlx_pixel_take(t_data *data, int x, int y);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				close_func(void);
void			put_sprites(t_all all);
void			sort_sprites(t_all all);
void			make_screenshot(t_all	all);
int 			check_extension(char *name, char *ext);

#endif