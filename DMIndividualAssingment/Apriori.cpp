#include "stdafx.h"
#include "Apriori.h"

void Apriori::createInitialItemsets()
{
	for (auto& const game: m_possibleGames)
	{
		AprioriItemSet s(game);
		m_itemsets.emplace_back(s);
	}
}

void Apriori::runAlgorithm()
{
	std::vector<AprioriItemSet> prevGen = m_itemsets;

	int count = 0;

	while (m_itemsets.size() != 0)
	{
		std::cout << "Computing phase " << count++ <<"... "<< std::endl;
		prevGen = m_itemsets;
		prune();				// modifies m_itemsets
		join();					// also modifies m_itemsets

		std::cout << "	current size of itemsets: "<< m_itemsets.size() << std::endl;
	}

	m_itemsets = prevGen;
}

void Apriori::prune()
{
	std::vector<AprioriItemSet> newGen;

	/* Check support of all itemsets */
	for (auto& const itemset: m_itemsets) {
		if (itemset.getSupportCount(m_students) > m_minSuport) {
			newGen.emplace_back(itemset);
		}
	}

	m_itemsets = newGen;
}

void Apriori::join()
{
	std::vector<AprioriItemSet> newGen;

	for (int i = 0; i < m_itemsets.size(); i++) {
		for (int j = i+1; j < m_itemsets.size(); j++)
		{
			/* Create a new itemset from two prev ones */
			AprioriItemSet itemset(m_itemsets[i], m_itemsets[j]);
			
			/* Check that itemset is unique */
			if (!itemset.checkUnique(newGen)) {
				continue;
			}

			/* Check if all subsets of this exist in current gen. If yes-> add to new itemset */
			if (itemset.checkSubsets(m_itemsets))
			{
				newGen.emplace_back(itemset);
			}
		}
	}

	m_itemsets = newGen;
}





void Apriori::printOutput()
{
	
	for (auto& const itemset : m_itemsets) {
		std::cout << "[Itemset] [Support]: " << itemset.getSupportCount(m_students) << " [Values]: ";
		itemset.print();
		itemset.computeConfidence(m_students, m_minCondifence);
		std::cout << std::endl;
	}
	std::cout << "----------------------------------- " << std::endl;
}




Apriori::Apriori(const DataManager & dataManager)
{

	m_students = dataManager.get_students();

	m_possibleGames.push_back(GamesPlayed::AngryBirds);
	m_possibleGames.push_back(GamesPlayed::Battlefield4);
	m_possibleGames.push_back(GamesPlayed::Bloodthorne);
	m_possibleGames.push_back(GamesPlayed::CallOfDuty);
	m_possibleGames.push_back(GamesPlayed::CandyCrush);
	m_possibleGames.push_back(GamesPlayed::CSGO);
	m_possibleGames.push_back(GamesPlayed::DragonAgeInquisition);
	m_possibleGames.push_back(GamesPlayed::Fallout4);
	m_possibleGames.push_back(GamesPlayed::FarmVille);
	m_possibleGames.push_back(GamesPlayed::Fifa2017);
	m_possibleGames.push_back(GamesPlayed::GoneHome);
	m_possibleGames.push_back(GamesPlayed::HerStory);
	m_possibleGames.push_back(GamesPlayed::Journey);
	m_possibleGames.push_back(GamesPlayed::LifeIsStrange);
	m_possibleGames.push_back(GamesPlayed::Minecraft);
	m_possibleGames.push_back(GamesPlayed::RiseOfTombRaider);
	m_possibleGames.push_back(GamesPlayed::RocketLeague);
	m_possibleGames.push_back(GamesPlayed::StanleyParable);
	m_possibleGames.push_back(GamesPlayed::StarWarsBattlefield);
	m_possibleGames.push_back(GamesPlayed::TheLastOfUs);
	m_possibleGames.push_back(GamesPlayed::TheMagicCircle);
	m_possibleGames.push_back(GamesPlayed::TheWitness);
	m_possibleGames.push_back(GamesPlayed::Wordfeud);

	//excluded GamesPlayed::NONE


}

void Apriori::start()
{
	std::cout << "------------ Apriori -------------- " << std::endl;
	createInitialItemsets();
	runAlgorithm();
	printOutput();
}

Apriori::~Apriori()
{
	
}
