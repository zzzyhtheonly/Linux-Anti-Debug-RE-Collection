#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/dirent.h>

#include "headers.h"

inline void real_write_cr0(unsigned long cr0)
{
	asm volatile(
			"mov %0, %%cr0":
			"+r"(cr0),
			"+m"(__force_order));

}

void disable_wp(void)
{
	unsigned long cr0 = read_cr0();
	clear_bit(16, &cr0);
	real_write_cr0(cr0);
}

void enable_wp(void)
{
	unsigned long cr0 = read_cr0();
	set_bit(16, &cr0);
	real_write_cr0(cr0);
}
