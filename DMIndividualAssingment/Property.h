#pragma once
#include <stdint.h>
/* Propery Template Struct
	-> since all data about a student is binned within a range of values (no continuous values used within the code)
	   the data can be stored simply using bits in order to improve memory efficiency

	-> enums such as AgeGroup or GamesPlayed are set to the apporiate bit value insted of the default int value
*/

struct Property
{
	uint64_t value = 0;				//TODO set to 64 if 32 proves insuficient

	template<typename T>
	T GetPropertyValueOf(uint64_t v) const
	{
		return (T)(value & v);
	}

	bool CheckValue(uint64_t v) const
	{
		return value == v;//& v == v;
	}
};
