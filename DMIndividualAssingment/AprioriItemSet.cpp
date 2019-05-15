#include "stdafx.h"
#include "AprioriItemSet.h"


void AprioriItemSet::generateSubsets(int i, const std::vector<GamesPlayed>& set, std::set<std::set<GamesPlayed>>& setOfSets)
{
	if (i == set.size())
	{
		setOfSets.emplace(std::set<GamesPlayed>());
		return;
	}

	generateSubsets(i + 1, set, setOfSets);

	std::vector<std::set<GamesPlayed>> newSets;
	for (auto subset : setOfSets)
	{
		subset.insert(set[i]);
		newSets.push_back(std::move(subset));
	}
	for (auto& newSet : newSets)
	{
		setOfSets.insert(std::move(newSet));
	}
}

AprioriItemSet::AprioriItemSet(GamesPlayed& gamePlayed)
{
	m_itemset.insert(gamePlayed);
}

AprioriItemSet::AprioriItemSet(const AprioriItemSet & set1, const AprioriItemSet & set2)
{
	m_itemset = set1.getItemset();
	m_itemset.insert(set2.getItemset().begin(), set2.getItemset().end());
}

AprioriItemSet::AprioriItemSet(const AprioriItemSet * initialSet,const std::set<GamesPlayed>& set)
{
	for (auto& const s : initialSet->getItemset()) {
		if (set.find(s) == set.end()) {
			m_itemset.insert(s);
		}
	}
}



bool AprioriItemSet::checkSubsets(const std::vector<AprioriItemSet>& initialItemsets)
{
	bool allSubsetsValid = false;

	int size = m_itemset.size() -1 ;	// Total size a subset can have

	// Kinnda crappy that i only got this to work by transforming into vector
	std::vector<GamesPlayed> v(m_itemset.begin(), m_itemset.end());
	std::set<std::set<GamesPlayed>> setOfSets;
	
	/* Generate all subsets (power set) [this is also kinnda crappy] */
	generateSubsets(0, v, setOfSets);

	int nrOfItemsets = 0;
	int nrOvValidItemsets = 0;

	for (auto& const set : setOfSets)
	{
		if (set.size() == size) {
			nrOfItemsets++;
			for (auto& const initialSets : initialItemsets) {
				if (set == initialSets.getItemset()) {
					nrOvValidItemsets++;
					break;
				}
			}
		}
	}

	return nrOfItemsets == nrOvValidItemsets;
}

/* Check uniqueness within list of itemsets */
bool AprioriItemSet::checkUnique(const std::vector<AprioriItemSet>& itemsets)
{
	for (auto& const initialSets : itemsets) {
		if (m_itemset == initialSets.getItemset()) {
			return false;
		}
	}
	return true;
}

/* Compute support count */
float AprioriItemSet::getSupportCount(const std::vector<Student>* students)
{
	float supportCount = 0.0f;

	for (auto& const student : *students)
	{
		bool hasItemset = true;

		for (auto& game : m_itemset)
		{
			// If student has not played one of the games in the itemset => suport = 0 for this student
			if (!student.hasPlayedGame(game))
			{
				hasItemset = false;
				break;
			}
		}

		// If all games have been played => increase support count 
		if(hasItemset) supportCount++;
	}

	return supportCount;
}

void AprioriItemSet::computeConfidence(const std::vector<Student>* students, float& minConfidence)
{
	// Again, kinnda crappy that i only got this to work by transforming into vector
	std::vector<GamesPlayed> v(m_itemset.begin(), m_itemset.end());
	std::set<std::set<GamesPlayed>> setOfSets;

	/* Generate all subsets (power set) */
	generateSubsets(0, v, setOfSets);

	float support = getSupportCount(students);

	std::cout << std::endl;

	for (auto& const set : setOfSets) {
		if (set.size() > 0 && set.size() != v.size()) {
			AprioriItemSet subset(set);
			float subSetSupport = subset.getSupportCount(students);
			float confidence = support / subSetSupport;
			
			if (confidence >= minConfidence) {
				AprioriItemSet minusSet(this, set);

				std::cout << " [s]: ";
				subset.print();
				
				std::cout << " => [s-l]: ";
				minusSet.print();
				
				std::cout<< " [Confidence]: " << confidence << std::endl;
			}
		}
		
	}
}

void AprioriItemSet::print() const
{
	for (auto& const game : m_itemset) {
		std::cout << game << " ";
	}
}