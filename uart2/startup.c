extern unsigned long _bss_begin;
extern unsigned long _bss_end;

extern int main(void);

__attribute__ ((section(".startup_sec")))
void startup(void)
{
	unsigned long *source;
	unsigned long *destination;

	// default zero to undefined variables
	for (destination = &_bss_begin; destination < &_bss_end;)
	{
	*(destination++) = 0;
	}
	
	// starting main program
	main();
}
