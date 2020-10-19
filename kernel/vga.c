#include "vga_test_kernelspace.h"

int
sys_init_graphics(void)
{
	c_main((volatile uint8 *)&_framebuffer);
	return 3; 
}
