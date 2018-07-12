
HW1.elf:     file format elf32-littlearm


Disassembly of section .init:



00008b88 <main>:
    8b88:	b510      	push	{r4, lr}
    8b8a:	2400      	movs	r4, #0
    8b8c:	2c23      	cmp	r4, #35	; 0x23
    8b8e:	dc07      	bgt.n	8ba0 <main+0x18>
    8b90:	f7ff ffb2 	bl	8af8 <stop_light>
    8b94:	1c20      	adds	r0, r4, #0
    8b96:	f000 f805 	bl	8ba4 <inc>
    8b9a:	1e04      	subs	r4, r0, #0
    8b9c:	2c23      	cmp	r4, #35	; 0x23
    8b9e:	ddf7      	ble.n	8b90 <main+0x8>
    8ba0:	bd10      	pop	{r4, pc}
    8ba2:	46c0      	nop			; (mov r8, r8)

