#include "stdafx.h"
#include "DataManager.h"
#include "CSVReader.h"


bool DataManager::setAgeRange(Student & s, const std::string& value)
{
	try {
		std::string::size_type sz;
		int int_value = std::stoi(value, &sz);		// Int value 

		if (AGE_RANGE_LOW <= int_value && int_value <= AGE_RANGE_MID)
		{
			s.setPropertyOfType(PropertyIndex::PI_AgeRange, AgeGroup::Twenty_TwentyFive);
			return true;
		}
		if (AGE_RANGE_MID <= int_value && int_value <= AGE_RANGE_HIGH) {
			s.setPropertyOfType(PropertyIndex::PI_AgeRange, AgeGroup::TwentySix_Thirty);
			return true;
		}
		if (AGE_RANGE_HIGH < int_value && int_value <= AGE_MAX_AGE) {
			s.setPropertyOfType(PropertyIndex::PI_AgeRange, AgeGroup::AboveThirty);
			return true;
		}

		// If age falls outside of ranges 20 - 50 => discard
		std::cout << "[DataManager][SetAgeRange] Discarded value (not in range): " << int_value << std::endl;
		return false;
	}
	catch (std::exception& e) {
		std::cout << "[DataManager][SetAgeRange] Discarded value (NAN): " << value << std::endl;
		return false;
	}
}

//TODO
bool DataManager::setCourseReason(Student & s, const std::string& value)
{
	//TODO
//	std::cout << "Course Reason: "<< value << std::endl;
	return true;
}

bool DataManager::setDegree(Student & s, const std::string& value)
{
	if (!value.empty()) {
		Degree degree;

		switch (value[0]) {
			case 'S': 
			{
				if (value[4] == 'S') { degree = Degree::SDT_SE; break; }		// SDT_SE
				else {degree = Degree::SDT_DT; break; }							// SDT_DT
			}
			case 'G': 
			{
				if (value[1] == 'A') { degree = Degree::GAMES_T; break; }		// GAMES_T
				else { degree = Degree::Guest; break; }							// Guest
			}
			default: 
			{
				std::cout << "[DataManager][SetDegree] Discarded value (invalid degree value): " << value << std::endl;
				return false;
			}
		}

		s.setPropertyOfType(PropertyIndex::PI_Degree, degree);
		return true;
	}

	std::cout << "[DataManager][SetDegree] Discarded value (no degree provided): " << value << std::endl;
	return false;
}

bool DataManager::setGamesPlayed(Student & s, const std::string& value)
{

	if (!value.empty()) {

		// "I have not played any of these games" (happy coincidence that none of the provided games start with an I :D)
		if (value[0] == 'I')
		{
			m_stats.noNoGamesPlayed++;
			//TODO
		//	s.setPropertyOfType(PropertyIndex::PI_GamesPlayed, GamesPlayed::NONE);
			return true;
		}

		std::stringstream stream(value);
		std::string game;

		while (std::getline(stream, game, ';')) 
		{
			GamesPlayed currentGame;
			switch (game[0])
			{
				case 'A': { currentGame = GamesPlayed::AngryBirds; m_stats.noAngryBirds++; break; }								// Angry Birds
				case 'B':
				{
					if (game[1] == 'a') { currentGame = GamesPlayed::Battlefield4; m_stats.noBattlefield++;  break; }			// Battlefield 4	
					currentGame = GamesPlayed::Bloodthorne;																		// Bloodthorne
					m_stats.noBloodthrone++;
					break;
				}
				case 'C': 
				{
					if (game[1] == 'o') { currentGame = GamesPlayed::CSGO; m_stats.noCSGO++;  break; }							// Counter Strike_ GO
					if (game[2] == 'l') { currentGame = GamesPlayed::CallOfDuty; m_stats.noCallOfDuty++;  break; }				// Call of Duty: Black Ops
					currentGame = GamesPlayed::CandyCrush;																		// Candy Crush
					m_stats.noCandyCrush++;
					break; 
				}
				case 'D': { currentGame = GamesPlayed::DragonAgeInquisition; m_stats.noDragonAge++;  break; }					// Dragon Age: Inquisition
				case 'F': 
				{
					if (game[1] == 'i') { currentGame = GamesPlayed::Fifa2017; m_stats.noFifa++; break; }						// Fifa 2017
					if (game[2] == 'r') { currentGame = GamesPlayed::FarmVille; m_stats.noFarmville++; break; }					// FarmVille
					currentGame = GamesPlayed::Fallout4;																		// Fallout 4
					m_stats.noFallout++;
					break;
				}
				case 'G': {currentGame = GamesPlayed::GoneHome; m_stats.noGoneHome++;  break; }									// Gone Home
				case 'H': {currentGame = GamesPlayed::HerStory; m_stats.noHerStory++; break; }									// Her Story
				case 'J': {currentGame = GamesPlayed::Journey; m_stats.noJourney++; break; }									// Journey
				case 'L': {currentGame = GamesPlayed::LifeIsStrange; m_stats.noLifeIsStrange++;  break; }						// Life is Strange
				case 'M': { currentGame = GamesPlayed::Minecraft; m_stats.noMinecraft++; break; }								// Minecraft
				case 'R': 
				{
					if (game[1] == 'i') { currentGame = GamesPlayed::RiseOfTombRaider; m_stats.noRiseOfTombRaider++;  break; }	// Rise of the Tomb Raider
					currentGame = GamesPlayed::RocketLeague;																	// Rocket League
					m_stats.noRocketLeague++;
					break;
				}
				case 'S': 
				{
					if (game[3] == 'n') { currentGame = GamesPlayed::StanleyParable; m_stats.noStanleyParable++; break; }		// Stanley Parable
					currentGame = GamesPlayed::StarWarsBattlefield;																// Star Wars Battlefield
					m_stats.noStarWarsBattlefield++;
					break;
				}
				case 'T':
				{
					if (game[4] == 'W') { currentGame = GamesPlayed::TheWitness; m_stats.noTheWitness++; break; }				// The Witness
					if (game[4] == 'M') { currentGame = GamesPlayed::TheMagicCircle; m_stats.noTheMagicCircle++; break; }		// The Magic Circle
					currentGame = GamesPlayed::TheLastOfUs;																		// The Last of Us
					m_stats.noTheLastOfUs++;
					break;
				}
				case 'W': {currentGame = GamesPlayed::Wordfeud; m_stats.noWordFeud++; break; }									// Wordfeud
				default:
				{
					std::cout << "[DataManager][SetGamesPlayed] Discarded value [non-mapped game]: " << value << std::endl;
					return false;
				}
			}

		//	std::cout << "Current value: "<< s.getPropOfType(PropertyIndex::PI_GamesPlayed).value << " to which we add: "<<currentGame<< std::endl;

			s.addGame(currentGame);
		}

		return true;
	}
	
	std::cout << "[DataManager][SetGamesPlayed] Discarded value [no games provided] " << value << std::endl;
	return false;
}

