#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<=ID<=999
	type = r_Type;
	status = WAIT;
	waitingTime = 0;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

void Order::SetType(ORD_TYPE l)
{
	type = l;
}





void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::setMoney(double m)
{
	totalMoney = m;
}

double Order::getMoney() const
{
	return totalMoney;
}

void Order::setSize(int s)
{
	size_Dishes = s;
}

int Order::getSize() const
{
	return size_Dishes;
}


void Order::setArrival(int a)
{
	ArrTime = a;
}

int Order::getArrival() const
{
	return ArrTime;
}

void Order::setServ(int a)
{
	ServTime = a;
}

int Order::getServ() const
{
	return ServTime;
}

void Order::setFinish(int a)
{
	FinishTime = a;
}

int Order::getFinish() const
{
	return FinishTime;
}

void Order::setWT(int a)
{
	if (getStatus() == SRV || getStatus() == DONE) return;
	if (a >= 0) waitingTime = a;
	else waitingTime = 0;
	//setStatus(SRV);
}

int Order::getWT() const
{
	return waitingTime;
}

