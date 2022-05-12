#pragma once

#include <map>
#include <string>

using CurrenciesData = std::map<std::string, double>;

enum class ApiType
{
	Free,
	Paid
};

class JsonHandler
{
public:
	virtual ~JsonHandler() {};
	virtual void updateCurrency() = 0;
	virtual const CurrenciesData& getCurrency() = 0;
	virtual void showCurrency() = 0;
};

