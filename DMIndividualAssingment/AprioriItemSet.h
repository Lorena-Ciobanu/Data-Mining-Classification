#pragma once
#include <set>
#include <vector>

#include "Student.h"
#include "GamesPlayed.h"

class AprioriItemSet
{
private:
	std::set<GamesPlayed> m_itemset;

	void generateSubsets(int i, const std::vector<GamesPlayed>& set, std::set<std::set<GamesPlayed>>& set_of_sets);

public:
	AprioriItemSet() {};

	/* Used to create initial item sets */
	AprioriItemSet(GamesPlayed& gamePlayed);

	/* Used in union */
	AprioriItemSet(const AprioriItemSet& set1, const AprioriItemSet& set2);

	/* Generate l - s */
	AprioriItemSet(const AprioriItemSet* initialSet, const std::set<GamesPlayed>& set);

	AprioriItemSet(const std::set<GamesPlayed>& set) { m_itemset = set; }



	const std::set<GamesPlayed>& getItemset() const { return m_itemset; }

	/* Create and check subsets with current generation */
	bool checkSubsets(const std::vector<AprioriItemSet>& itemsets);

	/* Check that itemset is unique */
	bool checkUnique(const std::vector<AprioriItemSet>& itemsets);

	/* Get support over all students */
	float getSupportCount(const std::vector<Student>* students);


	void computeConfidence(const std::vector<Student>* students, float& minConfidence);

	void print() const;
};

