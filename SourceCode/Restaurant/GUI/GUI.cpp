#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	DrawingItemsCount = 0;
	pWind = new window(WindWidth+15,WindHeight,0,0); 
	pWind->ChangeTitle("The Restautant");


	//Set color for each order type
	DrawingColors[TYPE_NRM] =  BLACK;	//normal-order color
	DrawingColors[TYPE_VGAN] = WHITE;		//vegan-order color
	DrawingColors[TYPE_VIP] = 	YELLOW;		//VIP-order color					

	ClearStatusBar();
	ClearDrawingArea(); 
	DrawRestArea();  
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label = "";
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		PrintMessage("", 0,0);
		PrintMessage(Label,1,0);
	}
	return Label;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,int num,int N) const	//Prints a message on status bar
{
	//ClearStatusBar();	//First clear the status bar
	//i used switch cases here to be able to choose the number of line i want to print my message in
	pWind->SetPen(DARKRED);//Microsoft Himalaya       Bahnschrift Light Condensed    Calibri      Times New Roman
	pWind->SetFont(18, BOLD, BY_NAME, "Times New Roman");
	switch (num) {
	case 0:
		ClearStatusBar();
		break;
	case 1:
		pWind->SetPen(BLACK);
		pWind->DrawString(10, WindHeight - (int)(140), msg);
		break;
	case 2:
		pWind->SetPen(BLACK);
		pWind->DrawString(10, WindHeight - (int)(120), msg);
		break;
	case 3:
		pWind->SetPen(BLACK);
		pWind->DrawString(10, WindHeight - (int)(100), msg);
		break;
	case 4:
		pWind->SetPen(BLACK);
		pWind->DrawString(10, WindHeight - (int)(80), msg);
		break;
	case 5:
		pWind->SetPen(DARKRED);
		switch (N) {
		case 0:
			pWind->DrawString(10, WindHeight - (int)(60), msg);
			break;
		case 1:
			pWind->DrawString(10, WindHeight - (int)(40), msg);
			break;
		case 2:
			pWind->DrawString(410, WindHeight - (int)(140), msg);
			break;
		case 3:
			pWind->DrawString(410, WindHeight - (int)(120), msg);
			break;
		case 4:
			pWind->DrawString(410, WindHeight - (int)(100), msg);
			break;
		case 5:
			pWind->DrawString(410, WindHeight - (int)(80), msg);
			break;
		case 6:
			pWind->DrawString(410, WindHeight - (int)(60), msg);
			break;
		case 7:
			pWind->DrawString(410, WindHeight - (int)(40), msg);
			break;
		case 8:
			pWind->DrawString(810, WindHeight - (int)(140), msg);
			break;
		case 9:
			pWind->DrawString(810, WindHeight - (int)(120), msg);
			break;
		case 10:
			pWind->DrawString(810, WindHeight - (int)(100), msg);
			break;
		case 11:
			pWind->DrawString(810, WindHeight - (int)(80), msg);
			break;
		case 12:
			pWind->DrawString(810, WindHeight - (int)(60), msg);
			break;
		case 13:
			pWind->DrawString(810, WindHeight - (int)(40), msg);
			break;
		}
		
	}

	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(ANTIQUEWHITE, 3);
	pWind->SetBrush(ANTIQUEWHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(DARKSEAGREEN, 3);
	pWind->SetBrush(DARKSEAGREEN);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the brown square of the Rest
	pWind->SetPen(BLACK);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(RestStartX, RestStartY, RestEndX, RestEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);//the horizontal line
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);//the vertical line.

	// 3- Drawing the 2 white crossed lines (inside the Rest)
	pWind->SetPen(DARKSEAGREEN);
	pWind->DrawLine(WindWidth/2, YHalfDrawingArea - RestWidth/2, WindWidth/2, YHalfDrawingArea + RestWidth/2);//the vertical line
	pWind->DrawLine(WindWidth/2 - RestWidth/2, YHalfDrawingArea, WindWidth/2 + RestWidth/2, YHalfDrawingArea);//the horizontal line

	// 4- Drawing the 4 white squares inside the Rest (one for each region) ???!!!
	/*pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(RestStartX , RestStartY , RestStartX + 2*L/2, RestStartY + 2*L/2);
	pWind->DrawRectangle(RestStartX + L/3, RestEndY - L/3, RestStartX + 2*L/3, RestEndY - 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestStartY + L/3, RestEndX - L/3, RestStartY + 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestEndY - L/3, RestEndX - L/3, RestEndY - 2*L/3);*/

	// 5- Writing regions labels
	pWind->SetPen(DARKSEAGREEN);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->DrawString(RestStartX + (int)(0.1*L), RestStartY + 5*L/12, "WAIT");

	pWind->DrawString(WindWidth/2 + (int)(0.1*L), RestStartY + 5*L/12, "COOK");

	pWind->DrawString(WindWidth/2 + (int)(0.1*L), YHalfDrawingArea + 5*L/12, "SRVG"); 

	pWind->DrawString(RestStartX + (int)(0.1*L), YHalfDrawingArea + 5*L/12, "DONE");

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the passed item in its region
//region count in the numbers of items drawn so far in that item's region
void GUI::DrawSingleItem(const DrawingItem* pDitem, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionOrderCount) 
		return; //no more items can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if(RegionCount>=MaxHorizOrders )	//max no. of orders to draw in one line
	{
		DrawDistance = (RegionCount-1)%MaxHorizOrders + 1;
		YPos = (RegionCount-1) / MaxHorizOrders + 1; 
	}

	GUI_REGION Region = pDitem->region;

	int x, y, refX, refY;
	//First calculate x,y position of the order on the output screen
	//It depends on the region and the order distance
	switch (Region)
	{
	case ORD_REG:
		refX = (WindWidth/2 - RestWidth/2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case COOK_REG:
		refX = (WindWidth/2 + RestWidth/2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case SRV_REG:
		refX = (WindWidth/2 + RestWidth/2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	case DONE_REG:
		refX = (WindWidth/2 - RestWidth/2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the item
	pWind->SetPen(pDitem->clr);
	pWind->SetFont(20,BOLD, MODERN);
	pWind->DrawInteger(x,y,pDitem->ID);
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw all items in DrawingList and ensure there is no overflow in the drawing*/
void GUI::DrawAllItems() 
{

	//Prepare counter for each region
	int RegionsCounts[REG_CNT]={0};	//initlaize all counters to zero

	DrawingItem* pDitem;
	for(int i=0; i<DrawingItemsCount; i++)
	{
		pDitem = DrawingList[i];
		RegionsCounts[pDitem->region]++;
		DrawSingleItem(DrawingList[i],RegionsCounts[pDitem->region]);

	}

}

void GUI::UpdateInterface() 
{
	ClearDrawingArea();
	DrawRestArea();
	DrawAllItems();
}

/*
	AddOrderForDrawing: Adds a new item related to the passed Order to the drawing list
*/
void GUI::AddToDrawingList(Order* pOrd)
{
	
	DrawingItem *pDitem=new DrawingItem;
	pDitem->ID = pOrd->GetID();
	pDitem->clr = DrawingColors[pOrd->GetType()];
	ORD_STATUS order_status = pOrd->getStatus();
	GUI_REGION reg;

	switch (order_status)
	{
	case WAIT:
		reg = ORD_REG;	//region of waiting orders
		break;
	case SRV:
		reg = SRV_REG;	//region of waiting orders
		break;
	case DONE:
		reg = DONE_REG;	//region of waiting orders
		break;
	}

	pDitem->region =reg;
	
	DrawingList[DrawingItemsCount++]=pDitem;

}

void GUI::AddToDrawingList(Cook* pC)
{
	
	DrawingItem *pDitem=new DrawingItem;
	pDitem->ID = pC->GetID();
	pDitem->clr = DrawingColors[pC->GetType()];
	pDitem->region = COOK_REG;
	
	DrawingList[DrawingItemsCount++]=pDitem;

}

/*void GUI::AddToDrawingList(Event* pE)
{
	DrawingItem* pDitem = new DrawingItem;
	pDitem->ID = pE->getOrderID();
	pDitem->clr = DrawingColors[TYPE_VIP];
	pDitem->region = ORD_REG;

	DrawingList[DrawingItemsCount++] = pDitem;
}*/

void GUI::ResetDrawingList()
{
	for(int i=0; i<DrawingItemsCount; i++)
		delete DrawingList[i];

	DrawingItemsCount = 0;
}

 


PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("", 0,0);
		PrintMessage("Please select GUI mode: (1)Interactive, (2)StepByStep, (3)Silent ",1,0);
		string S = GetString();
		Mode = (PROG_MODE) (atoi(S.c_str())-1);
	}
	while(Mode< 0 || Mode >= MODE_CNT);
	
	return Mode;
	
	return MODE_INTR;
}
