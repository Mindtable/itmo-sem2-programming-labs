#include "Statistics.h"

Statistics::Statistics(const std::string& name) : m_Name(name), m_Summary(0.0), 
                                                  m_Count(0), m_RD(), m_RNG(m_RD()),
	                                              m_RandomMedian(0, 9999)
{
	m_Reservoir.reserve(1024);
}

Statistics::~Statistics()
{
	std::sort(m_Reservoir.begin(), m_Reservoir.end());

	double median;
	size_t sz = m_Reservoir.size();
	if (sz % 2 == 0 && sz != 0) 
	{
		median = (m_Reservoir[sz / 2] + m_Reservoir[sz / 2 - 1]) / 2;
	}
	else 
	{
		median = m_Reservoir[sz / 2];
	}

	std::cout << "Valute name: " << m_Name << std::endl;
	std::cout << "Average value: " << m_Summary / m_Count << std::endl;
	std::cout << "Median value: " << median << std::endl;
}

void Statistics::insert(long double number)
{
	m_Summary += number;

	if (m_Count < 10000) 
	{
		m_Reservoir.push_back(number);
	}
	else 
	{
		m_Reservoir.at(m_RandomMedian(m_RNG)) = number;
	}

	++m_Count;
}
