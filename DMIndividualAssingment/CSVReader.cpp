#include "stdafx.h"
#include "CSVReader.h"



/* CSVReader */

std::vector<std::vector<std::string>> CSVReader::read_csv()
{
	//m_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::vector<std::vector<std::string>> data;

	try
	{
		m_stream.open(m_filename);

		CSVRow row;
		m_stream >> row;	// Discard first row [headers]

		
		while (m_stream >> row) {
			data.push_back(row.getData());
			m_stats.total_no_rows++;
		}
	}

	catch (std::ifstream::failure e)
	{
		std::cerr << "[CSVReader] Exception reading file " << e.what() << std::endl;
	}

	return data; 
	//Should have insted used a pointer to the data and saved it there, insed of returning a new instance here
}



/* CSVRow */

// Normaly way better to read entire file and parse insted of line by line
void CSVRow::readNextRow(std::istream & stream)
{
	try
	{
		std::string row;
		std::getline(stream, row);

		std::stringstream rowStream(row);
		std::string attribute;
		
		m_rowData.clear();

		/* 
			Due to structure of the .csv file (" ... " , " ... " ), read until " is found
			-> If it's a starting comma => discard substring 
			-> Otherwise save data 
		*/

		bool startComma = true;								

		while (std::getline(rowStream, attribute, '"'))
		{
			if (!startComma) m_rowData.push_back(attribute);
			startComma = !startComma;
		}
	}

	catch (std::exception& e)
	{
		std::cerr << "[CSVReader] Exception: " << e.what() << std::endl;
	}
}
