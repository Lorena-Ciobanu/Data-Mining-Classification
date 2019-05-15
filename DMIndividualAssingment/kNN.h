#pragma once
#include <vector>
#include "DataManager.h"
#include "kNNeighbour.h"

// Number of neighbours 
const int NEAREST_NEIGHBORS = 8;

class kNN
{
private:
	const std::vector<Student>* m_students;			// List of all students
	std::vector<Student*> m_trainingSet;			// Training set (points to certain students within the list of all students)

	std::set<PropertyIndex> m_attributes;			// List of attibutes used in contruction of tree [ Gender, Age Range, Preffered OS, Degree ]

	int m_trainingSetSize = 40;						// TODO figure out appropiate size (pass as parameter maybe?)

//	const int m_kNearestNeighbours = 3;		[defined as constant above] 			

	GamesPlayed m_game;								// The game used to consturct possible classes (Student playes the game / Doesn't play the game)


	/* Determine class of student based on training set */
	bool determineClass(const Student* s);

	/* Compute distance between two tuples */
	kNNeighbour computeNeighbour(const Student* target, const Student* training);

public:
	kNN(const DataManager& dataManager, GamesPlayed game);
	
	/* Predict game played based on training set */
	void predictIfGamePlayed();
	
	~kNN();
};

