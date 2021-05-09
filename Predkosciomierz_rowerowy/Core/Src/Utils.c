#include "Utils.h"
#include <math.h>

int char2int(const char a)
{
	return ((int)a) - '0';
}

float str2float(const char* const str)
{
	float tmp = 0.f;
	float multiplier = 10.f;
	
	for (int i = 0; i < (sizeof(str) / sizeof(str[0])); ++i)
	{
		if(str[i] == '.')
		{
			multiplier = 0.1f; 
		}
		else if(multiplier == 10.f)
		{
			tmp = tmp * multiplier + char2int(str[i]);
		}
		else
		{
			tmp += char2int(str[i]) * multiplier;
			multiplier /= 10;
		}
	}
	
	return tmp;
}
