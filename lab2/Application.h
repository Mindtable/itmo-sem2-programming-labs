#pragma once

#include <iostream>
#include "CurlGetter.h"
#include "Statistics.h"
#include "JsonHandler.h"
#include "FabricJsonHandler.h"

#include <chrono>
#include <thread>
#include <Windows.h>



class Application
{
public:
	Application(ApiType type);
	void run();
private:
	smartJsonPtr m_JsonHandler;
	std::map<std::string, Statistics> m_Stats;
};

