#include "stdafx.h"
#include "ID3.h"

#include "AgeGroup.h"

/* Construct Decision Tree */
ID3Node* ID3::constructDecisionTree(ID3Node* node, const std::vector<Student*>& set /*, std::set<PropertyIndex>& attributes*/)
{
	if (node == nullptr)
	{
		node = new ID3Node();
		node->m_type = 0;
	}

	int nrOfSameClass;
	bool majorityLabel = getMajorityClass(set, nrOfSameClass);	// Returns the number of majority (Has Played / Has Not Played)

	/* If they all belong to the same class or no more attributes => Majority Label */
	/* Alternatively, could compute entropy and check if == 0 */
	if (nrOfSameClass == set.size() || m_attributes.size() == 0)
	{
		node->m_hasPlayed = majorityLabel;
	//	node->m_label = majorityLabel;
		return node;
	}

	/* Attribute selection method */
	PropertyIndex propertyToSplit = attributeSelectionMethod(set, m_attributes);
	node->m_attribute = propertyToSplit;


	/* Erase found property from list of properties */
	m_attributes.erase(m_attributes.find(propertyToSplit));
	std::vector<Student*> currentSet = set;
	

	/* For all possible values of property*/
	for (auto& const val : m_properties.getPossibleValues(propertyToSplit))
	{
		
		std::vector<Student*> withProp;
		std::vector<Student*> withoutProp;

		separateStudentsByValue(currentSet, propertyToSplit, val, withProp, withoutProp);

		currentSet = withoutProp;

		if (withProp.size() == 0)
		{
			ID3Node * new_node = new ID3Node();
			node->m_hasPlayed = majorityLabel;
			node->m_childNodes.emplace_back(new_node);
		}
		else
		{
			ID3Node * new_node = new ID3Node();
			new_node->m_attribute = propertyToSplit;
			new_node->m_value = val;
			new_node->m_students = withProp;
			new_node->m_type = 1;
			node->m_childNodes.emplace_back(new_node);
		}
	}

	/* Construct further branches from leaf nodes */
	for (auto& const n : node->m_childNodes)
	{
		n->m_childNodes.emplace_back(constructDecisionTree(nullptr, n->m_students));
	}

	return node;
}

/* Get Majority Class */
bool ID3::getMajorityClass(const std::vector<Student*>& set, int & nr)
{
	int hasPlayed = 0;
	int hasNotPlayed = 0;
	for (auto& const s : set)
	{
		(s->hasPlayedGame(m_game))? hasPlayed++ : hasNotPlayed++;
	}
	
	if (hasNotPlayed > hasPlayed)
	{
		nr = hasNotPlayed;
		return false; //"Has not played game.";
	}
	else
	{
		nr = hasPlayed;
		return true; //"Has played game";
	}
}


/* Attribute Selection */
float ID3::computeGameEntropy(const std::vector<Student*>& set)
{
	int havePlayed = 0;
	int haveNotPlayed = 0;

	/* Count the number of played vs have not played */
	for (auto const s : set)
	{
		(s->hasPlayedGame(m_game)) ? havePlayed++ : haveNotPlayed++;
	}

	/* Compute probability of each class */
	float p1 = (float)havePlayed / set.size();
	float p2 = (float)haveNotPlayed / set.size();

	float entropy = 0;

	if (p1 != 0) { entropy += p1*log(p1); }			// to avoid nan by log(0)
	if (p2 != 0) { entropy += p2*log(p2); }

	return entropy * (-1);
}

void ID3::separateStudentsByValue(const std::vector<Student*>& set, const PropertyIndex & prop, const uint32_t & value, std::vector<Student*>& with, std::vector<Student*>& without)
{
	for (auto const s : set)
	{
		if (s->getPropOfType(prop).CheckValue(value))
		{
			with.push_back(s);
		}
		else
		{
			without.push_back(s);
		}
	}
}

