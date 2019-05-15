#include "stdafx.h"
#include "kMedoids.h"


void KMedoids::constructInitialClusters()
{
	/* Set up random generator: Uniform distribution about the entire set of students */
	std::random_device randomDevice;											// generate seed
	std::mt19937 engine(randomDevice());										// mersenne_twister_engine to which we feed the seed
	std::uniform_int_distribution<int> dist(0, (m_studentPlayers.size() - 1));		// initialize distribution from 0 to the max no of students we have		

	std::set<int> randomIndexes;

	/* Fill random indexes */
	while (randomIndexes.size() < m_numberOfClusters)
	{
		int randomIndex = dist(engine);

		/* Make sure we only add unique instances of students to training set */
		if (randomIndexes.find(randomIndex) == randomIndexes.end())
		{
			randomIndexes.insert(randomIndex);

			/* Construct cluster with centroid based around random student */
			kMedoidsStudent* s = new kMedoidsStudent();
			s->m_student = m_studentPlayers[randomIndex];

			kMedoidsCluster* cluster = new kMedoidsCluster(&m_properties);
			cluster->setMedoid(s);
			m_clusters.emplace_back(cluster);
		}
	}

	/* Consturct wrappers for all the other students */
	for (int index = 0; index < m_studentPlayers.size(); index++)
	{
		// If student hasn't already been assigned as centroid
		if (randomIndexes.find(index) == randomIndexes.end())
		{
			kMedoidsStudent* s = new kMedoidsStudent();
			s->m_student = m_studentPlayers[index];
			m_studentWrappers.emplace_back(s);
		}
	}

}

void KMedoids::runAlgorithm()
{
	bool newMatchFound = true;

	assignStudents();

	/* Initialize random */
	std::random_device randomDevice;											// generate seed
	std::mt19937 engine(randomDevice());										// mersenne_twister_engine to which we feed the seed
	std::uniform_int_distribution<int> dist(0, m_studentWrappers.size() - 1);


	/* Stop once no new match is found */
	while (newMatchFound)
	{
		newMatchFound = false;

		for (auto& cluster : m_clusters) {
			//std::cout << " Cluster error: " << cluster->getError() << std::endl;
			
			bool reasigned = cluster->searchNewMedoid();
			if (reasigned) newMatchFound = true;
		//	std::cout << "New cluster error: " << cluster->getError() << std::endl;
		}
		if(newMatchFound) assignStudents();
	
	}
}




/* Assign students to clusters */
void KMedoids::assignStudents()
{	
	for (auto& sw : m_studentWrappers)
	{
		if (sw->m_isMedoid) continue;

		kMedoidsCluster* cluster = sw->findBestMatch(m_clusters);

		/* If we find a better cluster */
		if (cluster != sw->m_cluster)
		{

		/* Got a bit confused here. It seems like we're always stuck with the "categories" picked by the rng with this implementation, since the medoids are only ever selected within cluster
		if (sw->m_isMedoid) {
				if (sw->m_cluster->getClusterSize() > 1) {		//Should always have at least one medoid
					std::cout << "Reasigned medoid " << std::endl;
					sw->m_cluster->exchangeMedoid(sw);
					sw->m_cluster->recomputeError();
				}
				else {
					// Select a random student to act as new medoid [?] (select from cluster with highest variation?)
				}
			} */

			/* Switch cluster */

			if (sw->m_cluster != nullptr)
			{
				sw->m_cluster->removeStudent(sw);
			}

			cluster->addStudent(sw);
		}
	}
}



KMedoids::KMedoids(const DataManager & manager, const int& nrOfClusters, const GamesPlayed& gamePlayed)
{
	m_numberOfClusters = nrOfClusters;
	m_students = manager.get_students();

	for (auto& const student : *m_students) {
		if (student.hasPlayedGame(gamePlayed)) {
			m_studentPlayers.emplace_back(&student);
		}
	}


	/* List of properties used in computing the distances between points */
	m_properties.emplace_back(PropertyIndex::PI_AgeRange);
	m_properties.emplace_back(PropertyIndex::PI_Degree);
	m_properties.emplace_back(PropertyIndex::PI_Gender);
	m_properties.emplace_back(PropertyIndex::PI_OS);
}

void KMedoids::start()
{
	constructInitialClusters();

	std::cout << std::endl;
	std::cout << " ------------ K-Medoids ------------ " << std::endl;

	runAlgorithm();
	std::cout << std::endl;
	
	for (auto& const cluster : m_clusters)
	{
		std::cout << "Cluster variation: " << cluster->getError() << " Size: "<<cluster->getClusterSize()<< std::endl;
		std::cout << "  [Medoid]: ";
		for (auto& const prop : m_properties) {
			std::cout << cluster->getMedoid()->m_student->getPropOfType(prop).value << " ";
		}
		std::cout << std::endl;
		
		for (auto& const student : cluster->getStudents()) {
			if (student != cluster->getMedoid()) {

				std::cout << "  [Student] ";
				for (auto& const prop : m_properties) {
					std::cout << student->m_student->getPropOfType(prop).value << " ";
				}
				std::cout << std::endl;
			}
		} 
	}

	std::cout << " ------------ K-Medoids ------------ " << std::endl;
	for (auto& const cluster : m_clusters) {
		std::cout << "Cluster variation: " << cluster->getError() << " Size: " << cluster->getClusterSize() << std::endl;
	}
	std::cout << " --------------------------------- " << std::endl;
}

KMedoids::~KMedoids()
{
	for (auto d : m_clusters)
	{
		delete d;
	}

	for (auto d : m_studentWrappers)
	{
		delete d;
	} 
}
