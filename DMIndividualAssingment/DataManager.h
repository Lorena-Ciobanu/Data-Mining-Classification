#pragma once
#include <random>
#include <set>

#include "CSVReader.h"
#include "Student.h"
#include "Labels.h"
#include "Stats.h"

#include "AgeGroup.h"
#include "CourseReason.h"
#include "Degree.h"
#include "GamesPlayed.h"
#include "Gender.h"
#include "Labels.h"
#include "OS.h"
#include "ProgLanguage.h"
#include "Topic.h"

/* Constants */
const int AGE_RANGE_LOW = 20;
const int AGE_RANGE_MID = 25;
const int AGE_RANGE_HIGH = 30;
const int AGE_MAX_AGE = 50;

// Could make singleton so as to ever only have on instance of student data
// however, in current implementation allows us to have data from different files

/* Class responsable for constructing and maintaining Student data
	-> using data recieved from CSVReader
*/
class DataManager
{
private:

	std::vector<Student> *m_students;
	Stats m_stats;

	CSVReader m_csvReader;

	void initialize_students();

	/* Student construction functions  */
	bool setAgeRange(Student& s, const std::string& value);
	bool setCourseReason(Student& s, const std::string& value);
	bool setDegree(Student& s, const std::string& value);
	bool setGamesPlayed(Student& s, const std::string& value);
	bool setGender(Student& s, const std::string& value);
	bool setOS(Student& s, const std::string& value);

public:

	/* Constructor - Responsable for calling initialize students function  */
	DataManager(std::string filename) : m_csvReader(filename, m_stats) { initialize_students(); }

	/* Getter functions */
	const std::vector<Student>* get_students() const { return m_students; }
	const Stats& get_stats() const { return m_stats; }
	

	/* Construct training set (returns a vector of pointers to original student vector) */
	const std::vector<Student*> construct_training_set(const int size) const;


	/* Display Functions [Only used for debug purposes] */
	void display_data(const std::vector<std::vector<std::string>>& data);

	void display_students();

	void display_stats();


	/* Destructor */
	~DataManager();
};

