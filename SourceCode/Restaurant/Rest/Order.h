#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include "..\Generic_DS\Queue.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	int waitingTime; 


	//
	// TODO: Add More Data Members As Needed
	//
	int size_Dishes;
	


public:
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;
	void SetType(ORD_TYPE l);

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//
	void setMoney(double m);
	double getMoney() const;

	void setSize(int s);
	int getSize() const;

	void setArrival(int a);
	int getArrival() const;

	void setServ(int a);
	int getServ() const;
	
	void setFinish(int a);
	int getFinish() const;

	void setWT(int a);
	int getWT() const;
};

#endif