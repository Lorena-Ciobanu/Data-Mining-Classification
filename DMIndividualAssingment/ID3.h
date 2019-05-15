#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "DataManager.h"
#include "ID3Node.h"
#include "ID3Property.h"

class ID3
{
private:
	const std::vector<Student>* m_students;			// List of all students
	std::vector<Student*> m_trainingSet;			// Training set (points to certain students within the list of all students)

	std::set<PropertyIndex> m_attributes;			// List of attibutes used in contruction of tree [ Gender, Age Range, Preffered OS, Degree ]		
	ID3Property m_properties;						// Map containing all attributes used and possible values (this sucks, i know)

	int m_trainingSetSize = 40;						// TODO figure out appropiate size (pass as parameter maybe?)

	ID3Node* m_startNode;

	GamesPlayed m_game;								// The game used to consturct possible classes (Playes Game / Doesn't play game)

	/* Function to create decision tree based on training data */
	ID3Node* constructDecisionTree(ID3Node* prevNode, const std::vector<Student*>& set/*, std::set<PropertyIndex>& attributes*/);


	/* Returns the label of majority class and the number of students found */
	bool getMajorityClass(const std::vector<Student*>& set, int& nr);	


	/* Attribute selection method helper functions */
	float computeGameEntropy(const std::vector<Student*>& set);

	void separateStudentsByValue(const std::vector<Student*>& set, const PropertyIndex & prop, const uint32_t & value, std::vector<Student*>& with, std::vector<Student*>& without);

	float computeInformationGain(const std::vector<Student*>& set, const PropertyIndex & prop);


	/* Attribute selection method - return property with highest information gain at each step*/
	PropertyIndex attributeSelectionMethod(const std::vector<Student*>& set, const std::set<PropertyIndex>& properties);

	bool checkNode(const ID3Node* node, const Student * s);

public:

	/* Constructor - Requires reference to a dataManager to get student data and construct training set */
	ID3(const DataManager& dataManager, const GamesPlayed& game);

	/* Display function (only used for debug) */
	void displayTrainingSet();

	void displayTree(ID3Node *n, int depth);

	void predictIfGamePlayed();
	
	~ID3();	//TODO recursively delete pointers to child nodes
};

