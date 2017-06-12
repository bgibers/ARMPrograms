/**
Brendan Giberson
March 23 2016
Program 3
driver.s
**/

.text
.align 2
.global main

main:
	alpha   .req r0
	bravo   .req r1
	charlie .req r2
	temp    .req r3
	count   .req r4
	
	push {r0-r2,lr}
	sub sp, sp, #4	

	mov count, #0	@count=0 will be used as counter

	bl loop		@start the loop
loop:
	cmp count, #3	@if temp<3 keep going else done
	bge done
	
	ldr r0, =prm	@ask user to input
	bl printf	

	ldr r0, =read   @read first num
	mov r1, sp
	bl scanf
	ldr r9, [sp]

	ldr r0, =read   @read second num
        mov r1, sp
        bl scanf
        ldr r10, [sp]

	ldr r0, =read   @read third num
        mov r1, sp
        bl scanf
        ldr r11, [sp]
	
	mov alpha, r9   @put values in first three registers
	mov bravo, r10
	mov charlie, r11

	bl discrim	

	add count, #1

	bl print


print:
	ldr r0, =fmt
	bl printf
	
	mov r0,#0
	
	bl loop
done:
	.unreq alpha
	.unreq bravo
	.unreq charlie
	.unreq temp

	mov r0, #0
	add sp, sp, #4
	pop {r0-r2,pc}

	.section .rodata
	.align 2

prm:    .asciz "Please enter three values: \n"
fmt:	.asciz "The discrim is %d \n"
read:	.asciz "%d"	
