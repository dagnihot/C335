	.text
	.syntax unified
	.thumb
	.global	max_array
	.type max_array, %function
max_array:
	push {r4-r7}
	movs r2, #0
	movs r3, #0
	.MAX:
	cmp r1, #0
	beq .END
	ldr r4, [r0, r3]
	adds r3, #4
	subs r1, #1
	cmp r2, r4
	bgt .MAX
	movs r2, r4
	bal .MAX
	.END:
	movs r0, r2
	pop {r4-r7}
	bx	lr