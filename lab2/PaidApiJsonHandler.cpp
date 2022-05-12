#include "PaidApiJsonHandler.h"

PaidApiJsonHandler::PaidApiJsonHandler()
:m_curl("http://api.currencylayer.com/live?access_key=dee259d7d6573750110a00338bc5dc07&currencies=RUB,EUR")
{}

void PaidApiJsonHandler::updateCurrency()
{
	using json = nlohmann::json;

	std::string result;
	result = m_curl.getJSONstring();

	json ValuteJSON = json::parse(result);

	m_data["USD"] = ValuteJSON["quotes"]["USDRUB"];
	double eurValue = ValuteJSON["quotes"]["USDEUR"];
	m_data["EUR"] = (1.0 / eurValue) * m_data["USD"];
}

const CurrenciesData& PaidApiJsonHandler::getCurrency()
{
	return m_data;
}

void PaidApiJsonHandler::showCurrency()
{
	std::cout << "EURO: " << m_data["EUR"] << std::endl;
	std::cout << "AMERICAN DOLLAR: " << m_data["USD"] << std::endl;
}
