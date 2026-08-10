#include <framebuffer.h>
#include <disp_manager.h>



int main(int argc, char **argv)
{
	fb_zc();
	dis_set("fb");
	dis_init();
	dis_display();
	dis_deinit();
	return 0;	
}

