#pragma once
#include <vector>
#include <list>
#include <map>

#include "AprioriItemSet.h"
#include "DataManager.h"


/* Find patterns between the games students have played */
class Apriori
{
private:
	const std::vector<Student>* m_students;

	// List of all possible games a student could have chosen in questionare 
	// Defined in constuctor (enums need to match to position in students)

	std::vector<GamesPlayed> m_possibleGames;		


	std::vector<AprioriItemSet> m_itemsets;


	float m_minSuport = 10.0f;		// minimum support value

	float m_minCondifence = 0.8;	// minimum confidence 


	/* Create initial itemsets (one itemset per each possible game) */
	void createInitialItemsets();

	void runAlgorithm();

	void prune();

	void join();

	void printOutput();

public:
	Apriori(const DataManager& dataManager);

	void start();


	~Apriori();
};

