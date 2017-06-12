//Brendan Giberson
//Bgibers
//CPSC 2310-01
//April 14 2016
//Program 4
//The purpose of this program is to print the values of 8-bit floating point values and show steps required in adding two floating point values

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;

/*
	THIS PROGRAM MUST COMPILE WITH C++ 11
*/
int finalGuard[2];
int finalbin[8];
//this function prints the internal rep of the two values
void print_internal(double fraction1, double fraction2, int exponent1, 
		    int exponent2, int guard1[], int guard2[])
{
	//internal rep of values
        printf("internal rep of first value:    %.4f %d%d x 2^(%d)\n",
                                      fraction1,guard1[0],guard1[1],exponent1);
        printf("internal rep of second value:   %.4f %d%d x 2^(%d)\n",
                                      fraction2,guard2[0],guard2[1],exponent2);
}

//this function will convert the binary significand to the decimal significand
double get_decsig(int binary_array[])
{
	int fraction_array[4];
	double dec_sig =0;

	fraction_array[0]=binary_array[3];
	fraction_array[1]=binary_array[2];
	fraction_array[2]=binary_array[1];
        fraction_array[3]=binary_array[0];

	if(fraction_array[0] == 1) dec_sig += .5;
        if(fraction_array[1] == 1) dec_sig += .25;
        if(fraction_array[2] == 1) dec_sig += .125;
        if(fraction_array[3] == 1) dec_sig += .0625;
	
	return dec_sig;
	
}

//this function takes in a binary array extracts the 3 bit exponent and returns the appropriate exponent
int get_exponent(int binary_array[])
{
	int exponent_array[3];
	string exponent;

        exponent_array[0]= binary_array[6];
        exponent_array[1]= binary_array[5];
	exponent_array[2]= binary_array[4];

	std::stringstream ss;
	for(int i=0;i<3;i++)
	{
		ss << exponent_array[i];
	}

	ss >> exponent;

	 if(exponent == "001")
        {
                int returned= 1;
             
                return returned;
        }

	else if(exponent == "010")
        {       
                int returned= 2;
                
                return returned;
        }

	else if(exponent == "011")
        {       
                int returned= 3;
                
                return returned;
        }

	else if(exponent == "100")
        {       
                int returned= 4;
                
                return returned;
        }

	else if(exponent == "101")
        {       
                int returned= 5;
                
                return returned;
        }

	else if(exponent == "110")
        {       
                int returned= 6;
                
                return returned;
        }

	else if(exponent == "111")
        {       
                int returned= 7;
                
                return returned;
        }

	else
		cout << "Error exponent not in range (-3) - (3)" << endl;
		exit(EXIT_FAILURE);
}

//the purpose of this function is to perform twos complement on the value passed in
double twoscomp(double passIn)
{
	string store= to_string(passIn);
        char frac_array[6];
        std::strcpy(frac_array, store.c_str());
	int keepGoing=1;

	for(int i=5;i>-1;i--)
	{
		if(frac_array[i] == '0')
			frac_array[i]='1';

		else if(frac_array[i] == '1')
			frac_array[i]='0';

		else if(frac_array[i] == '.')
			frac_array[i]= '.'; 
	}	

	int i=5;
	while(keepGoing == 1)
	{
		if(frac_array[i] == '0')
		{
			frac_array[i] = '1';
			keepGoing=0;
		}
		else if(frac_array[i] == '1')
		{
			frac_array[i] = '0';
			i--;
			keepGoing=1;
		}
		
	}

	passIn=std::stod (frac_array);
//	cout << passIn << endl;
	return passIn;
}	

