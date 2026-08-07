#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <framebuffer.h>

static int fd_fb;
static struct fb_var_screeninfo var;	/* Current var */
static int screen_size;
static unsigned char *fb_base;
static unsigned int line_width;
static unsigned int pixel_width;

/**********************************************************************
 * 函数名称： lcd_put_pixel
 * 功能描述： 在LCD指定位置上输出指定颜色（描点）
 * 输入参数： x坐标，y坐标，颜色
 * 输出参数： 无
 * 返 回 值： 会
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/05/12	     V1.0	  zh(angenao)	      创建
 ***********************************************************************/ 
void lcd_put_pixel(int x, int y, unsigned int color)
{
	unsigned char *pen_8 = fb_base+y*line_width+x*pixel_width;
	unsigned short *pen_16;	
	unsigned int *pen_32;	

	unsigned int red, green, blue;	

	pen_16 = (unsigned short *)pen_8;
	pen_32 = (unsigned int *)pen_8;

	switch (var.bits_per_pixel)
	{
		case 8:
		{
			*pen_8 = color;
			break;
		}
		case 16:
		{
			/* 565 */
			red   = (color >> 16) & 0xff;
			green = (color >> 8) & 0xff;
			blue  = (color >> 0) & 0xff;
			color = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
			*pen_16 = color;
			break;
		}
		case 32:
		{
			*pen_32 = color;
			break;
		}
		default:
		{
			printf("can't surport %dbpp\n", var.bits_per_pixel);
			break;
		}
	}
}

char fb_init(void)
{
	// 打开Framebuffer设备节点，读写方式操作LCD显存
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}

	// ioctl获取fb可变屏幕信息：分辨率、色深(bits_per_pixel)
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}

	// 每行字节数 = 水平分辨率 × 每个像素bit数 / 8
	line_width  = var.xres * var.bits_per_pixel / 8;
	// 单个像素占用多少字节，例如24bit：3字节；32bit：4字节
	pixel_width = var.bits_per_pixel / 8;
	// 整个显存总字节大小
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;

	// mmap映射fb设备到用户态虚拟地址，直接操作显存，不需要read/write系统调用
	// MAP_SHARED：用户空间修改同步到硬件显存
	fb_base = (unsigned char *)mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if (fb_base == (unsigned char *)-1)
	{
		printf("can't mmap\n");
		return -1;
	}

	/* 清屏: 全部设为白色，0xff全字节置1 */
	memset(fb_base, 0xff, screen_size);

	return -1;
}

char fb_display(void)
{
	int i;
	/* 清屏: 全部设为白色，0xff全字节置1 */
	memset(fb_base, 0xff, screen_size);

	/* 在屏幕中间画一条横线，100个红色像素点 */
	for (i = 0; i < 100; i++)
		lcd_put_pixel(var.xres/2+i, var.yres/2, 0xFF0000);
	
	return -1;

}
char fb_deinit(void)
{
	// 解除内存映射
	munmap(fb_base , screen_size);
	// 关闭fb设备文件描述符
	close(fd_fb);
	
	return 0;	
}
