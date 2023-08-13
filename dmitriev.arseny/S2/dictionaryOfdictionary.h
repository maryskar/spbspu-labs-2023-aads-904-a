#ifndef DICTIONARYOFDICTIONARY_H
#define DICTIONARYOFDICTIONARY_H

#include "dictionary.h"
#include <iostream>
#include <sstream>
#include <string>

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare = std::less< > >
	class DictionaryOfDictionary
	{
	public:
		using basicDic = Dictionary< Key, Value, Compare >;
		using basicIterator = typename basicDic::iterator;
		using basicConstIterator = typename basicDic::constIterator;
		using iterator = typename Dictionary< std::string, basicDic >::iterator;
		using constIterator = typename Dictionary< std::string, basicDic >::constIterator;

		DictionaryOfDictionary(std::istream& input):
			m_dicOfDic(dicInit(input))
		{}

		DictionaryOfDictionary(const DictionaryOfDictionary& other):
			m_dicOfDic(other.m_dicOfDic)
		{}
		DictionaryOfDictionary(DictionaryOfDictionary&& other):
			m_dicOfDic(other.m_dicOfDic)
		{}

		~DictionaryOfDictionary() = default;

		void doTheTasksFromInp(std::istream& input, std::ostream& out)
		{
			std::string line;
			while (std::getline(input, line))
			{
				if (line.find_first_not_of(" \n") == std::string::npos)
				{
					continue;
				}
				std::stringstream ss(line);
				std::string command = "";
				ss >> command;

				if (command == "print")
				{
					std::string datasetName = "";
					ss >> datasetName;
					print(out, datasetName);
				}
				else if(command == "complement")
				{
					std::string newDatasetName = "";
					std::string lhs = "";
					std::string rhs = "";

					ss >> newDatasetName >> lhs >> rhs;
					complement(newDatasetName, lhs, rhs);
				}
				else if (command == "intersect")
				{
					std::string newDatasetName = "";
					std::string lhs = "";
					std::string rhs = "";

					ss >> newDatasetName >> lhs >> rhs;
					intersect(newDatasetName, lhs, rhs);
				}
				else if (command == "union")
				{
					std::string newDatasetName = "";
					std::string lhs = "";
					std::string rhs = "";

					ss >> newDatasetName >> lhs >> rhs;
					unionDictionary(newDatasetName, lhs, rhs);
				}
				else
				{
					out << "<INVALID COMMAND>" << '\n';
				}
			}
		}

		void print(std::ostream& out)
		{
			for (iterator it = m_dicOfDic.begin(); m_dicOfDic.isExist(it); it++)
			{
				out << it->first << ' ';

				basicDic datasetDic = it->second;
				basicIterator itBasic = datasetDic.begin();
				if (!datasetDic.isExist(itBasic))
				{
					out << "<EMPTY>" << '\n';
				}
				else
				{
					out << itBasic->first << ' ' << itBasic->second;
					itBasic++;
					for (; datasetDic.isExist(itBasic); itBasic++)
					{
						out << ' ' << itBasic->first << ' ' << itBasic->second;
					}
					out << '\n';
				}

			}
		}
		void print(std::ostream& out, std::string datasetName)
		{
			for (iterator it = m_dicOfDic.begin(); m_dicOfDic.isExist(it); it++)
			{
				if (it->first == datasetName)
				{
					out << it->first << ' ';

					basicDic datasetDic = it->second;
					basicIterator itBasic = datasetDic.begin();

					if (!datasetDic.isExist(itBasic))
					{
						out << "<EMPTY>" << '\n';
					}
					else
					{
						out << itBasic->first << ' ' << itBasic->second;
						itBasic++;
						for (; datasetDic.isExist(itBasic); itBasic++)
						{
							out << ' ' << itBasic->first << ' ' << itBasic->second;
						}
						out << '\n';
					}
				}
			}
		}

		void complement(std::string newDatasetName, std::string lhs, std::string rhs)
		{
			basicDic newDic;
			newDic.complement(m_dicOfDic[lhs], m_dicOfDic[rhs]);
			
			m_dicOfDic.insert({newDatasetName, newDic});
		}
		void intersect(std::string newDatasetName, std::string lhs, std::string rhs)
		{
			basicDic newDic;
			newDic.intersect(m_dicOfDic[lhs], m_dicOfDic[rhs]);

			m_dicOfDic.insert({newDatasetName, newDic});
		}
		void unionDictionary(std::string newDatasetName, std::string lhs, std::string rhs)
		{
			basicDic newDic;
			newDic.unionDictionary(m_dicOfDic[lhs], m_dicOfDic[rhs]);

			m_dicOfDic.insert({newDatasetName, newDic});
		}

	private:
		Dictionary< std::string, basicDic > m_dicOfDic;

		Dictionary< std::string, basicDic > dicInit(std::istream& input)
		{
			Dictionary< std::string, basicDic > newDD;

			std::string line;
			while (std::getline(input, line))
			{
				if (line.find_first_not_of(" \n") == std::string::npos)
				{
					continue;
				}
				std::stringstream ss(line);
				std::string datasetName;
				ss >> datasetName;
	
				basicDic datasetDic;
				Key key;
				Value value;
				while (ss >> key >> value)
				{
					datasetDic.insert({key, value});
				}

				newDD.insert({datasetName, std::move(datasetDic)});
			}

			return newDD;
		}
	};
}

#endif
