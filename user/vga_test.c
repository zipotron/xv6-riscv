#include "kernel/types.h"
#include "kernel/syscall.h"
//#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
	int a = init_graphics();
	printf("vga driver answer: %d\n", a);
	exit(0);
}
