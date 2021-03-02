#include "cub.h"

int main()
{
    void *mlx;
    void *win;
    void *img;
    int texWidth = 64;
    int texHeight = 64;
    mlx = mlx_init();
    win = mlx_new_window(mlx, 720, 480, "Hello world!");
    img = mlx_xpm_file_to_image(mlx, "textures/bluestone.xpm", &texWidth, &texHeight);
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
}