#include "stdafx.h"
#include "kMedoidsCluster.h"

/* kMeansStudent */
kMedoidsCluster* kMedoidsStudent::findBestMatch(const std::vector<kMedoidsCluster*>& clusters)
{
	float currentDistance = 999.9f;

	if (m_cluster != nullptr) 
	{
		currentDistance = m_cluster->getDistance(this->m_student);
	}

	
	kMedoidsCluster* bestMatch = m_cluster;

	for (auto& const cluster : clusters)
	{
		if (cluster->getMedoid() == this) continue;

		float newDistance = cluster->getDistance(this->m_student);
		if (newDistance < currentDistance)
		{
			bestMatch = cluster;
			currentDistance = newDistance;
		}
	}

	return bestMatch;
}


void kMedoidsCluster::recomputeError()
{
	m_error = 0.0f;
	for (auto & const student : m_students)
	{
		if(student != m_medoid) m_error += getDistance(student->m_student);
	}
}

void kMedoidsCluster::exchangeMedoid(kMedoidsStudent* s)
{
	// Reset previous medoid (if there was one) [should always be one in this case]
	if (m_medoid) {
		m_medoid->m_isMedoid = false;
	}

	m_medoid = s;
	s->m_isMedoid = true;
}

/* kMeansCluster */
void kMedoidsCluster::removeStudent(kMedoidsStudent * s)
{
	auto it = m_students.find(s);
	if (it != m_students.end())
	{

		m_error -= getDistance(s->m_student);
		m_students.erase(it);
	}
	s->m_cluster = nullptr;

}

void kMedoidsCluster::addStudent(kMedoidsStudent * s)
{
	m_students.insert(s);
	s->m_cluster = this;
	m_error += getDistance(s->m_student);
}

void kMedoidsCluster::setMedoid(kMedoidsStudent * s)
{
	// Reset previous medoid (if there was one)
	if (m_medoid) {
		m_medoid->m_isMedoid = false;
		m_medoid->m_cluster = nullptr;
	}
	
	m_medoid = s;
	s->m_cluster = this;
	s->m_isMedoid = true;
	m_students.insert(s);
	recomputeError();
}

float kMedoidsCluster::getDistance(const Student * s)
{

	float matches = 0;
	float totalProps = (float)(m_properties->size());

	for (auto& const prop : *m_properties)
	{
		/* If centroid and provided student have same value for given property */
		
		if (s->getPropOfType(prop).CheckValue(m_medoid->m_student->getPropOfType(prop).value))
		{
			matches++;
		}
	}

	return (totalProps-matches) / totalProps;
}


bool kMedoidsCluster::searchNewMedoid()
{

	kMedoidsStudent* best_medoid = m_medoid;
	float lowestError=m_error;
	bool madeSwap = false;

	for (auto& s : m_students)
	{
		exchangeMedoid(s);	// changes the m_medoid
		recomputeError();	// changes the m_error
		
		if (m_error < lowestError) {
			best_medoid = s;
			lowestError = m_error;
			madeSwap = true;		
		}
	}

	// Put back the best medoid we found
	exchangeMedoid(best_medoid);
	m_error = lowestError;
	return madeSwap;
}





