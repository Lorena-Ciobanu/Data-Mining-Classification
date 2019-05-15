#pragma once
#include <map>
#include <vector>
#include "PropertyIndex.h"
#include "AgeGroup.h"
#include "Degree.h"
#include "Gender.h"
#include "OS.h"

class ID3Property
{
private:
	std::map<PropertyIndex, std::vector<uint32_t>> m_props;

public:
	ID3Property();

	std::vector<uint32_t> getPossibleValues(const PropertyIndex& prop) const;

	~ID3Property();
};

