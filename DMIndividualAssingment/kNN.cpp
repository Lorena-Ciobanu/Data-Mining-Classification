#include "stdafx.h"
#include "kNN.h"


/* Determine class of student based on training set */
bool kNN::determineClass(const Student * s)
{
	kNNeighbour neighbours[NEAREST_NEIGHBORS];
	
	int currentLargestDistance = 0;
	int currentCount = 0;

	/* I'm sure there's way better ways of storing the closest neighbours */
	for (auto& const student : m_trainingSet)
	{

		kNNeighbour neighbour = computeNeighbour(student, s);
		
		if (currentCount < NEAREST_NEIGHBORS)
		{
			neighbours[currentCount++] = neighbour;
			if (neighbour.m_distance > currentLargestDistance) { currentLargestDistance = neighbour.m_distance;  }
		}
		else
		{
			// Only modify if we find a smaller distance than the largest one available
			if (neighbour.m_distance < currentLargestDistance)
			{
				for (int i = 0; i < NEAREST_NEIGHBORS; i++)
				{
					if (neighbours[i].m_distance < neighbour.m_distance)
					{
						neighbours[i] = neighbour;
						break;
					}
				}
			}
		}
	}

	/* Once all closest neighbours have been found => find dominant class among them */
	int hasPlayed = 0;
	int hasNotPlayed = 0;
	
	for (int i = 0; i < NEAREST_NEIGHBORS; i++)
	{
		(neighbours[i].m_student->hasPlayedGame(m_game)) ? hasPlayed++ : hasNotPlayed++;
	}

	return (hasPlayed > hasNotPlayed) ? true : false;
}

/* Compute distance between two tuples */
kNNeighbour kNN::computeNeighbour(const Student * target, const Student * training)
{
	kNNeighbour n;
	n.m_distance = 0.0f;
	n.m_student = target;
	for (auto const& attr : m_attributes)
	{
		/* Since all the attributes used are nominal -> simply check equality */
		if (target->getPropOfType(attr).value != training->getPropOfType(attr).value)
		{
			n.m_distance += 1;	// if property does not match -> increase distance
		}
	}
	
	return n;
}

/* Constructor */
kNN::kNN(const DataManager & dataManager, GamesPlayed game)
{
	/* Get constant list of students */
	m_students = dataManager.get_students();

	/* Construct random training set */
	m_trainingSet = dataManager.construct_training_set(m_trainingSetSize);

	/* Game to determine if person has played or not */
	m_game = game;

	/* Define the list of attributes to be used when constructing the decision tree */
	m_attributes.insert(PropertyIndex::PI_AgeRange);
	m_attributes.insert(PropertyIndex::PI_Degree);
	m_attributes.insert(PropertyIndex::PI_Gender);
	m_attributes.insert(PropertyIndex::PI_OS);
}

/* Predict if Game Played */
void kNN::predictIfGamePlayed()
{
	int correctValues = 0;
	int attempts = 0;

	int tp = 0;	//True positive;
	int tn = 0; //True negative;
	int fp = 0; //False positive;
	int fn = 0; //False negative;

	int positive = 0;
	int negative = 0;

	for (auto& const student : *m_students)
	{
	//	std::cout << "Known value: " << student.hasPlayedGame(m_game) << std::endl;

		bool result = determineClass(&student);

//		std::cout << "Predicted value: " << result << std::endl;

		if (result == student.hasPlayedGame(m_game)) {
			correctValues++;
			(result) ? tp++ : tn++;
		}
		else
		{
			(result) ? fp++ : fn++;
		}

		attempts++;
	}

	positive = tp + fp;
	negative = tn + fn;

	std::cout << std::endl;
	std::cout << " ----------- k-NN -----------" << std::endl;
	std::cout << " Neighbours used: " << NEAREST_NEIGHBORS << std::endl;
	std::cout << " Attempts: " << attempts << std::endl;
	std::cout << std::endl;
	std::cout << " True positives  (TP): " << tp << std::endl;
	std::cout << " True negatives  (TN): " << tn << std::endl;
	std::cout << " False positives (FP): " << fp << std::endl;
	std::cout << " False negatives (FN): " << fn << std::endl;
	std::cout << std::endl;
	std::cout << " Positives: " << positive << std::endl;
	std::cout << " Negatives: " << negative << std::endl;
	std::cout << std::endl;
	std::cout << " Accuracy: " << (float)(tp + tn) / (float)(positive + negative) << std::endl;
	std::cout << " Error rate: " << (float)(fp + fn) / (float)(positive + negative) << std::endl;
	std::cout << std::endl;
	std::cout << " Sensitivity [True positive]: " << ((float)tp / (float)positive) << std::endl;
	std::cout << " Specificity [True negative]: " << ((float)tn / (float)negative) << std::endl;
	std::cout << " --------------------------" << std::endl;
}

kNN::~kNN()
{
	//TODO delete pointer to m_students[?]
}
