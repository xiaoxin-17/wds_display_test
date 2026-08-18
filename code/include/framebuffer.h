#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

void lcd_put_pixel(int x, int y, unsigned int color);
void lcd_put_ascii(int x, int y, unsigned char c);
char fb_init(void);
char fb_display(void);
char fb_deinit(void);
void fb_zc(void);

#endif