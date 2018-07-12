	.text
	.syntax unified
	.thumb
	.global	regName
	.type regName, %function
regName:
	push {r4-r7}
	cmp r0, 15
	bgt .ERROR
	ldr r1, .tag
	lsls r0, #2
	ldr r0, [r1, r0]
	bal .END

.ERROR:
	movs r0, #0

.END:
	pop {r4-r7}
	bx	lr
	.align 2

.tag:
	.word names
