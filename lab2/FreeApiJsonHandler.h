#pragma once

#include <nlohmann/json.hpp>
#include <iostream>

#include "JsonHandler.h"
#include "CurlGetter.h"



class FreeApiJsonHandler : public JsonHandler
{
public:
	//qq
	FreeApiJsonHandler();
	void updateCurrency() override;
	const CurrenciesData& getCurrency() override;
	void showCurrency() override;
private:
	const Curl m_curl;
	CurrenciesData m_data;

	
};

