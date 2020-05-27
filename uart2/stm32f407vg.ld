/***********************************************************************
 stm32f407vg.ld linker script
***********************************************************************/

/* memory layout for an stm32f407vg */
MEMORY
{
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
	FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 1024K
}

/* output sections */
SECTIONS
{
	/* section where program code will be stored */
	.text :
	{
		. = ALIGN(4);
		KEEP(*(.startup_sec))
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
	} > RAM

	.data : 
	{
		. = ALIGN(4);
		*(.data)
		*(.data*)
	} > RAM

	.bss :
	{
		. = ALIGN(4);
		_bss_begin = .;		
		*(.bss)
		*(.bss*)
		_bss_end = .;		
	} > RAM	

	_stack_size = 1024;
	_stack_end = ORIGIN(RAM)+LENGTH(RAM);
	_stack_begin =  _stack_end - _stack_size;
	. = _stack_begin;
	._stack :
	{
		. = . + _stack_size;
	} > RAM
} 

