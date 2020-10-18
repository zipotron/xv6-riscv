extern void initVGA();
int
sys_init_graphics(void)
{
	initVGA();
	return 3; 
}
