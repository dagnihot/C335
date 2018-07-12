	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
	movs r7, #0
	subs r6, r7, r0 // 0 - input = -input
	// if input was pos go to end, otherwise continue
	blt .END
	// move -input to input
	movs r0, r6
.END:
	pop {r4-r7}
	bx	lr
