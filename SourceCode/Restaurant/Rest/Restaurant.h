#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\LinkedList.h"
#include "..\Generic_DS\Node.h"
#include "..\QueueP.h"
#include "Order.h"
#include <fstream>

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Queue<Cook*> CookN;
	Queue<Cook*> CookV;
	Queue<Cook*> CookG;
	LinkedList<Order*>Orders_N;
	QueueP<Order*>Orders_V;
	Queue<Order*>Orders_G;
	Queue<Order*> FinishedOrders;
	LinkedList<Order*> InServiceOrders;
	QueueP<Order*> UrgentOrders;
	int Break_Order;
	int AutoP;
	int OrderNumber;
	int N, G, V;//The Number of cooks of each type
	int Normal_Orders=0, Vip_Orders=0, Vegan_Orders=0;
	string File_Name;
	int Num = 0;
	int Auto_p = 0;
	
	//health problems variables
	float injuryProp;
	int restTime;
	int VIP_WT;
	int urgentnum=0;
	int injurednum=0;
public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void Add_Events();


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//
	void Add_Cooks(int n, int v, int g, int SN_min,int SN_max,int SG_min, int SG_max,int SV_min,int SV_max, int BN_min, int BN_max, int BG_min,int BG_max,int BV_min,int BV_max);
	void Add_Normal_Orders(Order* pOrder);
	void Add_VIP_Orders(Order* pOrder);
	void Add_Veg_Orders(Order* pOrder);
	void Delete_Order(int ID);
	void Promote_Order(int ID, int arrival_time, double extra_money);

	bool ServeVIPOrder(Order*& pOrder,const int& t);
	bool ServeVeganOrder(Order* pOrder, const int& t);
	bool ServeNormalOrder(Order* pOrder, const int& t);
	bool ChooseCook(Order* pOrder,const int& t);
	
	bool EventsOrdersFound();//to each if there is still orders or events in the resturant
	void CheckOrder(int t);
	void Serving_Transfer();
	void Finished_Transfer();
	void Cook_Dute();//to check the cooks those have orders and make them finish plates
	void CooksInBreak();//made to increment the breaktime of the cook in break by one 
	void AutoP_Check(int t);//to check for the auto promotion of normal orders
	void Increase_WT();
	void Output_File(string name);
	
	//Gui porpuse
	void Num_WT_Orders();//to print the waiting number of orders of each type
	void Num_Cooks_Able();//to print the number of cooks available of each type
	void Assign(Cook* pC, Order* pO,int n);//to print the assigned orders info
	void Served_num();//to ptint number of served orders of each type so far
	void checkHealth();
	void CheckUrgentOrders(int t);
	bool cutbreaks();
	void calcinjuredcooks();
	/*void ChooseUrgentCook(Order* pOrder, const int& t);
	void ServeUrgentOrder(Order* pOrder, const int& t);*/
};

#endif