# include "minirt.h"

// t_color	plane_checkerboard(t_vector p)
// {
// 	double	u;
// 	double	v;

// 	u = fract(p.x * 0.2);
// 	v = fract(p.y * 0.2);
// 	if (u > 0.5)
// 	{
// 		if (v > 0.5)
// 			return (new_vec(1.0, 1.0, 1.0));
// 		return (new_vec(0.0, 0.0, 0.0));
// 	}
// 	else
// 	{
// 		if (v < 0.5)
// 			return (new_vec(1.0, 1.0, 1.0));
// 		return (new_vec(0.0, 0.0, 0.0));
// 	}
// }

unsigned char	*get_bmp_addr(char *path, int *w, int *h)
{
	int bmpFile = open(path, O_RDONLY);
	// if (bmpFile == -1)
	// {
	// 	perror("Error opening file");
	// 	return 1;
	// }

	BMPHeader header;

	read(bmpFile, &header, sizeof(BMPHeader));
	// if (read(bmpFile, &header, sizeof(BMPHeader)) != sizeof(BMPHeader))
	// {
	// 	perror("Error reading BMP header");
	// 	close(bmpFile);
	// 	return 1;
	// }

	uint32_t imageDataSize = header.dataSize != 0 ? header.dataSize : header.fileSize - header.dataOffset;
	uint8_t *imageData = (uint8_t *)malloc(imageDataSize);

	// if (imageData == NULL)
	// {
	// 	perror("Error allocating memory");
	// 	close(bmpFile);
	// 	return 1;
	// }
	*w = header.width;
	*h = header.height;

	read(bmpFile, imageData, imageDataSize);

	// Assuming 24 bits per pixel (BGR order)
	// int width = header.width;
	// int height = header.height;

	// for (int y = height - 1; y >= 0; y--)
	// {
	// 	for (int x = 0; x < width; x++)
	// 	{
	// 		int index = (x + y * width) * 3;
	// 		uint8_t blue = imageData[index];
	// 		uint8_t green = imageData[index + 1];
	// 		uint8_t red = imageData[index + 2];

	// 		// Use the RGB values as needed
	// 		printf("Pixel at (%d, %d): R=%d, G=%d, B=%d\n", x, y, red, green, blue);
	// 	}
	// }

	// free(imageData);
	close(bmpFile);
	return (imageData);
}

t_color	plane_texture(t_vector p, t_hit_array* pl)
{
	double	u;
	double	v;

	u = fract(p.x * 0.2);
	v = fract(p.y * 0.2);
	int	x = (int)(pl->texture_w * u);
	int	y = (int)(pl->texture_h * v);
	int	index = (x + y * pl->texture_w) * 3;
	return (new_color(pl->texture_addr[index + 2] / 255.0, pl->texture_addr[index + 1] / 255.0, pl->texture_addr[index] / 255.0));
}

t_color	shpere_texture(t_vector p, t_hit_array* sp)
{
	double	u;
	double	v;
	double	theta = acos(-p.y);
	double	phi = atan2(-p.z, p.x) + M_PI;

	u = phi / (2 * M_PI);
	v = theta / M_PI;
	int	x = (int)(sp->texture_w * u);
	int	y = (int)(sp->texture_h * v);
	int	index = (x + y * sp->texture_w) * 3;
	return (new_color(sp->texture_addr[index + 2] / 255.0, sp->texture_addr[index + 1] / 255.0, sp->texture_addr[index] / 255.0));
}
