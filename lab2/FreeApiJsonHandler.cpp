#include "FreeApiJsonHandler.h"

FreeApiJsonHandler::FreeApiJsonHandler()
: m_curl("https://www.cbr-xml-daily.ru/daily_json.js")
{}

void FreeApiJsonHandler::updateCurrency()
{
	using json = nlohmann::json;

	std::string result;
	result = m_curl.getJSONstring();

	json ValuteJSON = json::parse(result);

	m_data["USD"] = ValuteJSON["Valute"]["USD"]["Value"];
	m_data["EUR"] = ValuteJSON["Valute"]["EUR"]["Value"];
}

const CurrenciesData& FreeApiJsonHandler::getCurrency()
{
	return m_data;
}

void FreeApiJsonHandler::showCurrency()
{
	std::cout << "EURO: " << m_data["EUR"] << std::endl;
	std::cout << "AMERICAN DOLLAR: " << m_data["USD"] << std::endl;
}
