#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancelEvent.h"
#include "..\PromoteEvent.h"


Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	srand(time(NULL));
	pGUI = new GUI;
	pGUI->PrintMessage("Enter The Name Of The File Please, Then Press Enter Button....", 1, 0);
	File_Name = pGUI->GetString();

	PROG_MODE mode = pGUI->getGUIMode();
	Add_Events();
	int CurrentTimeStep = 1;
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		while (EventsOrdersFound()) {
			string TS = "TimeStep: " + to_string(CurrentTimeStep);
			pGUI->PrintMessage(TS, 0, 0);
			pGUI->PrintMessage(TS, 1, 0);
			checkHealth();
			CooksInBreak();
			ExecuteEvents(CurrentTimeStep);
			Cook_Dute();
			CheckUrgentOrders(CurrentTimeStep);
			CheckOrder(CurrentTimeStep);
			Serving_Transfer();
			Finished_Transfer();
			Increase_WT();
			AutoP_Check(CurrentTimeStep);

			Num_WT_Orders();
			Num_Cooks_Able();
			Served_num();

			FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->waitForClick();
			pGUI->ResetDrawingList();

			CurrentTimeStep++;
			Num = 0;
		}
		pGUI->PrintMessage("", 0, 0);
		pGUI->PrintMessage("Enter The Name Of The  Output File Please, Then Press Enter Button....", 1, 0);
		File_Name = pGUI->GetString();
		Output_File(File_Name);
		break;
	case MODE_STEP:
		while (EventsOrdersFound()) {
			char timestep[10];
			itoa(CurrentTimeStep, timestep, 10);
			pGUI->PrintMessage(timestep, 0, 0);
			pGUI->PrintMessage(timestep, 1, 0);
			checkHealth();
			CooksInBreak();
			ExecuteEvents(CurrentTimeStep);
			Cook_Dute();
			CheckUrgentOrders(CurrentTimeStep);
			CheckOrder(CurrentTimeStep);
			Serving_Transfer();
			Finished_Transfer();
			Increase_WT();
			AutoP_Check(CurrentTimeStep);

			Num_WT_Orders();
			Num_Cooks_Able();
			Served_num();
			FillDrawingList();
			pGUI->UpdateInterface();
			Sleep(1000);
			pGUI->ResetDrawingList();

			CurrentTimeStep++;
			Num = 0;
		}
		pGUI->PrintMessage("", 0, 0);
		pGUI->PrintMessage("Enter The Name Of The  Output File Please, Then Press Enter Button....", 1, 0);
		File_Name = pGUI->GetString();
		Output_File(File_Name);
		break;
	case MODE_SLNT:
		while (EventsOrdersFound()) {
			char timestep[10];
			itoa(CurrentTimeStep, timestep, 10);
			pGUI->PrintMessage(timestep, 0, 0);
			pGUI->PrintMessage(timestep, 1, 0);
			checkHealth();
			CooksInBreak();
			ExecuteEvents(CurrentTimeStep);
			Cook_Dute();
			CheckUrgentOrders(CurrentTimeStep);
			CheckOrder(CurrentTimeStep);
			Serving_Transfer();
			Finished_Transfer();
			Increase_WT();
			AutoP_Check(CurrentTimeStep);
			pGUI->PrintMessage(timestep, 1, 0);
			Num_WT_Orders();
			Num_Cooks_Able();
			Served_num();
			pGUI->UpdateInterface();

			pGUI->ResetDrawingList();
			 
			CurrentTimeStep++;
			Num = 0;
		}
		pGUI->PrintMessage("", 0, 0);
		pGUI->PrintMessage("Enter The Name Of The  Output File Please, Then Press Enter Button....", 1, 0);
		File_Name = pGUI->GetString();
		Output_File(File_Name);
		break;
	};
}

