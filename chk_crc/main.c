#include <stdio.h>
#include <assert.h>

// pre-calculated
__uint32_t real_crc = 4294967212;

__uint32_t calc_func_crc(char* start, char* end)
{
	__uint32_t crc = 0;
	for(; start < end; ++start)
	{
		crc += *start;
	}
	return crc;
}

void __attribute__((noinline)) foo()
{
	// do something
	int a = 0;
	a++;
	a <<= 2;
}

void __attribute__((noinline)) bar()
{
	//do something
	int b = 32;
	b -= 5;
}

int main()
{
	__uint32_t crc = calc_func_crc((char*)foo, (char*)bar);
	assert(real_crc == crc);
	printf("Normally exit!\n");
	return 0;
}
