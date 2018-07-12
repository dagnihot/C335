//Dhruv Agnihotri
//C335
//HW 4

	.text
	.syntax unified
	.thumb
	.global	multby5	
	.type multby5, %function
multby5:
	push {r4-r7}
	movs r1, r0
	lsls r0, #2 // mult by 4
	adds r0, r1 // add orig
.END:
	pop {r4-r7}
	bx	lr
