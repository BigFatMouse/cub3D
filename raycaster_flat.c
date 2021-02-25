/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/02/25 20:30:04 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24


typedef struct  s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}               t_data;

typedef struct s_complex
{
	int boba;
	
	
}				t_complex;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// void		key_hook(int keycode, t_complex *complex)
// {
	// mlx_destroy_image(complex->mlx, complex->data.img);
// 	if (keycode == 12)
// 	{
// 		if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0)
// 			posX += dirX * moveSpeed;
// 		if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0)
// 			posY += dirY * moveSpeed;
// 	}
// 	if (keycode == 0)
// 	{
// 		if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0)
// 			posX -= dirX * moveSpeed;
// 		if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0)
// 			posY -= dirY * moveSpeed;
// 	}

// 	if (keycode == 1)
// 	{
// 		if(worldMap[(int)(posX + dirY * moveSpeed)][(int)(posY)] == 0)
// 			posX += dirY * moveSpeed;
// 		if(worldMap[(int)(posX)][(int)(posY - dirX * moveSpeed)] == 0)
// 			posY -= dirX * moveSpeed;

// 	}
// 	if (keycode == 2)
// 	{
// 		if(worldMap[(int)(posX - dirY * moveSpeed)][(int)(posY)] == 0)
// 			posX -= dirY * moveSpeed;
// 		if(worldMap[(int)(posX)][(int)(posY + dirX * moveSpeed)] == 0)
// 			posY += dirX * moveSpeed;
// 	}
	// complex->data.img = mlx_new_image(complex->mlx, screenWidth, screenHeight);
	// complex->data.addr = mlx_get_data_addr(complex->data.img, &complex->data.bpp, &complex->data.length, &complex->data.end);
	// ft_mlx(complex);
	// mlx_put_image_to_window(complex->mlx, complex->mlx_win, complex->data.img, 0, 0);
// }


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void		ft_mlx(t_data data)
{
	double deltaDistX;
	double deltaDistY;
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	for(int x = 0; x < screenWidth; x++)
    {
 		//calculate ray position and direction
 		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
 		double rayDirX = dirX + planeX * cameraX;
 		double rayDirY = dirY + planeY * cameraX;
 		//which box of the map we're in
 		int mapX = (int)posX;
 		int mapY = (int)posY;

		  //length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

       //length of ray from one x or y-side to next x or y-side
		                                                                                                                                                                                                                                                                                                                                                                                                                                          deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));


		double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
	if(rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if(rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}
	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(worldMap[mapX][mapY] > 0)			// запомните твари 
			hit = 1;
	}
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if(side == 0)
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
	int lineHeight = (int)(screenHeight / perpWallDist);
	
	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + screenHeight / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + screenHeight / 2;
	if(drawEnd >= screenHeight)
		drawEnd = screenHeight - 1;
	int y = 0;
	
	float moveSpeed = 0.3;
	
		while (y < screenHeight)
		{
			if (y >= drawStart && y <= drawEnd)
				my_mlx_pixel_put(&data, x, y, 0xFFFFFF);
			y++;
		}
	}
	
}

int			main(void)
{
	t_data data;
	void	*mlx;
	void	*mlx_win;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3D");
	data.img = mlx_new_image(mlx, screenWidth, screenHeight);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
	ft_mlx(data);
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	write(1, "open\n", 5);
	mlx_loop(mlx);	
}
