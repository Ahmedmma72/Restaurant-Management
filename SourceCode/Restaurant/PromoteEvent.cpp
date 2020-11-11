#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(int eTime, int oID, double m) :Event(eTime, oID)
{
	Extra_Money = m;
}

void PromoteEvent::Execute(Restaurant* pRest)
{
	pRest->Promote_Order(this->getOrderID(), this->getEventTime(), Extra_Money);
}
