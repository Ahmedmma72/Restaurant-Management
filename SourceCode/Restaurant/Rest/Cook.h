#pragma once

#include "..\Defs.h"
#include "Order.h"

#pragma once
class Cook
{
	int ID;				//cook ID.
	ORD_TYPE type;		//for each order type there is a corresponding type (VIP, Normal, Vegan).
	int speed;			//dishes it can prepare in one clock tick (in one timestep).
	Order* pOrder;		//the order being serviced.
	bool busy;			//is the cook busy working? or not.
	int servingTime;    //counter increamted to show that the current order is still in service.

	int orderToRest;	//how many orders to do before rest
	int break_period;	//time is taken as break.
	bool isBreak;		//is the cook in break? or not.
	int dishesPrep;		//dishes prepared by the cook from his last break or up till now.
	int breakTime;		//the time taken during his break;
						//shouldn't exceed the break_period (e.g. like a counter)

	bool injured;
	bool atRest;
	int restTime;
	int spentRest;
	bool gotinjured_before;
	bool was_minimum = false;
	bool injuredserveurgent = false;
	bool speedwasodd = false;
public:
	Cook();
	Cook(int i, ORD_TYPE t, int s,int otr,int b_period,bool b);
	virtual ~Cook();

	void setID(int);
	int GetID() const;

	void setType(ORD_TYPE);
	ORD_TYPE GetType() const;
	
	
	void setBP(int b_period);
	int getBP();

	void setBusy(bool b);
	bool getBusy();

	void TakeBreak();
	bool getBreak() const;

	void serveNewOrder(Order*& ptr,const int& t);
	void serveCurenntOrder();

	void setInjured(bool b);
	bool getInjured(); 

	void setRest(bool b);
	bool getRest();

	void setRestTime(int i);
	void cutbreak();
	void setinjuredbefore();
	bool gotinjuredbefore();
	void set_inj_servUrge();
};
