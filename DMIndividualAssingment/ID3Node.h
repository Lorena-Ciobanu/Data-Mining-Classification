#pragma once
#include <vector>

#include "Property.h"
#include "PropertyIndex.h"
#include "Student.h"

/* Class used to construct ID3 decision tree */
struct ID3Node
{
	int m_type = 0; // DEBUG ONLY  0 = parent node, 1 = leaf node

	std::vector<Student*> m_students;

	std::vector<ID3Node*> m_childNodes;

	PropertyIndex m_attribute;

	uint32_t m_value;

	std::string m_label;

	bool m_hasPlayed;	//use insted of label
};

