#pragma once
#include "Events/Event.h"
#include "Rest/Restaurant.h"
class PromoteEvent:public Event
{
//info of the event wanted to be promoted
	double Extra_Money;
public:
	PromoteEvent(int eTime, int oID, double m);

	virtual void Execute(Restaurant* pRest);
};

