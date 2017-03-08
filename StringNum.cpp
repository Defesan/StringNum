#include "StringNum.h"

void StringNum::initialize()
{
	std::map<int, std::string> tUnits
	{
		{0, "zero"},
		{1, "one"},
		{2, "two"},
		{3, "three"},
		{4, "four"},
		{5, "five"},
		{6, "six"},
		{7, "seven"},
		{8, "eight"},
		{9, "nine"},
		{10, "ten"},
		{11, "eleven"},
		{12, "twelve"},
		{13, "thirteen"},
		{14, "fourteen"},
		{15, "fifteen"},
		{16, "sixteen"},
		{17, "seventeen"},
		{18, "eighteen"},
		{19, "nineteen"}
	};
	
	this->units = tUnits;
	
	std::map<int, std::string> tDeca
	{
		{0, "impossible"},
		{1, "ten"},
		{2, "twenty"},
		{3, "thirty"},
		{4, "forty"},
		{5, "fifty"},
		{6, "sixty"},
		{7, "seventy"},
		{8, "eighty"},
		{9, "ninety"} 	
	};

	this->deca = tDeca;


	std::map<int, std::string> tPowers
	{
		{0, " quintillion"},
		{1, " quadrillion"},
		{2, " trillion"},
		{3, " billion"},
		{4, " million"},
		{5, " thousand"},
		{6, " hundred"}
	};

	this->powers = tPowers;

	std::map<int, long> tSteps
	{
		{0, 1000000000000000000},
		{1, 1000000000000000},
		{2, 1000000000000},
		{3, 1000000000},
		{4, 1000000},
		{5, 1000},
		{6, 100}
	};

	this->steps = tSteps;
}

StringNum::StringNum()
{
	this->initialize();
}

std::string StringNum::toDescriptive(long num)
{
	long remainder = num;
	long quotient = 0;
	std::string descriptive = "";	
	std::string temp = "";	

	if(remainder == 0)
	{
		return "zero";
	}

	if(remainder < 0)
	{
		descriptive += "negative ";
		remainder *= -1;
	}

	//We now know that the remaining number is between 1 and
	//9.3 * 10^18, i.e. less than 10 quintillion.

	for(int i = 0; i <= 6; i++)
	{
		if(remainder >= this->steps[i])
		{
			quotient = remainder / this->steps[i];
			temp = this->toDescriptive(quotient);
			descriptive += temp;
			descriptive += this->powers[i];
			remainder -= quotient * this->steps[i];
			if(remainder == 0)
			{
				break;
			}
			else if (remainder > 100)
			{
				descriptive += ", ";	
			}
			else
			{
				descriptive += " and ";
			} 
		}
	}
    //base cases. Here, we have a number less than 100. In the first case, we deal with numbers greater than 19. These numbers all have the form <tens>(-units):twenty-three, fifty-nine.
	if(remainder >= 20)
	{
		quotient = remainder / 10;
		remainder -= quotient * 10;
		descriptive += this->deca[quotient];
		if(remainder > 0)
		{
			descriptive += "-";
		}
	}
	//If the number was less than 20, or the previous block extracted the units digit, the final number comes out of the units map. huh?
	if(remainder > 0)
	{
		descriptive += this->units[remainder];
	}
	return descriptive;
}