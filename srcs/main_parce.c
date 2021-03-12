int		main(int argc, char **argv)
{
	int		fd = open(argv[1], O_RDONLY);
	t_all	all;
	t_scene	scene;
	t_parce	flags;
	t_var	var;
	t_sprite	sprite;
	all.scene = &scene;
	all.flags = &flags;
	all.var = &var;
	all.sprite = &sprite;
	
	struct_flags_init(&all);
	parcer(fd, &all);
	
	printf("params:\nR %d %d\n", all.scene->i_width, all.scene->i_height);
	printf("NO %s|\n", all.scene->tex_north_file);
	printf("SO %s\n", all.scene->tex_south_file);
	printf("WE %s\n", all.scene->tex_west_file);
	printf("EA %s\n", all.scene->tex_east_file);
	printf("sprite %s\n", all.scene->sprite_file);
	printf("floor %p\n", all.scene->floor_color);
	printf("ceill %p\n", all.scene->ceill_color);
	printf("map:\n");
	int j = -1;
	parce_map(&all);
	
	char c;
	write(1, "\n", 1);
	printf("parce:\n");
	printf("all.var->dir_x: %.2f\n", all.var->dir_x);
	printf("all.var->dir_y: %.2f\n", all.var->dir_y);
	printf("all.scene->pos_x: %.2f\n", all.scene->pos_x);
	printf("all.scene->pos_y: %.2f\n", all.scene->pos_y);
	printf("all.var->plane_x: %.2f\n", all.var->plane_x);
	printf("all.var->plane_y: %.2f\n", all.var->plane_y);
	printf("all.flags->player: %d\n", all.flags->player);
	int i = 1;
	while (i < all.scene->spr_num)
	{
		printf("sprite_x%d: %.2f\n", i, all.sprite[i].x);
		printf("sprite_y%d: %.2f\n", i, all.sprite[i].y);
		i++;
	}
	//printf("all.scene->spr_num: %d", spr);
	// while (all.scene->map[++j])
	// {
	// 	int i = -1;
	// 	//c = all.scene->map[j][i];
	// 	while ((c = all.scene->map[j][++i]) != '\0')
	// 		write(1, &c, 1);
	// 	write(1, "\n", 1);
	// }
	// 	printf("%s\n", all.scene->map[j]);
	// printf("check_params: %d\n", check_params("640 -480", "0123456789 ,"));
}