double addition(double returned,double fraction1, double fraction2,int guard1[],int guard2[])
{
	//put fraction1 and 2 into arrays to compare
	string store= to_string(fraction1);
	string store1= to_string(fraction2);
        char frac_array1[7];
	char frac_array2[7];
	char summed_array[7]={0};
        std::strcpy(frac_array1, store.c_str());
	std::strcpy(frac_array2, store1.c_str());
	


	//add the values
	for(int i=6;i>-1;i--)
	{
		if(frac_array1[i] == '.' && frac_array2[i] == '.' )
		{
			summed_array[i]= '.';
		}

		else if(frac_array1[i] == '1' && frac_array2[i] == '1')
                {
                        summed_array[i]='2';
                }

		else if(frac_array1[i] == '1' || frac_array2[i] == '1')  
		{
			summed_array[i]='1';
		}

		else if(frac_array1[i] == '0' && frac_array2[i] == '0')
		{
			summed_array[i]='0';
		}  

		
	
	}

	for(int i=6;i>-1;i--)
	{
		if(summed_array[i]=='2')
		{
			summed_array[i]='0';
			if(summed_array[i-1] == '1')
			{
				summed_array[i-1]='2';
			}
			else if(summed_array[i-1]=='2')
			{
				summed_array[i-1]='3';
			}
			else
				summed_array[i-1]='1';
		}
	
		else if(summed_array[i]=='3')
		{
			summed_array[i]='1';
			if(summed_array[i-1] == '1')
                        {
                                summed_array[i-1]='2';
                        }
                        else if(summed_array[i-1]=='2')
                        {
                                summed_array[i-1]='3';
                        }
                        else
                                summed_array[i-1]='1';
		}
	
		else if(summed_array[i]=='1')
		{
			summed_array[i]='1';
		}
	
		else if(summed_array[i] =='0')
		{
			summed_array[i]='0';
		}
	}
	
		if(guard1[0] == 1 && guard2[0] == 1)
		{
			finalGuard[0]=0;
			finalGuard[1]=1;
		}

		else if((guard1[0] == 1 && guard2[0] == 0) || (guard2[0] == 1 &&
				guard1[0]==0))
		{
			finalGuard[0]=1;
		}

		if(finalGuard[1] != 1 || (guard1[1] == 1 && guard2[1] == 0) ||
 			(guard2[1] == 1 && guard1[1]==0))
		{
			finalGuard[1]=1;	
		}

		else
			finalGuard[0]=0;
			finalGuard[1]=0;

	
	finalbin[3]=summed_array[3];
	finalbin[2]=summed_array[2];
	finalbin[1]=summed_array[1];
	finalbin[0]=summed_array[0];

	returned= atof (summed_array);
	return returned;
}