bool DataManager::setGender(Student & s, const std::string& value)
{	
	if (!value.empty()) {
		
		Gender gender;
		char startChar = tolower(value[0]);

		switch (startChar)
		{
			case 'm': 
			{
				gender = Gender::Male;
				m_stats.noMale++;
				break;
			}
			case 'f': 
			{
				if (value[1] == 'l') { gender = Gender::Other_Gender; m_stats.noOther++; break; }	// Fluid
				gender = Gender::Female; 
				m_stats.gender_noFemale++;
				break; 
			}
			case 'w': 
			{
				gender = Gender::Female;
				m_stats.gender_noFemale++;
				break; 
			}
			default: 
			{ 
				gender = Gender::Other_Gender; 
				m_stats.noOther++;
				break;
			}
		}

		s.setPropertyOfType(PropertyIndex::PI_Gender, gender);
		return true;
	}

	std::cout << "[DataManager][SetGender] Discarded value [no gender provided] "<< value << std::endl;
	return false;
	
}

bool DataManager::setOS(Student & s, const std::string& value)
{
	if (!value.empty())
	{
		OS os;

		switch (value[0])
		{
			case 'A': {os = OS::Android; break; }
			case 'i': {os = OS::iOS; break; }
			case 'W': {os = OS::Windows; break; }
			case 'm': {os = OS::macOS; break; }
			default: 
			{
				std::cout << "[DataManager][SetOS] Discarded value [unhandled OS value]: " << value << std::endl;
			}
		}

		s.setPropertyOfType(PropertyIndex::PI_OS, os);
	}
	else 
	{
		std::cout << "[DataManager][SetOS] Discarded value [no OS provided] " << value << std::endl;
		return false;
	}
	
	return true;
}


void DataManager::initialize_students()
{
	std::vector<std::vector<std::string>> data = m_csvReader.read_csv();
	m_students = new std::vector<Student>(0);

	for (auto const& row : data)
	{
		Student s;
		if (!setAgeRange(s, row[Labels::Label_Age])) continue;
		if (!setCourseReason(s, row[Labels::Label_CourseReason])) continue;
		if (!setDegree(s, row[Labels::Label_Degree])) continue;
		if (!setGamesPlayed(s, row[Labels::Label_GamesPlayed])) continue;
		if (!setGender(s, row[Labels::Label_Gender])) continue;
		if (!setOS(s, row[Labels::Label_PrefferedOS])) continue;

		m_students->emplace_back(s);
		m_stats.total_no_students++;
	}

	//TODO stats not done right, since instance might be discarded after stat data entered

//	display_students();
//	display_data();
//	display_stats();
	
}

