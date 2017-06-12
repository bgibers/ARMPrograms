/**
Brendan Giberson
March 23 2016
CPSC 2310
Program 3
**/

.file "discrim.s"
.text
.align 2
.global discrim
.type   discrim, %function

/** This function will return the discrim of a b and c
b^2-4ac
  **/

discrim:
  
alpha    .req r0
bravo    .req r1
charlie  .req r2
temp     .req r3

	push {r3, lr}
	


        mov temp, bravo            @temp=b
	mul bravo, temp, bravo     @b=b*b
	mov temp, #4               @temp=4
	mul alpha, temp, alpha     @a=a*4
	mul alpha, charlie, alpha  @a=a*c
	sub bravo, alpha           @b=b-a

	mov r0,bravo

	pop {r3, pc}
   	
