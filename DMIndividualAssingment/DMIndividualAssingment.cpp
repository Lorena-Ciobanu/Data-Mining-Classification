// DMIndividualAssingment.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ID3.h"
#include "kNN.h" 
#include "Apriori.h"
#include "kMedoids.h"

/* Constant - FILENAME */
const std::string FILENAME = "Data Mining - Spring 2018.csv";


/* ID3 */
void ID3_Algorithm(const DataManager& dataManager)
{
	ID3 id3(dataManager, GamesPlayed::AngryBirds);				// Define the game to construct decision tree around
	id3.predictIfGamePlayed();									// Run prediction for entire set of students previously on constructed tree
}


/* K Nearest Neighbor */
void k_NN(const DataManager& dataManager)
{
	kNN knn(dataManager, GamesPlayed::TheMagicCircle);
	knn.predictIfGamePlayed();
}


/* k-Means */
void k_Medoids(const DataManager& dataManager)
{
	KMedoids kMedoids(dataManager, 5, GamesPlayed::AngryBirds);		// define number of clusters and game played
	kMedoids.start();
}

/* Apriori */
void apriori(const DataManager& dataManager)
{
	Apriori api(dataManager);
	api.start();
}

/* Main */
int main()
{
	/* Initialize and construct student data */
	DataManager dataManager(FILENAME);

	/* ID3 */
	ID3_Algorithm(dataManager);

	/* k-Nearest Neighbor */
	k_NN(dataManager);

	/* k-means */
	k_Medoids(dataManager);


	/* Apriori */
	apriori(dataManager);

    return 0;
}

