#ifndef STRINGNUM_H
#define STRINGNUM_H

#include <string>
#include <map>
#include <iostream>


class StringNum
{
private:
	static StringNum *sRef;
	std::map<int, std::string> units;
	std::map<int, std::string> deca;
	std::map<int, std::string> powers;
	std::map<int, long> steps;
	
	StringNum();
	void initialize();
public:
	static StringNum *instance()
	{
		if(!sRef)
		{
			sRef = new StringNum();
		}
		return sRef;
	}
	std::string toDescriptive(long num);
};




#endif 