/* Used for clasifier algorithms (ID3, kNN) */
const std::vector<Student*> DataManager::construct_training_set(const int size) const
{
	std::vector<Student*> training_set;

	if (m_students == nullptr || (*m_students).size() == 0)
	{
		std::cerr << "[DataManager][GetTrainingSet] Students not initialized." << std::endl;
		return training_set;
	}

	if (size >= (*m_students).size())
	{
		std::cerr << "[DataManager][GetTrainingSet] Trying to construct training set larger than total set." << std::endl;
		return training_set;
	}

	/* Set up random generator: Uniform distribution about the entire set of students */
	std::random_device randomDevice;											// generate seed
	std::mt19937 engine(randomDevice());										// mersenne_twister_engine to which we feed the seed
	std::uniform_int_distribution<int> dist(0, (*m_students).size() - 1);		// initialize distribution from 0 to the max no of students we have		

	std::set<int> randomIndexes;

	/* Make sure we only add unique instances of students to training set */
	while (randomIndexes.size() < size)
	{
		int randomIndex = dist(engine);

		if (randomIndexes.find(randomIndex) == randomIndexes.end())
		{
			randomIndexes.insert(randomIndex);
			training_set.emplace_back(&((*m_students)[randomIndex]));				// add pointer to random student into training set 
		}
	}

	return training_set;
}

void DataManager::display_data(const std::vector<std::vector<std::string>>& data)
{
	if (data.size() > 0) 
	{
		for (auto const& row : data) {
			std::cout << "Student: ";
			for (auto const& attr : row) {
				std::cout << attr << " - ";
			}
			std::cout << std::endl << std::endl;
		}
	}
	else 
	{
		std::cout << "No data loaded." << std::endl;
	}
	
}

void DataManager::display_students()
{
	for (auto const& student : *m_students) 
	{
		std::cout << "Student: " << student.getPropOfType(PropertyIndex::PI_AgeRange).value << " "<< student.getPropOfType(PropertyIndex::PI_OS).value << " "<<std::endl;
	}

	std::cout << "Total of: " << (*m_students).size() << std::endl;
}

void DataManager::display_stats()
{
	std::cout << "---------------------- Stats ----------------------" << std::endl;
	std::cout << " Total rows: " << m_stats.total_no_rows << std::endl;
	std::cout << " Total students: " << m_stats.total_no_students << std::endl;
	std::cout << std::endl;
	std::cout << " Male: " << m_stats.noMale << std::endl;
	std::cout << " Female:" << m_stats.gender_noFemale << std::endl;
	std::cout << " Other: " << m_stats.noOther << std::endl;
	std::cout << std::endl;
	std::cout << " No games played: " << m_stats.noNoGamesPlayed << std::endl;
	std::cout << " AngryBirds: " << m_stats.noAngryBirds << std::endl;
	std::cout << " Battlefield4: " << m_stats.noBattlefield << std::endl;
	std::cout << " Bloodthrone: " << m_stats.noBloodthrone << std::endl;
	std::cout << " CallOfDuty: " << m_stats.noCallOfDuty << std::endl;
	std::cout << " CandyCrush: " << m_stats.noCandyCrush << std::endl;
	std::cout << " CSGO: " << m_stats.noCSGO << std::endl;
	std::cout << " DragonAge: " << m_stats.noDragonAge << std::endl;
	std::cout << " Farmville: " << m_stats.noFarmville << std::endl;
	std::cout << " Fallout4: " << m_stats.noFallout << std::endl;
	std::cout << " Fifa2017: " << m_stats.noFifa << std::endl;
	std::cout << " GoneHome: " << m_stats.noGoneHome << std::endl;
	std::cout << " HerStory: " << m_stats.noHerStory << std::endl;
	std::cout << " Journey: " << m_stats.noJourney << std::endl;
	std::cout << " LifeIsStrange: " << m_stats.noLifeIsStrange << std::endl;
	std::cout << " Minecraft: " << m_stats.noMinecraft << std::endl;
	std::cout << " RiseOfTombRaider: " << m_stats.noRiseOfTombRaider << std::endl;
	std::cout << " RocketLeague: " << m_stats.noRocketLeague << std::endl;
	std::cout << " StanleyParable: " << m_stats.noStanleyParable << std::endl;
	std::cout << " StarWarsBattlefield: " << m_stats.noStarWarsBattlefield << std::endl;
	std::cout << " TheWitness: " << m_stats.noTheWitness << std::endl;
	std::cout << " TheLastOfUs: " << m_stats.noTheLastOfUs << std::endl;
	std::cout << " TheMagicCircle: " << m_stats.noTheMagicCircle << std::endl;
	std::cout << " Wordfeud: " << m_stats.noWordFeud << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
}


DataManager::~DataManager()
{
	if (m_students != nullptr) delete m_students;
}
