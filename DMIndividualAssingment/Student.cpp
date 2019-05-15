#include "stdafx.h"
#include "Student.h"

Student::Student()
{
	m_gamesPlayed.resize(25);		//Number of games played
}

const Property& Student::getPropOfType(const PropertyIndex & prop) const
{
	return m_properties[prop];
}

void Student::setPropertyOfType(const PropertyIndex & prop, const uint64_t value)
{
	m_properties[prop].value = value;
}

void Student::addGame(GamesPlayed game)
{
	m_gamesPlayed[game] = true;
}

bool Student::hasPlayedGame(GamesPlayed game) const
{
	return m_gamesPlayed[game];
}

Student::~Student()
{
}
