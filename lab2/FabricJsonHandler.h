#pragma once

#include <memory>

#include "JsonHandler.h"
#include "FreeApiJsonHandler.h"
#include "PaidApiJsonHandler.h"

using smartJsonPtr = std::shared_ptr<JsonHandler>;

class FabricJsonHandler
{
public:
	static smartJsonPtr generate(ApiType type);
};

