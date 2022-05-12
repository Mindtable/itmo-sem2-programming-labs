#include "FabricJsonHandler.h"

smartJsonPtr FabricJsonHandler::generate(ApiType type)
{
	switch (type)
	{
	case ApiType::Free:
		return smartJsonPtr(new FreeApiJsonHandler);
		break;
	case ApiType::Paid:
		return smartJsonPtr(new PaidApiJsonHandler);
		break;
	default:
		throw std::exception();
		break;
	}
}
