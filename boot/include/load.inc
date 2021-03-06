	;boot 位置
    boot_base equ 0x7c00
    
    ;加载器位置
    loader_base equ 0x0800 ;段地址
	loader_offset equ 0x000 ;偏移地址
    loader_address equ 0x8000
    ;FAT缓冲位置
	FAT_base equ 0x1000
	FAT_offset equ 0

    ;kernel加载位置
    kernel_base equ 0x3000
	kernel_offset equ 0x0000
    kernel_address equ 0x30000
    ;GDT加载位置:0x10045  段界限 
    ;IDT加载位置：0x3000 段界限8*10=80