int main()
{
	//declare variables
	int val_1, val_2; //read in values 0-255 will be stored here
	int binary1[8];   //storage of binary numbers(they are stored backwords)
	int binary2[8];
	std::stringstream ss;  //for string conversion 1
	std::stringstream ss2; //for string conversion 2
	string fraction1_str, fraction2_str; //fraction values as strings
	double fraction1, fraction2;	
	int guard1[2];
	guard1[0]=0;
	guard1[1]=0;
	int guard2[2];
	guard2[0]=0;
	guard2[1]=0;	

	//read in values
	cout << "Please input first value: ";
	cin >> val_1;
	cout << "Pleae input second value: ";
	cin >> val_2;
	
	if(val_1 <0 || val_1 >255 || val_2 <0 || val_2 >255)
	{
		cout << "Please enter between values in range 0-255\n" ;
		exit(EXIT_FAILURE);
	}

	//convert values to binary and store in array of ints
	for(int i=0; i < 8; ++i)
	{
		binary1[i]= val_1 & (1 << i) ? 1 : 0;
		binary2[i]= val_2 & (1 << i) ? 1 : 0;
	}

	cout << "\nencoding of first value:       " ;
	for(int i=7; i>-1; i--)
	{
		cout << binary1[i];
	}
	cout << "\nencoding of second value:      " ;
	 for(int i=7; i>-1; i--)
        {
                cout << binary2[i];
        }
	cout << "\n\n" ;

	//concate array values 4-8 to extract fraction as string. Add one and convert the values to doubles
	for(int i=3; i > -1; i--)
	{
		ss << binary1[i];
	}
	
	ss >> fraction1_str;
	fraction1_str.insert(0,"1."); //add 1 to the fraction
	fraction1= atof(fraction1_str.c_str());	//change the string to a double

	for(int i=3; i > -1; i--)
        {
                ss2 << binary2[i];
        }

        ss2 >> fraction2_str;
	fraction2_str.insert(0,"1.");
	fraction2= atof(fraction2_str.c_str());

	//determine exponents (save a copy of unbiased)
	int exponent1= get_exponent(binary1) -4;
	int exponent2= get_exponent(binary2) -4;	
	int unbiased1=exponent1;
	int unbiased2=exponent2;

	//internal rep of values printed
	print_internal(fraction1,fraction2,exponent1,
                    exponent2, guard1, guard2);	
	printf("hidden bit----------------------^ ffff gr\n");
        printf("4-bit fraction--------------------^^^^ \n\n");

	cout <<"addition of the values: \n"<< endl;
	
	//swap operands if necessary
	if(exponent1 < exponent2)
	{
		int temp_exp;
		double temp_frac;
		int binaryTemp[8];

		cout << "operands are swapped\n";

		temp_exp= exponent1;
		exponent1=exponent2;
		exponent2=temp_exp;

		temp_frac=fraction1;
		fraction1=fraction2;
		fraction2=temp_frac;
		
		int tempbias1=unbiased1;
		unbiased1=unbiased2;
		unbiased2=unbiased1;
		
		for(int i=0;i<8;i++)
		{
			binaryTemp[i]=binary1[i];
			binary1[i]=binary2[i];
			binary2[i]=binaryTemp[i];
		}
	
		print_internal(fraction1,fraction2,exponent1,
                    exponent2, guard1, guard2);
	}

	
	//shift until exponents match
	while(exponent2 != exponent1)
	{
		cout << "second operand shifted to equalize exponents\n";
		fraction2=fraction2/10;
		exponent2++;
		
		string store= to_string(fraction2);
		char frac_array[8];
		std::strcpy(frac_array, store.c_str());

		char guardbit1=frac_array[6];
		char guardbit2=frac_array[7];
		
		int toguard1=guardbit1-'0';
		int toguard2=guardbit2-'0';;


		guard2[0]=toguard1;
		guard2[1]=toguard2;
	
		printf("internal rep of second value:    %.4f %d%d x 2^(%d)\n",
                                      fraction2,guard2[0],guard2[1],exponent2);
	}
	
	//check if sign bit set
	if(binary1[7] == 1 && binary2[7] == 0)
	{
		cout << "first operand negated"<< endl;
		fraction1=twoscomp(fraction1);
		printf("internal rep of first value:    %.4f %d%d x 2^(%d)\n",
                                      fraction1,guard1[0],guard1[1],exponent1);
	}	

	if(binary2[7] == 1 && binary1[7]==0)
	{
		cout << "second operand negated"<< endl;
		fraction2=twoscomp(fraction2);
		printf("internal rep of second value:    %.4f %d%d x 2^(%d)\n",
                                      fraction2,guard2[0],guard2[1],exponent2);
	}	

	if(binary2[7] == 1 && binary1[7] ==1)
	{
		finalbin[0]=1;

	}
	else
		finalbin[0]=0;
	//perform addition
	cout << "addition takes place" << endl;
	double sum =addition(0.0,fraction1,fraction2,guard1,guard2);
	print_internal(fraction1,fraction2,exponent1,
                    exponent2, guard1, guard2);
	printf("internal rep of sum:    %.4f %d%d x 2^(%d)\n",
                                     sum,finalGuard[0],finalGuard[1],exponent2);

	int finalexp = exponent2;
	if(sum < 1)
	{
		cout << "sum normalized" << endl;
		sum= sum*10;
		finalexp --;
		printf("internal rep of sum:    %.4f %d%d x 2^(%d)\n",
                                     sum,finalGuard[0],finalGuard[1],finalexp);
	}
	
	int tempfin = finalexp+4;

	if(tempfin == 1 )
        {
		finalbin[4]=0;
		finalbin[5]=0;
                finalbin[6]=1;
        }

        else if(tempfin== 2 )
        {
		finalbin[4]=0;
                finalbin[5]=1;
                finalbin[6]=0;
        }

        else if(tempfin == 3 )
        {
		finalbin[4]=0;
                finalbin[5]=1;
                finalbin[6]=1;
        }

        else if(tempfin == 4 )
        {
         	finalbin[4]=1;
                finalbin[5]=0;
                finalbin[6]=0;      
        }

        else if(tempfin == 5 )
        {
		finalbin[4]=1;
                finalbin[5]=0;
                finalbin[6]=1;
        }

        else if(tempfin == 6 )
        {
		finalbin[4]=1;
                finalbin[5]=1;
                finalbin[6]=0;
        }

        else if(tempfin == 7 )
        {
		finalbin[4]=1;
                finalbin[5]=1;
                finalbin[6]=1;
        }




	//get the decimal significand to produce the decimal value
	double decsig1= get_decsig(binary1) + 1;
	double decsig2= get_decsig(binary2) + 1;
	double finalsig= get_decsig(finalbin) + 1;
	double decval1= decsig1 * (pow(2,unbiased1));
        double decval2= decsig2 * (pow(2,unbiased2));
	double finvalue= finalsig * (pow(2,finalexp));

	printf("           %.4f x 2^(%d) = %f\n", decsig1,unbiased1,
							decval1);
        printf("added to   %.4f x 2^(%d) = %f\n", decsig2,unbiased2,
                                                        decval2);
	printf("equals     %.4f x 2^(%d) = %f\n", finalsig,finalexp,finvalue);
	
	
}