void Restaurant::Add_Events()
{
	int BO, BN_min, BN_max, BG_min, BG_max, BV_min, BV_max, SN_min, SN_max, SG_min, SG_max, SV_min, SV_max;
	ifstream InFile;
	InFile.open(File_Name + ".txt");
	string found;
	if (InFile.is_open()) {
		InFile >> N >> G >> V >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max >> Break_Order >> BN_min >> BN_max >> BG_min >> BG_max >> BV_min >> BV_max >> injuryProp >> restTime >> AutoP >> VIP_WT >> OrderNumber;
		Add_Cooks(N, G, V, SN_min, SN_max, SG_min, SG_max, SV_min, SV_max, BN_min, BN_max, BG_min, BG_max, BV_min, BV_max);
		while (InFile >> found) {
			if (found == "R") {
				string type;
				Event* p_event;
				int id, arrive_time, money, size;
				InFile >> type >> arrive_time >> id >> size >> money;
				if (type == "N") {
					p_event = new ArrivalEvent(arrive_time, id, TYPE_NRM, size, money);
					Normal_Orders++;
				}
				else if (type == "V") {
					p_event = new ArrivalEvent(arrive_time, id, TYPE_VIP, size, money);
					Vip_Orders++;
				}
				else if (type == "G") {
					p_event = new ArrivalEvent(arrive_time, id, TYPE_VGAN, size, money);
					Vegan_Orders++;
				}
				EventsQueue.enqueue(p_event);
			}
			if (found == "X") {
				int id, arrive_time;
				InFile >> arrive_time >> id;
				CancelEvent* pX_event = new CancelEvent(arrive_time, id);
				EventsQueue.enqueue(pX_event);
			}
			if (found == "P") {
				int id, arrive_time, extra_Money;
				InFile >> arrive_time >> id >> extra_Money;
				PromoteEvent* pP_event = new PromoteEvent(arrive_time, id, extra_Money);
				EventsQueue.enqueue(pP_event);
			}
		}
	}

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//to add the arrived events 
	/*Event* pE;
	for (int i = 0; i < EventsQueue.getCount(); i++) {
		EventsQueue.dequeue(pE);
		pGUI->AddToDrawingList(pE);
		EventsQueue.dequeue(pE);
	}*/
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	Cook** Arr_CookG;
	int Cook_NumG = CookG.getCount();
	Arr_CookG = CookG.toArray();

	Cook** Arr_CookN;
	int Cook_NumN = CookN.getCount();
	Arr_CookN = CookN.toArray();

	Cook** Arr_CookV;
	int Cook_NumV = CookV.getCount();
	Arr_CookV = CookV.toArray();

	Cook* pC;

	for (int i = 0; i < Cook_NumN; i++) {
		pC = Arr_CookN[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {//not busy and not in break
			pGUI->AddToDrawingList(pC);
		}
	}
	for (int i = 0; i < Cook_NumG; i++) {
		pC = Arr_CookG[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {
			pGUI->AddToDrawingList(pC);
		}
	}
	for (int i = 0; i < Cook_NumV; i++) {
		pC = Arr_CookV[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {
			pGUI->AddToDrawingList(pC);
		}
	}
	pC = nullptr;
	for (int i = 0; i < Cook_NumN; i++) {
		pC = Arr_CookN[i];
		if ((pC->getBusy()) || (pC->getBreak())) {
			pGUI->AddToDrawingList(pC);
		}
	}
	for (int i = 0; i < Cook_NumG; i++) {
		pC = Arr_CookG[i];
		if ((pC->getBusy()) || (pC->getBreak())) {
			pGUI->AddToDrawingList(pC);
		}
	}
	for (int i = 0; i < Cook_NumV; i++) {
		pC = Arr_CookV[i];
		if ((pC->getBusy()) || (pC->getBreak())) {
			pGUI->AddToDrawingList(pC);
		}
	}

	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	Order** Arr_OrderG;
	int Order_NumG = Orders_G.getCount();
	Arr_OrderG = Orders_G.toArray();

	Order** Arr_OrderV;
	int Order_NumV = Orders_V.getCount();
	Arr_OrderV = Orders_V.toArray();

	Order** Arr_OrderN;
	int Order_NumN = Orders_N.getCount();
	Arr_OrderN = Orders_N.toArray();

	Order** Arr_OrderU;
	int Order_NumU = UrgentOrders.getCount();
	Arr_OrderU = UrgentOrders.toArray();

	Order* pO;

	for (int i = 0; i < Order_NumG; i++) {
		pO = Arr_OrderG[i];
		pGUI->AddToDrawingList(pO);
	}
	for (int i = 0; i < Order_NumV; i++) {
		pO = Arr_OrderV[i];
		pGUI->AddToDrawingList(pO);
	}
	for (int i = 0; i < Order_NumN; i++) {
		pO = Arr_OrderN[i];
		pGUI->AddToDrawingList(pO);
	}
	for (int i = 0; i < Order_NumU; i++) {
		pO = Arr_OrderU[i];
		pGUI->AddToDrawingList(pO);
	}

	pO = nullptr;
	//-----for drawing inservice orders-----//
	Order** Arr_InService;
	int Order_InService = InServiceOrders.getCount();
	Arr_InService = InServiceOrders.toArray();

	for (int i = 0; i < Order_InService; i++) {
		pO = Arr_InService[i];
		pGUI->AddToDrawingList(pO);
	}

	//-----for drawing finished orders-----//
	Order** Arr_Finished;
	int Order_Finished = FinishedOrders.getCount();
	Arr_Finished = FinishedOrders.toArray();
	for (int i = 0; i < Order_Finished; i++) {
		pO = Arr_Finished[i];
		pGUI->AddToDrawingList(pO);
	}
}

void Restaurant::Add_Cooks(int n, int v, int g, int SN_min, int SN_max, int SG_min, int SG_max, int SV_min, int SV_max, int BN_min, int BN_max, int BG_min, int BG_max, int BV_min, int BV_max)
{
	int id = 1;
	int sn, bn, sv, bv, sg, bg;
	for (n; n > 0; n--) {
		sn = rand() % (SN_max - SN_min + 1) + SN_min;
		bn = rand() % (BN_max - BN_min + 1) + BN_min;
		Cook* pCook = new Cook(id++, TYPE_NRM, sn, Break_Order, bn, false);
		CookN.enqueue(pCook);
	}
	for (v; v > 0; v--) {
		sv = rand() % (SV_max - SV_min + 1) + SV_min;
		bv = rand() % (BV_max - BV_min + 1) + BV_min;
		Cook* pCook = new Cook(id++, TYPE_VIP, sv, Break_Order, bv, false);
		CookV.enqueue(pCook);
	}
	for (g; g > 0; g--) {
		sg = rand() % (SG_max - SG_min + 1) + SG_min;
		bg = rand() % (BG_max - BG_min + 1) + BG_min;
		Cook* pCook = new Cook(id++, TYPE_VGAN, sg, Break_Order, bg, false);
		CookG.enqueue(pCook);
	}

}

void Restaurant::Add_Normal_Orders(Order* pOrder)
{
	Orders_N.InsertEnd(pOrder, pOrder->GetID());
}

void Restaurant::Add_VIP_Orders(Order* pOrder)
{
	int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
	Orders_V.enqueue(pOrder, priority);
}

void Restaurant::Add_Veg_Orders(Order* pOrder)
{
	Orders_G.enqueue(pOrder);
}

void Restaurant::Delete_Order(int ID)
{
	Orders_N.Delete(ID);
}

void Restaurant::Promote_Order(int ID, int arrival_time, double extra_money)
{
	Order* pOrder = Orders_N.GetFromID(ID);
	if (pOrder != NULL) {
		int money = pOrder->getMoney() + extra_money;
		int priority = -(money / pOrder->getSize()) - arrival_time;
		pOrder->setMoney(money);
		pOrder->SetType(TYPE_VIP);
		pOrder->setArrival(arrival_time);//not sure which arrival to use
		Orders_V.enqueue(pOrder, priority);
	}
	Delete_Order(ID);
}

bool Restaurant::ServeVIPOrder(Order*& pOrder, const int& t)
{
	Cook* temp;
	
		for (int i = 0; i < CookV.getCount(); i++) {
			CookV.dequeue(temp);
			if (!temp->getInjured() && !temp->getBreak() && !temp->getBusy() && pOrder->getStatus() == WAIT) {		//not in break and not busy

				temp->serveNewOrder(pOrder, t);
				Assign(temp, pOrder, Num);
				CookV.enqueue(temp);
				Num++;//increasing the number to get in the next case in the next time if there is more than one order in that TS
				return true;
			}
			else CookV.enqueue(temp);
		}
		return false;
}


bool Restaurant::ServeVeganOrder(Order* pOrder, const int& t)
{

	Cook* temp;
	
		for (int i = 0; i < CookG.getCount(); i++) {
			CookG.dequeue(temp);
			if (!temp->getInjured() && !temp->getBreak() && !temp->getBusy() && pOrder->getStatus() == WAIT) {//not in break and not busy

				temp->serveNewOrder(pOrder, t);
				Assign(temp, pOrder, Num);
				CookG.enqueue(temp);
				Num++;//increasing the number to get in the next case in the next time if there is more than one order in that TS
				return true;
			}
			else CookG.enqueue(temp);
		}
		return false;
}


bool Restaurant::ServeNormalOrder(Order* pOrder, const int& t)
{
	Cook* temp;
	
		for (int i = 0; i < CookN.getCount(); i++) {
			CookN.dequeue(temp);
			if (!temp->getInjured() && !temp->getBreak() && !temp->getBusy() && pOrder->getStatus() == WAIT) {	//not in break and not busy.

				temp->serveNewOrder(pOrder, t);
				Assign(temp, pOrder, Num);
				CookN.enqueue(temp);
				Num++;//increasing the number to get in the next case in the next time if there is more than one order in that TS
				return true;
			}

			else CookN.enqueue(temp);
		}
		return false;
}

bool Restaurant::ChooseCook(Order* pOrder, const int& t)
{
	if (pOrder->getStatus() == DONE) return false;
	if (t < pOrder->getArrival()) return false;
	switch (pOrder->GetType()) {
	case TYPE_VIP:
		if (!ServeVIPOrder(pOrder, t))
			if (!ServeNormalOrder(pOrder, t))
				if (!ServeVeganOrder(pOrder, t)) return false;
		break;
	case TYPE_VGAN:
		if (!ServeVeganOrder(pOrder, t)) return false;
		break;
	case TYPE_NRM:
		if (!ServeNormalOrder(pOrder, t))
			if (!ServeVIPOrder(pOrder, t)) return false;
		break;
	default:
		break;
	}
	return true;
}

bool Restaurant::EventsOrdersFound()
{
	if (!EventsQueue.isEmpty() || !InServiceOrders.IsEmpty() || !Orders_G.isEmpty() || !Orders_N.IsEmpty() || !Orders_V.isEmpty() || !UrgentOrders.isEmpty()) {
		return true;
	}
	return false;
}

void Restaurant::CheckOrder(int t)
{
	Order* pOrder;

	for (int i = 0; i < Orders_V.getCount(); i++) {
		Orders_V.dequeue(pOrder);
		ChooseCook(pOrder, t);//checking if there is an unbusy cook to serve the order
		int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
		Orders_V.enqueue(pOrder, priority);
	}
	for (int i = 0; i < Orders_G.getCount(); i++) {
		Orders_G.dequeue(pOrder);
		ChooseCook(pOrder, t);//checking if there is an unbusy cook to serve the order
		Orders_G.enqueue(pOrder);
	}
	for (int i = 0; i < Orders_N.getCount(); i++) {
		Orders_N.peekHead(pOrder);
		ChooseCook(pOrder, t);//checking if there is an unbusy cook to serve the order
		Orders_N.InsertEnd(pOrder, pOrder->GetID());
	}
	//Serving_Transfer();
}

void Restaurant::Serving_Transfer()
{
	//checking the orders in service to transfer it from waiting list to serve list
	Order* pOrder;
	int nV = Orders_V.getCount();
	for (int i = 0; i < nV; i++) {
		Orders_V.dequeue(pOrder);
		if (pOrder->getStatus() == SRV) {
			InServiceOrders.InsertEnd(pOrder, pOrder->GetID());//if it is in serve i transfer it to the serve list
		}
		else {
			int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
			Orders_V.enqueue(pOrder, priority);//if not in serve i add it again to the waiting list
		}
	}
	int nG = Orders_G.getCount();
	for (int i = 0; i < nG; i++) {
		Orders_G.dequeue(pOrder);
		if (pOrder->getStatus() == SRV) {
			InServiceOrders.InsertEnd(pOrder, pOrder->GetID());//if it is in serve i transfer it to the serve list

		}
		else {
			Orders_G.enqueue(pOrder);//if not in serve i add it again to the waiting list
		}
	}
	int nN = Orders_N.getCount();
	for (int i = 0; i < nN; i++) {
		Orders_N.peekHead(pOrder);
		if (pOrder->getStatus() == SRV) {
			InServiceOrders.InsertEnd(pOrder, pOrder->GetID());//if it is in serve i transfer it to the serve list
		}
		else {
			Orders_N.InsertEnd(pOrder, pOrder->GetID());//if not in serve i add it again to the waiting list
		}
	}
	int nU = UrgentOrders.getCount();
	for (int i = 0; i < nU; i++) {
		UrgentOrders.dequeue(pOrder);
		if (pOrder->getStatus() == SRV) {
			InServiceOrders.InsertEnd(pOrder, pOrder->GetID());//if it is in serve i transfer it to the serve list
		}
		else {
			int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
			UrgentOrders.enqueue(pOrder, priority);//if not in serve i add it again to the waiting list
		}
	}

}

void Restaurant::Finished_Transfer()
{
	Order* pOrder;
	int num = InServiceOrders.getCount();
	for (int i = 0; i < num; i++) {//looping in the orders in service if any has finished
		InServiceOrders.peekHead(pOrder);
		if (pOrder->getStatus() == DONE) {
			FinishedOrders.enqueue(pOrder);//adding the finished order in the finished list
		}
		else {
			InServiceOrders.InsertEnd(pOrder, pOrder->GetID());//if it isn't finished i will add it again in the serving list
		}
	}
}

void Restaurant::Cook_Dute()
{
	Cook* pCook;
	for (int i = 0; i < CookV.getCount(); i++) {
		CookV.dequeue(pCook);

		if (pCook->getBusy()) {  //if the cook is working on an order 
			pCook->serveCurenntOrder();
		}
		CookV.enqueue(pCook);
	}
	for (int i = 0; i < CookG.getCount(); i++) {
		CookG.dequeue(pCook);
		if (pCook->getBusy()) {  //if the cook is working on an order 
			pCook->serveCurenntOrder();
		}


		CookG.enqueue(pCook);
	}
	for (int i = 0; i < CookN.getCount(); i++) {
		CookN.dequeue(pCook);
		if (pCook->getBusy()) {  //if the cook is working on an order 
			pCook->serveCurenntOrder();
		}


		CookN.enqueue(pCook);
	}
}

void Restaurant::CooksInBreak()
{
	Cook* pCook;
	for (int i = 0; i < CookV.getCount(); i++) {
		CookV.dequeue(pCook);
		if (pCook->getBreak() || pCook->getInjured()) {	//if the cook in break i increment the break_period by 1
			pCook->TakeBreak();
		}
		CookV.enqueue(pCook);
	}
	for (int i = 0; i < CookN.getCount(); i++) {
		CookN.dequeue(pCook);
		if (pCook->getBreak() || pCook->getInjured()) {	//if the cook in break i increment the break_period by 1
			pCook->TakeBreak();
		}
		CookN.enqueue(pCook);
	}
	for (int i = 0; i < CookG.getCount(); i++) {
		CookG.dequeue(pCook);
		if (pCook->getBreak() || pCook->getInjured()) {	//if the cook in break i increment the break_period by 1
			pCook->TakeBreak();
		}
		CookG.enqueue(pCook);
	}
}

void Restaurant::AutoP_Check(int t)
{
	Order* pOrder;
	int count = Orders_N.getCount();
	for (int i = 0; i < count; i++) {
		bool promote = false;
		Orders_N.peekHead(pOrder);
		if (pOrder->getWT() > AutoP) {
			promote = true;
		}
		Orders_N.InsertEnd(pOrder, pOrder->GetID());
		if (promote) {
			Promote_Order(pOrder->GetID(), t, 0);
			Auto_p++;
		}
	}
}

void Restaurant::Increase_WT()
{
	Order* pOrder;
	for (int i = 0; i < Orders_V.getCount(); i++) {
		Orders_V.dequeue(pOrder);
		pOrder->setWT(pOrder->getWT() + 1);
		int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
		Orders_V.enqueue(pOrder, priority);
	}
	for (int i = 0; i < Orders_G.getCount(); i++) {
		Orders_G.dequeue(pOrder);
		pOrder->setWT(pOrder->getWT() + 1);
		Orders_G.enqueue(pOrder);
	}
	for (int i = 0; i < Orders_N.getCount(); i++) {
		Orders_N.peekHead(pOrder);
		pOrder->setWT(pOrder->getWT() + 1);
		Orders_N.InsertEnd(pOrder, pOrder->GetID());
	}
	for (int i = 0; i < UrgentOrders.getCount(); i++) {
		UrgentOrders.dequeue(pOrder);
		pOrder->setWT(pOrder->getWT() + 1);
		int priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
		UrgentOrders.enqueue(pOrder, priority);
	}

}

void Restaurant::Output_File(string name)
{
	calcinjuredcooks();
	Order* pOrder;
	ofstream Out;
	int NN, NG, NV, total_orders;
	int total_cooks;
	double AVG_WT, AVG_SERV;
	NN = NG = NV = total_orders = AVG_WT = AVG_SERV = 0;
	Out.open(name + ".txt");
	Out << "FT		" << "ID		" << "AT		" << "WT		" << "ST		" << "\n";
	while (!FinishedOrders.isEmpty()) {
		FinishedOrders.dequeue(pOrder);

		NN += pOrder->GetType() == TYPE_NRM;
		NG += pOrder->GetType() == TYPE_VGAN;
		NV += pOrder->GetType() == TYPE_VIP;

		AVG_WT += pOrder->getWT();
		AVG_SERV += pOrder->getServ();

		Out << pOrder->getFinish() << "		" << pOrder->GetID() << "		" << pOrder->getArrival() << "		" << pOrder->getWT() << "		" << pOrder->getServ() << "\n";
	}
	total_orders += NN + NG + NV;
	AVG_WT /= total_orders;
	AVG_SERV /= total_orders;
	total_cooks = CookN.getCount() + CookG.getCount() + CookV.getCount();
	Out << endl << endl;
	Out << "Orders: " << total_orders << "	[Norm: " << NN << ", Veg: " << NG << ", VIP: " << NV - urgentnum << "]" << endl;
	Out << "cooks: " << total_cooks << "	[Norm: " << CookN.getCount() << ", Veg: " << CookG.getCount() << ", VIP: " << CookV.getCount() << ", Injured: " << injurednum << "]" << endl;
	Out << "Avg Wait: " << AVG_WT << ", Avg Serv: " << AVG_SERV << endl;
	Out << "Urgent Orders: " << urgentnum << " Auto_Promoted: " << ((float)Auto_p/ (float)Normal_Orders)*100 <<"%"<< endl;
	Out.close();
}

void Restaurant::Num_WT_Orders()
{
	string num = "Waiting Orders:     VIP = " + to_string(Orders_V.getCount()) + "     Normal = " + to_string(Orders_N.getCount()) + "     Vegan = " + to_string(Orders_G.getCount()) + "     Urgent = " + to_string(UrgentOrders.getCount());
	pGUI->PrintMessage(num, 2, 0);
}

void Restaurant::Num_Cooks_Able()
{
	int NN = 0, NV = 0, NG = 0;
	Cook** Arr_CookG;
	int Cook_NumG = CookG.getCount();
	Arr_CookG = CookG.toArray();

	Cook** Arr_CookN;
	int Cook_NumN = CookN.getCount();
	Arr_CookN = CookN.toArray();

	Cook** Arr_CookV;
	int Cook_NumV = CookV.getCount();
	Arr_CookV = CookV.toArray();

	Cook* pC;

	for (int i = 0; i < Cook_NumN; i++) {
		pC = Arr_CookN[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {
			NN++;
		}
	}
	for (int i = 0; i < Cook_NumG; i++) {
		pC = Arr_CookG[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {
			NG++;
		}
	}
	for (int i = 0; i < Cook_NumV; i++) {
		pC = Arr_CookV[i];
		if (!(pC->getBusy()) && !(pC->getBreak())) {
			NV++;
		}
	}
	string num = "Available Cooks:   VIP = " + to_string(NV) + "     Normal = " + to_string(NN) + "     Vegan = " + to_string(NG);
	pGUI->PrintMessage(num, 3, 0);

}

void Restaurant::Assign(Cook* pC, Order* pO, int n)
{
	string a;
	switch (pC->GetType()) {
	case TYPE_NRM:
		switch (pO->GetType()) {
		case TYPE_NRM:
			a = "Normal cook# " + to_string(pC->GetID()) + " is assigned to prepare Normal order# " + to_string(pO->GetID());
			break;
		case TYPE_VGAN:
			a = "Normal cook# " + to_string(pC->GetID()) + " is assigned to prepare Vegan order# " + to_string(pO->GetID());
			break;
		case TYPE_VIP:
			a = "Normal cook# " + to_string(pC->GetID()) + " is assigned to prepare VIP order# " + to_string(pO->GetID());
			break;
		}
		break;
	case TYPE_VIP:
		switch (pO->GetType()) {
		case TYPE_NRM:
			a = "VIP cook# " + to_string(pC->GetID()) + " is assigned to prepare Normal order# " + to_string(pO->GetID());
			break;
		case TYPE_VGAN:
			a = "VIP cook# " + to_string(pC->GetID()) + " is assigned to prepare Vegan order# " + to_string(pO->GetID());
			break;
		case TYPE_VIP:
			a = "VIP cook# " + to_string(pC->GetID()) + " is assigned to prepare VIP order# " + to_string(pO->GetID());
			break;
		}
		break;
	case TYPE_VGAN:
		switch (pO->GetType()) {
		case TYPE_NRM:
			a = "Vegan cook# " + to_string(pC->GetID()) + " is assigned to prepare Normal order# " + to_string(pO->GetID());
			break;
		case TYPE_VGAN:
			a = "Vegan cook# " + to_string(pC->GetID()) + " is assigned to prepare Vegan order# " + to_string(pO->GetID());
			break;
		case TYPE_VIP:
			a = "Vegan cook# " + to_string(pC->GetID()) + " is assigned to prepare VIP order# " + to_string(pO->GetID());
			break;
		}
		break;
	}
	pGUI->PrintMessage(a, 5, n);
}

void Restaurant::Served_num()
{
	Order** pO;
	int NN = 0, NV = 0, NG = 0;
	int FinishCount = FinishedOrders.getCount();
	pO = FinishedOrders.toArray();
	for (int i = 0; i < FinishCount; i++) {
		switch (pO[i]->GetType()) {
		case TYPE_NRM:
			NN++;
			break;
		case TYPE_VIP:
			NV++;
			break;
		case TYPE_VGAN:
			NG++;
			break;
		}
	}
	string finished_orders = "Served Orders:     VIP = " + to_string(NV) + "     Normal = " + to_string(NN) + "     Vegan = " + to_string(NG);
	pGUI->PrintMessage(finished_orders, 4, 0);
}

void Restaurant::checkHealth() {
	float x = (rand() % 100) / 100.0;
	if (x <= injuryProp) {
		Cook* pCook;
		bool found = false;
		for (int i = 0; i < CookV.getCount(); i++) {
			CookV.dequeue(pCook);
			if (pCook->getBusy())
			{
				pCook->setinjuredbefore();
				pCook->setInjured(true);
				pCook->setRestTime(restTime);
				found = true;
				CookV.enqueue(pCook);
				break;
			}
			CookV.enqueue(pCook);
		}
		if (!found)
			for (int i = 0; i < CookN.getCount(); i++) {
				CookN.dequeue(pCook);
				if (pCook->getBusy())
				{
					pCook->setinjuredbefore();
					pCook->setInjured(true);
					pCook->setRestTime(restTime);
					found = true;
					CookN.enqueue(pCook);
					break;
				}
				CookN.enqueue(pCook);
			}
		if (!found)
			for (int i = 0; i < CookG.getCount(); i++) {
				CookG.dequeue(pCook);
				if (pCook->getBusy())
				{
					pCook->setinjuredbefore();
					pCook->setInjured(true);
					pCook->setRestTime(restTime);
					CookG.enqueue(pCook);
					break;
				}
				CookG.enqueue(pCook);
			}
	}
}

void Restaurant::CheckUrgentOrders(int t)
{
	Order* pOrder;
	bool found = false;
	int priority;
	for (int i = 0; i < Orders_V.getCount(); i++) {
		Orders_V.dequeue(pOrder);
		priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
		bool stat = t - pOrder->getArrival() >= VIP_WT;
		if (stat)
		{
			found = true;
			UrgentOrders.enqueue(pOrder, priority);
			urgentnum++;
		}
		else
		{
			Orders_V.enqueue(pOrder, priority);
		}
	}
	if (found || !UrgentOrders.isEmpty())
	{
		bool able_to_serve;
		for (int i = 0; i < UrgentOrders.getCount(); i++) {
			UrgentOrders.dequeue(pOrder);
			able_to_serve = ChooseCook(pOrder, t);
			if (!able_to_serve)
			{
				bool stat = cutbreaks();
				if (stat)
				{
					ChooseCook(pOrder, t);
				}
			}
			priority = -(pOrder->getMoney() / pOrder->getSize()) - pOrder->getArrival();
			UrgentOrders.enqueue(pOrder, priority);
		}


	}
}

bool Restaurant::cutbreaks()
{
	Cook* pCook;
	bool found = false;
	for (int i = 0; i < CookV.getCount(); i++) {
		CookV.dequeue(pCook);

		if (pCook->getBreak()) {
			pCook->cutbreak();
			found = true;
			CookV.enqueue(pCook);
			break;
		}
		CookV.enqueue(pCook);
	}
	if (!found)
	{
		for (int i = 0; i < CookN.getCount(); i++) {
			CookN.dequeue(pCook);
			if (pCook->getBreak()) {
				pCook->cutbreak();
				found = true;
				CookN.enqueue(pCook);
				break;
			}
			CookN.enqueue(pCook);
		}
	}

	if (!found)
	{
		for (int i = 0; i < CookG.getCount(); i++) {
			CookG.dequeue(pCook);
			if (pCook->getBreak()) {
				pCook->cutbreak();
				found = true;
				CookG.enqueue(pCook);
				break;
			}
			CookG.enqueue(pCook);
		}
	}
	if (!found)
	{
		for (int i = 0; i < CookV.getCount(); i++) {
			CookV.dequeue(pCook);
			if (pCook->getInjured()&&!pCook->getBusy()) {
				pCook->cutbreak();
				found = true;
				pCook->set_inj_servUrge();
				CookV.enqueue(pCook);
				break;
			}
			CookV.enqueue(pCook);
		}
	}
	if (!found)
	{
		for (int i = 0; i < CookN.getCount(); i++) {
			CookN.dequeue(pCook);
			if (pCook->getInjured() && !pCook->getBusy()) {
				pCook->cutbreak();
				found = true;
				pCook->set_inj_servUrge();
				CookN.enqueue(pCook);
				break;
			}
			CookN.enqueue(pCook);
		}
	}
	if (!found)
	{
		for (int i = 0; i < CookG.getCount(); i++) {
			CookG.dequeue(pCook);
			if (pCook->getInjured() && !pCook->getBusy()) {
				pCook->cutbreak();
				found = true;
				pCook->set_inj_servUrge();
				CookG.enqueue(pCook);
				break;
			}
			CookG.enqueue(pCook);
		}
	}

	return found;
}

void Restaurant::calcinjuredcooks()
{
	Cook* pCook;
	for (int i = 0; i < CookV.getCount(); i++) {
		CookV.dequeue(pCook);

		if (pCook->gotinjuredbefore())
		{
			injurednum++;
		}
		CookV.enqueue(pCook);
	}
	for (int i = 0; i < CookN.getCount(); i++) {
		CookN.dequeue(pCook);
		if (pCook->gotinjuredbefore())
		{
			injurednum++;
		}
		CookN.enqueue(pCook);
	}

	for (int i = 0; i < CookG.getCount(); i++) {
		CookG.dequeue(pCook);
		if (pCook->gotinjuredbefore())
		{
			injurednum++;
		}
		CookG.enqueue(pCook);
	}

}
