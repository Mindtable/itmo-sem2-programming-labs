#pragma once

#include <iostream>
#include <string>
#include <random>
#include <vector>

class Statistics
{
public:
	Statistics(const std::string &name);
	~Statistics();

	void insert(long double number);

private:
	std::string m_Name;
	long double m_Summary;
	size_t m_Count;

	std::vector<double> m_Reservoir;

	std::random_device m_RD;
	std::mt19937 m_RNG;
	std::uniform_int_distribution<int> m_RandomMedian;
};