float ID3::computeInformationGain(const std::vector<Student*>& set, const PropertyIndex & prop)
{
	float sum = 0.0f;

	std::vector<uint32_t> possibleValues = m_properties.getPossibleValues(prop);
	std::vector<Student*> currentSet = set;

	for (auto const& val : possibleValues)
	{
		std::vector<Student*> withProp;
		std::vector<Student*> withoutProp;

		separateStudentsByValue(currentSet, prop, val, withProp, withoutProp);

		currentSet = withoutProp;			// Since the values used are always discrete and single, we can check strictly in the ones left over from prev searches

		if (withProp.size() == 0) continue;

		float gameEntWithProp = computeGameEntropy(withProp);
		sum += ((float)withProp.size() / (float)set.size()) * gameEntWithProp;
		
	}

	return computeGameEntropy(set) - sum;
}

PropertyIndex ID3::attributeSelectionMethod(const std::vector<Student*>& set, const std::set<PropertyIndex>& properties)
{
	PropertyIndex bestProp;
	float highestGain = 0.0f;

	for (auto& const prop : m_attributes)
	{
		float infoGain = computeInformationGain(set, prop);
		if (highestGain <= infoGain)
		{
			highestGain = infoGain;
			bestProp = prop;
		}
		//std::cout << "Prop " << prop << " - info gain: " << infoGain << std::endl;
	}

	return bestProp;
}




/* Constructor */
ID3::ID3(const DataManager & dataManager, const GamesPlayed& game)
{
	/* Get constant list of students */
	m_students = dataManager.get_students();

	/* Construct random training set */
	m_trainingSet = dataManager.construct_training_set(m_trainingSetSize);

	/* Define the list of attributes to be used when constructing the decision tree */
	m_attributes.insert(PropertyIndex::PI_AgeRange);
	m_attributes.insert(PropertyIndex::PI_Degree);
	m_attributes.insert(PropertyIndex::PI_Gender);
	m_attributes.insert(PropertyIndex::PI_OS);

	m_game = game;

	m_startNode = constructDecisionTree(nullptr, m_trainingSet/*, m_attributes*/);
//	displayTree(m_startNode, 0);
}


/* Debug Help Function */
void ID3::displayTrainingSet()
{
	for (auto s : m_trainingSet)
	{
		PropertyIndex a = PropertyIndex::PI_AgeRange;
		//Property<AgeGroup> ageGroup = s->GetProp(PropertyIndex::PI_AgeRange);
	}
}

void ID3::displayTree(ID3Node *n, int depth)
{
	std::cout << "Depth: " << depth << " ";
	std::cout << " Type: " << n->m_type << " ";
	std::cout << " Attribute: " << n->m_attribute << " ";
	std::cout << " Value: " << n->m_value << " ";

	if (!n->m_label.empty())
	{
		std::cout << " Label: " << n->m_hasPlayed;
	}

	std::cout<<std::endl;

	if (n->m_childNodes.size() > 0)
	{
		for (auto& const p : n->m_childNodes)
		{
			displayTree(p, depth + 1);
		}
	}
	
}

bool ID3::checkNode(const ID3Node* node, const Student * s)
{
	/* Final leaf node */
	if (node->m_childNodes.size() == 0)
	{
		return node->m_hasPlayed;
	}

	/* Leaf node with only ever have one child */
	if (node->m_type == 1)
	{
		return checkNode(node->m_childNodes[0], s);
	}

	for (auto const sub_node : node->m_childNodes)
	{
		if (s->getPropOfType(sub_node->m_attribute).CheckValue(sub_node->m_value))
		{
			return checkNode(sub_node, s);
		}
	}
}


void ID3::predictIfGamePlayed()
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
//		std::cout << "Known value: " << student.hasPlayedGame(m_game) << std::endl;

		if (m_startNode == nullptr)
		{
			m_startNode = constructDecisionTree(nullptr, m_trainingSet);
		}
		
		bool result = checkNode(m_startNode, &student);

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
	std::cout << " ----------- ID3 -----------" << std::endl;
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
	//std::cout << "Attempts: " << attempts << " Correct Predictions: " << correctValues << " Accuracy percentage: " << (((float)correctValues / (float)attempts) * 100) <<"%"<< std::endl;

}



/* Destructor */
ID3::~ID3()
{
	//TODO delete nodes 
}
