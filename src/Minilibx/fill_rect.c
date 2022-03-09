#include "minilibx.h"

void    fill_rect(t_texture *texture, t_color color)
{
    int     		i;
    int     		j;
    unsigned char	*pixel;

    i = 0;
    while (i < texture->rect.h)
    {
        j = 0;
        while (j < texture->rect.w)
        {
            pixel = texture->addr + (i * texture->line_length
                + j * (texture->bits_per_pixel / 8));
            if (texture->endian)
            {
                pixel[0] = 0;
                pixel[1] = color.r;
                pixel[2] = color.g;
                pixel[3] = color.b;
            }
            else
            {
                pixel[0] = color.b;
                pixel[1] = color.g;
                pixel[2] = color.r;
                pixel[3] = 0;
            }
            j++;
        }
        i++;
    }
}
