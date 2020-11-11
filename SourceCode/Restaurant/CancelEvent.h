#pragma once
#include "Events/Event.h"
class CancelEvent:public Event
{
	//info of the order wanted to be canceled
public:
	CancelEvent(int eTime, int oID);

	virtual void Execute(Restaurant* pRest);	//override execute function
};

