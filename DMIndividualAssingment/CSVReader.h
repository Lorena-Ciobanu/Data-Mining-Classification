#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

#include "Stats.h"


/* Row class to read data to */
/* Temp class used to store data read per csv row */
class CSVRow
{
private:
	std::vector<std::string> m_rowData;

public:

	void readNextRow(std::istream& stream);

	std::size_t size() const { return m_rowData.size(); }
	std::string const& operator[](std::size_t index) const { return m_rowData[index]; }

	std::vector<std::string> getData() const { return m_rowData; }
};

/* CSV Reader */
/* Class responsable for reading data from .csv file */
class CSVReader
{
private:

	std::string m_filename;
	std::ifstream m_stream;
	Stats& m_stats;

public:

	/* Constructor */
	CSVReader(std::string filename, Stats& stats) : m_filename(filename), m_stats(stats) {}

	/* Read CSV file (called from inside DataManager class) */
	std::vector<std::vector<std::string>> read_csv();

	/* Overload operator in order to read directly into CSVRow class*/
	friend std::istream& operator>>(std::istream& str, CSVRow& data);

	/* Destructor */
	~CSVReader() {}
};


/* Overload >> operator for istream to read directly into CSVRow */
inline std::istream& operator>>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}