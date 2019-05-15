#include "stdafx.h"
#include "ID3Property.h"


ID3Property::ID3Property()
{
	std::vector<uint32_t> prop;
	prop.emplace_back(AgeGroup::Twenty_TwentyFive);
	prop.emplace_back(AgeGroup::TwentySix_Thirty);
	prop.emplace_back(AgeGroup::AboveThirty);
	m_props[PropertyIndex::PI_AgeRange] = prop;

	std::vector<uint32_t> prop2;
	prop2.emplace_back(Degree::SDT_DT);
	prop2.emplace_back(Degree::SDT_SE);
	prop2.emplace_back(Degree::GAMES_T);
	prop2.emplace_back(Degree::Guest);
	m_props[PropertyIndex::PI_Degree] = prop2;

	std::vector<uint32_t> prop3;
	prop3.emplace_back(Gender::Male);
	prop3.emplace_back(Gender::Female);
	prop3.emplace_back(Gender::Other_Gender);
	m_props[PropertyIndex::PI_Gender] = prop3;

	std::vector<uint32_t> prop4;
	prop4.emplace_back(OS::Android);
	prop4.emplace_back(OS::iOS);
	prop4.emplace_back(OS::macOS);
	prop4.emplace_back(OS::Windows);
	m_props[PropertyIndex::PI_OS] = prop4;


}

std::vector<uint32_t> ID3Property::getPossibleValues(const PropertyIndex& prop) const
{
	auto it = m_props.find(prop);
	if (it != m_props.end())
	{
		return it->second;
	}
	return std::vector<uint32_t>();
}


ID3Property::~ID3Property()
{
}
