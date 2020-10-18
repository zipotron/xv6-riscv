#include "kernel/vga_test_kernelspace.h"
#include "types.h"

typedef uint32 uint32_t;
extern volatile uint8 *VRAM;

int mandelbrot(float cr, float ci)
{
	uint32_t reps = 0;
	float zr = 0.0f;
	float zi = 0.0f;
	for ( ; reps < 256; reps++ ) {
		float tr = zr*zr - zi*zi;
		float ti = 2.0f*zr*zi;
		zr = tr + cr;
		zi = ti + ci;
		if ( zr*zr + zi*zi >= 2.0f*2.0f ) {
			break;
		}
	}
	return reps;
}

void c_main(void)
{
	float zoom = 4.0f;
	for (int xx=0;xx<200;xx++) {
		float ci_delta = zoom/200.0f;
		float cr_delta = zoom/200.0f;
		float initial_cr = -0.598f + cr_delta*-160;
		float initial_ci = -0.665f + ci_delta*-100;

		// Do initial render
		{
			float ci = initial_ci;
			for ( uint32_t y = 0; y < 200; y += 4 ) {
				float cr = initial_cr;
				for ( uint32_t x = 0; x < 320; x += 4 ) {
					int reps = mandelbrot(cr, ci);
					VRAM[y*320+x] = reps;
					cr += cr_delta*4;
				}
				ci += ci_delta*4;
			}
		}

#if 0
		// Fill in horizontally 8->4
		{
			float ci = initial_ci;
			for ( uint32_t y = 0, i = 0; y < 200; y += 8 ) {
				float cr = initial_cr+ci_delta*4;
				for ( uint32_t x = 0; x < 320; x += 8 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (x+8 >= 320 ? r0+1 : VRAM[(y+0)*320+(x+8)]);
					if ( r0 != r1 ) {
						VRAM[(y+0)*320+(x+4)] = reps;
					} else {
						VRAM[(y+0)*320+(x+4)] = r0;
					}
					cr += cr_delta*8;
				}
				ci += ci_delta*8;
			}
		}

		// Fill in vertically 8->4
		{
			float ci = initial_ci+cr_delta*4;
			for ( uint32_t y = 0, i = 0; y < 200; y += 8 ) {
				float cr = initial_cr;
				for ( uint32_t x = 0; x < 320; x += 4 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (y+8 >= 200 ? r0+1 : VRAM[(y+8)*320+(x+0)]);
					if ( r0 != r1 ) {
						VRAM[(y+4)*320+(x+0)] = reps;
					} else {
						VRAM[(y+4)*320+(x+0)] = r0;
					}
					cr += cr_delta*4;
				}
				ci += ci_delta*8;
			}
		}
#endif

		// Fill in horizontally 4->2
		{
			float ci = initial_ci;
			for ( uint32_t y = 0; y < 200; y += 4 ) {
				float cr = initial_cr+ci_delta*2;
				for ( uint32_t x = 0; x < 320; x += 4 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (x+4 >= 320 ? r0+1 : VRAM[(y+0)*320+(x+4)]);
					if ( r0 != r1 ) {
						VRAM[(y+0)*320+(x+2)] = reps;
					} else {
						VRAM[(y+0)*320+(x+2)] = r0;
					}
					cr += cr_delta*4;
				}
				ci += ci_delta*4;
			}
		}

		// Fill in vertically 4->2
		{
			float ci = initial_ci+cr_delta*2;
			for ( uint32_t y = 0; y < 200; y += 4 ) {
				float cr = initial_cr;
				for ( uint32_t x = 0; x < 320; x += 2 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (y+4 >= 200 ? r0+1 : VRAM[(y+4)*320+(x+0)]);
					if ( r0 != r1 ) {
						VRAM[(y+2)*320+(x+0)] = reps;
					} else {
						VRAM[(y+2)*320+(x+0)] = r0;
					}
					cr += cr_delta*2;
				}
				ci += ci_delta*4;
			}
		}

		// Fill in horizontally 2->1
		{
			float ci = initial_ci;
			for ( uint32_t y = 0; y < 200; y += 2 ) {
				float cr = initial_cr+cr_delta;
				for ( uint32_t x = 0; x < 320; x += 2 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (x+2 >= 320 ? r0+1 : VRAM[(y+0)*320+(x+2)]);
					if ( r0 != r1 ) {
						VRAM[(y+0)*320+(x+1)] = reps;
					} else {
						VRAM[(y+0)*320+(x+1)] = r0;
					}
					cr += cr_delta*2;
				}
				ci += ci_delta*2;
			}
		}

		// Fill in vertically 2->1
		{
			float ci = initial_ci+ci_delta;
			for ( uint32_t y = 0; y < 200; y += 2 ) {
				float cr = initial_cr;
				for ( uint32_t x = 0; x < 320; x += 1 ) {
					int reps = mandelbrot(cr, ci);
					int r0 = VRAM[(y+0)*320+(x+0)];
					int r1 = (y+2 >= 200 ? r0+1 : VRAM[(y+2)*320+(x+0)]);
					if ( r0 != r1 ) {
						VRAM[(y+1)*320+(x+0)] = reps;
					} else {
						VRAM[(y+1)*320+(x+0)] = r0;
					}
					cr += cr_delta;
				}
				ci += ci_delta*2;
			}
		}

		zoom *= 0.99f;
	}
}
