#pragma once

#include <nlohmann/json.hpp>
#include <iostream>

#include "JsonHandler.h"
#include "CurlGetter.h"

class PaidApiJsonHandler : public JsonHandler
{
public:
	PaidApiJsonHandler();
	void updateCurrency() override;
	const CurrenciesData& getCurrency() override;
	void showCurrency() override;
private:
	const Curl m_curl;
	CurrenciesData m_data;


};

