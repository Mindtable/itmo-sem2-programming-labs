#include "Application.h"

Application::Application(ApiType type)
{
	m_JsonHandler = FabricJsonHandler::generate(type);
	m_Stats.emplace("USD", std::string("USD"));
	m_Stats.emplace("EUR", std::string("EUR"));
}

void Application::run()
{
	bool exitNeeded = false;

	std::thread thr([&exitNeeded]()
		{
			std::string input;
			while (std::cin >> input && input != "#");
			exitNeeded = true;
		});

	while (!exitNeeded)
	{
		m_JsonHandler->updateCurrency();
		m_JsonHandler->showCurrency();
		auto &data = m_JsonHandler->getCurrency();

		for (const auto& mapElem : data)
		{
			m_Stats.at(mapElem.first).insert(mapElem.second);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		system("cls");
	}
	thr.join();
}
