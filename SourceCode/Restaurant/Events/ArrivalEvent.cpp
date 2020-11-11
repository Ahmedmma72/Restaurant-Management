#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include <fstream>


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int s, double m):Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = m;
	size = s;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order* pOrder = new Order(this->getOrderID(), OrdType);
	pOrder->setArrival(this->getEventTime());
	pOrder->setSize(size);
	pOrder->setMoney(OrdMoney);
	pOrder->setStatus(WAIT);
	if (OrdType == TYPE_NRM) {
		pRest->Add_Normal_Orders(pOrder);
	}
	else if (OrdType == TYPE_VIP) {
		pRest->Add_VIP_Orders(pOrder);
	}
	else if (OrdType == TYPE_VGAN) {
		pRest->Add_Veg_Orders(pOrder);
	}
}
