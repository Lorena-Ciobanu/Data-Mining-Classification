#pragma once
#include <random>

#include "DataManager.h"
#include "kMedoidsCluster.h"
class KMedoids
{
private:
	const std::vector<Student>* m_students;				// List of all students

	std::vector<const Student*> m_studentPlayers;		// List of students that have played a specific game


	std::vector<kMedoidsCluster*> m_clusters;

	std::vector<kMedoidsStudent*> m_studentWrappers;	// Used for two way reference between students and clusters

	std::vector<PropertyIndex> m_properties;			// Properties used to determine distance between two tuples (defined in contructor)

	int m_numberOfClusters;								// Number of clusters used in algorithm

	// Split m_students into initial set (m_clusters) and rest (m_studentWrappers)
	void constructInitialClusters();

	// Assign students to clusters based on mean, stop when no more changes
	void runAlgorithm();

	void assignStudents();

public:
	KMedoids(const DataManager& manager, const int& nrOfClusters, const GamesPlayed& gamePlayed);

	void start(); 

	~KMedoids();
};

