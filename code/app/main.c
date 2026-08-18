#include <framebuffer.h>
#include <disp_manager.h>



int main(int argc, char **argv)
{
	ptDIS_DATE get_dis_buf;
	Region dis_area;
	fb_zc();
	dis_set("fb");
	dis_init();
	dis_display();
	
	lcd_put_ascii(100, 100, 'A'); /*在屏幕中间显示8*16的字母A*/

	dis_area.iLeftUpX = 100;
	dis_area.iLeftUpY = 100;
	dis_area.iWidth   = 8;
	dis_area.iHeigh   = 16;

	get_dis_buf = GetDisplayBuffer();
	FlushRegion(&dis_area,get_dis_buf);
	dis_deinit();
	return 0;	
}

