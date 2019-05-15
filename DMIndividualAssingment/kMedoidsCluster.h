#pragma once
#include <set>
#include "Student.h"

class kMedoidsCluster;

/* Wrapper class for student which keeps reference to current cluster */
struct kMedoidsStudent
{
	bool m_isMedoid;
	const Student* m_student;
	kMedoidsCluster* m_cluster;

	kMedoidsCluster* findBestMatch(const std::vector<kMedoidsCluster*>& clusters);
};


/* Struct used to maintain Clusters in KMeans algorithm */
class kMedoidsCluster
{
private:
	kMedoidsStudent * m_medoid;
	std::set<kMedoidsStudent*> m_students;			// includes medoid 
	float m_error = 0.0f;

	const std::vector<PropertyIndex>* m_properties;

	

	

public:

	kMedoidsCluster(const std::vector<PropertyIndex>* properties) : m_properties(properties) {}
	
	void removeStudent(kMedoidsStudent* s);
	void addStudent(kMedoidsStudent* s);

	void setMedoid(kMedoidsStudent* s);

	void exchangeMedoid(kMedoidsStudent* s);

	void recomputeError();

	kMedoidsStudent* getMedoid() const { return m_medoid; }

	float getDistance(const Student * s);

	float getError() const { return m_error; }

	int getClusterSize() const { return m_students.size(); }

	const std::set<kMedoidsStudent*> getStudents() const { return m_students; }

	bool searchNewMedoid();
};

