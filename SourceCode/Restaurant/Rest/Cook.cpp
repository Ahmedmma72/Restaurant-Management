#include "Cook.h"
#include "Order.h"
#include<iostream>

using namespace std;

Cook::Cook()
{
}

Cook::Cook(int i, ORD_TYPE t, int s, int otr, int b_period, bool b)
{
	ID = i;
	type = t;
	speed = s;
	orderToRest = otr;
	break_period = b_period;
	busy = b;
	servingTime = 0;
	dishesPrep = 0;
	isBreak = false;
	pOrder = nullptr;
	breakTime = 0;
	injured = false;
	atRest = false;
	restTime = 0;
	spentRest = 0;
	gotinjured_before = false;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setBP(int b_period)
{
	break_period = b_period;
}

int Cook::getBP()
{
	return break_period;
}

void Cook::setBusy(bool b)
{
	busy = b;
}

bool Cook::getBusy()
{
	return busy;
}
 


void Cook::TakeBreak()		//handels the cook break each time called.
{
	if (injured)
	{
		if (!atRest&&busy)
		{
			return;
		}
		else if (!atRest&&!busy)
		{
			setRest(true);
			spentRest++;
			dishesPrep = 0;
		}
		else if (atRest && spentRest < restTime + 1)
		{
			spentRest++;
		}
		else
		{

			setRest(false);
			setInjured(false); 
			spentRest = 0;
			
		}
	}
	else
	{
		if (dishesPrep >= orderToRest) 
		{
			isBreak = true;
			breakTime++;
			dishesPrep = 0;
		}
		else if (isBreak && breakTime < break_period + 1)
		{
			breakTime++;
		}
		else
		{
			isBreak = false  ;
			breakTime = 0;
			if (injuredserveurgent)
			{
				injuredserveurgent=false;
				if (!was_minimum)
				{
					if (speedwasodd)
					{
						speed = speed * 2 + 1;
					}
					else
					{
						speed = speed * 2;
					}
				}
			}
		}
	}
}

bool Cook::getBreak() const
{
	return isBreak;
}


void Cook::serveNewOrder(Order*& ptr, const int& t)	//for new orders when the cook is free and not in break.
{
	this->setBusy(true);
	ptr->setStatus(SRV);
	//ptr->setWT(t - ptr->getArrival());
	this->pOrder = ptr;
	dishesPrep++;
	serveCurenntOrder();
}
 
void Cook::serveCurenntOrder() //for the current order.
{
	if (pOrder->getSize() > 0) {	//the order has number of dishes 

		pOrder->setSize(pOrder->getSize() - speed);//decrement of the order size with the cook speed
		servingTime++;

	}
	else {//the order size can't be negative so it's finished and the cook returned to be free or break.
		pOrder->setFinish(pOrder->getArrival() + pOrder->getWT() + servingTime);
		pOrder->setStatus(DONE);
		pOrder->setServ(servingTime);
		servingTime = 0;
		pOrder = nullptr;
		this->setBusy(false); 
		TakeBreak();
	}
}


void Cook::setInjured(bool b) {
	if (b == true)
	{
		injured = true;
		if (speed > 1)
		{
			if (speed % 2 != 0)
			{
				speedwasodd = true;
			}
			speed = speed / 2;
		}
		else
		{
			speed = 1;
			was_minimum = true;
		}
	}
	else {
		injured = false;
		if(!was_minimum)
		{
			if (speedwasodd)
			{
				speed = speed * 2 + 1;
			}
			else 
			{
				speed = speed * 2;
			}
		}
		
	}
}
bool Cook::getInjured() {
	return injured;
}

void Cook::setRest(bool b) {
	atRest = b;
}
bool Cook::getRest() {
	return atRest;
}

void Cook::setRestTime(int i) {
	restTime = i;
}

void Cook::cutbreak()
{
	isBreak = false;
	breakTime = 0;
	setRest(false);
	spentRest = 0;
	injured = false;
}
void Cook::setinjuredbefore()
{
	gotinjured_before = true;
}

bool Cook::gotinjuredbefore()
{
	return gotinjured_before;
}

void Cook::set_inj_servUrge()
{
	injuredserveurgent = true;
}

 