#pragma once
#include <iostream>
#include <vector>
#include "Property.h"
#include "PropertyIndex.h"
#include "GamesPlayed.h"

const int NUMBER_OF_PROPERTIES = 5;		// Total number of attribures used [TODO]

/* Struct used to maintain data of individual student 
	-> uses Property template struct to store attributes both individual as well as arrays
*/
class Student
{

private: 
	Property m_properties[NUMBER_OF_PROPERTIES];	// Nominal properties 

	std::vector<bool> m_gamesPlayed;

//	float m_age;			// Normalized by min-max. Used for Clustering algotihm (could tehnically still be kept inside a Property object)
public:
	Student();

	//TODO Could just overload [] operator 
	const Property& getPropOfType (const PropertyIndex& prop) const;

	void setPropertyOfType(const PropertyIndex& prop, const uint64_t value);

	void Student::addGame(GamesPlayed game);

	bool Student::hasPlayedGame(GamesPlayed game) const;

	const std::vector<bool>& getGamesPlayed() const{ return m_gamesPlayed; }

	//TODO
//	void setAge(float age) { m_age = age; }

	//float getAge() const { return m_age; }


	~Student();
};
