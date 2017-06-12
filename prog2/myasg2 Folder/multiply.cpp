/*
Brendan Giberson(bgibers)
CPSC 2310-001
Program 2
February 22 2016

This program will illustate the steps required for multiplication using
the algorithm given in class
*/

#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib>

using namespace std;

/*print check portion of program */
void end(int multiplicand, int multiplier, int *mdr, int *accmq)
{
	int product= multiplicand*multiplier;

	cout << "---------------------------------------------------"<< endl;;
	cout << "check:                 binary   decimal"<< endl;;
  	cout << "                     " << (bitset<8>)multiplicand << "       " 
						<< multiplicand << endl;
  	cout << "           x         " << (bitset<8>)multiplier << "  x    "
					 << multiplier << endl;
  	cout << "             ----------------    ------"<< endl;;
  	cout << "             ";
      	cout << (bitset<16>)product << "     " << product << endl;;

}

/* print top line of step */
void accmq_print(int accmq[], int carry_val,int step_num)
{
	cout << "---------------------------------------------------" << endl;;
   	cout << "step " << step_num << ":";
   	cout << "   " << carry_val << " ";

   	for (int j= 0; j <= 7; j++)
	{
      		cout << accmq[j];
	}

   	cout << " ";

   	for (int j= 8; j <= 15; j++)
	{
      		cout << accmq[j];
	}
}

/*mdr + acc with carries . Adds from right to left*/
int mdr_add(int carry_val, int *accmq, int *mdr)
{
	int sum;
	int c=0;//temp carry
	
	for(int j=7; j>-1; j--)
	{
		sum=accmq[j] + mdr[j] + c;

		if(sum > 1)
		{
			c=1;
		}

		else
		{
			c=0;
		}

		accmq[j]= sum % 2;
	}
		return c;
}

/* shift accmq by 1 */
void shifter(int carry_val, int *accmq)
{
	for(int j=14; j>-1; j--)
	{
		accmq[j+1]=accmq[j];
	}
	
	if(carry_val)
	{
		accmq[0]=1;
	}

	else
	{
		accmq[0]=0;
	}
}

/*prints the step output */
void step_print(int lsb, int carry_val, int *mdr, int *accmq)
{
	//if lsb is 1 add mdr else do not
	if(lsb==1)
	{
		cout << "\n        +   ";
		for(int j=0; j <=7;j++)
		{
			cout << mdr[j];
		}
		cout <<"        ^ add based on lsb=1\n";
	}

	else
	{
		cout << "\n        +   ";
      		cout << "00000000";
      		cout << "         ^ no add based on lsb=0\n";
	}

	//print acc added to mq then shift the value to the right then print shifted 
	cout << "          ----------\n";
	cout  << "          " << carry_val << " ";
  	 for (int j= 0; j <= 7; j++)
	{
     		 cout << accmq[j];
	}

   	cout << " ";

   	for (int j= 8; j <= 15; j++)
	{
    	 	 cout << accmq[j];
	}

	cout << endl;
	cout << "       >>                     shift right\n";
	shifter(carry_val,accmq);
	carry_val=0;

	cout  << "          " << carry_val << " ";
	for(int j=0;j<=7;j++)
	{
		cout << accmq[j];
	}
	
	cout << " ";

	for (int j= 8; j <= 15; j++)
        {
                 cout << accmq[j];
        }

        cout << endl;

	
}

/* compute multiplication of 8bit by 8bit */
void compute(int step_num, int carry_val, int multiplicand, int multiplier,
					 int *mdr,int *accmq)
{
	int c=0;//carry 
	
	//if lsb is 1 print mdr else print without mdr increment step by 1
	for(int j=1; j<9; j++)
	{
		if(accmq[15] == 1)
		{
			accmq_print(accmq,c,step_num);
			c=mdr_add(c,accmq,mdr);
			step_print(1,c,mdr,accmq);
			c=0;
			step_num++; 			
		}

		else
		{
			accmq_print(accmq,carry_val,step_num);
			step_print(0,carry_val,mdr,accmq);
			step_num++;
		}
	}

	end(multiplicand,multiplier,mdr,accmq);
}

/*Input will read in the Multiplicand and multiplier, check if they are
within the range 0-255, and then convert the values to binary  */
void input(string file, int step_num, int carry_val, int multiplicand,
			 int multiplier, int *mdr, int *accmq)
{
	int binary;
	int temp_mcand, temp_mlier;//temp multiplicand and multiplier

	//input and check if vals are in range
	ifstream fin;
	fin.open(file.c_str());

	fin >> multiplicand;
	fin >> multiplier;
	
	fin.close();
	
	if(multiplicand < 0 || multiplier < 0 || multiplicand > 255 || multiplier > 255)
	{
		cout << "Values must be less then 255 and greater than 0\n" << endl;
	}

	//print top portion of output
	cout << "\nmultiplicand: " << multiplicand << endl;
  	cout << "multiplier: " << multiplier << "\n\n";
   	cout << "c and acc set to " << 0 << endl;
   	cout << "mq set to multiplier     = " << multiplier << " decimal and "
        << (bitset<8>)multiplier << " binary" << endl;
   	cout << "mdr set to multiplicand  = " << multiplicand << " decimal and "
        << (bitset<8>)multiplicand << " binary" << endl;

	//acc = 00000000
	for(int j=0; j<= 7; j++)
	{
		accmq[j]=0;
	}	
	
	//conver mq and mdr to binary
	temp_mlier=multiplier;
	temp_mcand=multiplicand;

	for(int j=15; j>7; j--)
	{
		binary=temp_mlier % 2;
		accmq[j]=binary;
		temp_mlier= temp_mlier / 2;
	}

	for(int j=7; j>-1;j--)
	{
		binary=temp_mcand % 2;
		mdr[j]=binary;
		temp_mcand= temp_mcand / 2;
	}

	compute(step_num,carry_val,multiplicand,multiplier,mdr,accmq);
}


int main()
{
	int accmq[16]; //acc and mq binary vals
	int step_num=1; //step number
	int carry_val=0; //carry value
	int multiplier=0 , multiplicand=0;
	int mdr[8]; //binary value of mdr

	input("prog2.txt",step_num,carry_val,multiplicand,multiplier,mdr,accmq);  

	return 0;
}
