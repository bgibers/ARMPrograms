comment(' Brendan Giberson ')
comment(' CPSC 2310        ')
comment(' Program 1        ')
comment(' Jan 25 2016      ')
comment(' This program is supposed to compute the GCD of two numbers. It does this by using Euclids GCD method. In this method we subtract A-B to get the remainder. Once the remainder is determined and not equal to 0 intB becomes intA while the remainder becomes intB and the process is done again until R becomes 0. Once R is 0 than intB will be printed as the GCD')

word(intA,64)            comment('A is the dividend ')
word(intB,36)            comment('B is the divisor ')
word(rem,0)              comment('Rem is the remainder ')
word(temp,0)  		 comment('Temp var to determine whether to loop ')

label(loop)
	load(intA)
	sub(intB)
	store(rem)      comment('R=A-B ')
	
	load(rem)	comment('Loop if R-B is greater than 0 ')
	sub(intB)
	store(temp)	
	bgt0(loop)
	
label(done)
	load(rem)
	beq0(printstatement) comment('If R=0 print gcd found ')

	load(intB)       comment('B=A ')
	store(intA)
  
	load(rem)       comment('R=B ')
	store(intB)

	ba(loop)

label(printstatement)
	print(intB)
	halt

	end(loop)
