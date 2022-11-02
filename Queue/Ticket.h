/*
 * Ticket.h
 *
 *  Created on: 31 Oct 2022
 *      Author: shaun
 */

#ifndef TICKET_H_
#define TICKET_H_

#include <iostream>
#include <ctime>
using namespace std;
class Ticket{
private:
	string TransID, TicketID, Source, Desti, CusID, CusName, CusIC, TransDT;
	double TicAmount;
	string DepartT;
public:
	Ticket() = default;
	Ticket(string TrID, string TiID, string source, string dest, double amount, string dT){
		this->TransID=TrID;
		this->TicketID=TiID;
		this->Source=source;
		this->Desti=dest;
		this->TicAmount=amount;
		this->CusID="Test1";
		this->CusName="Test2";
		this->CusIC="Test3";
		time_t now=time(0);
		char* dtnow = ctime(&now);
		this->TransDT= dtnow;
		this->DepartT=dT;
	}
	string getTrID(){
		return this->TransID;
	}
	string getTkID(){
		return this->TicketID;
	}
	string getSource(){
		return this->Source;
	}
	string getDest(){
		return this->Desti;
	}
	double getAmount(){
		return this->TicAmount;
	}
	string getTransDT(){
		return this->TransDT;
	}
	string getDepartT(){
		return this->DepartT;
	}
	string getCusID(){
		return this->CusID;
	}
	string getCusName(){
		return this->CusName;
	}
	string getCusIC(){
		return this ->CusIC;
	}
	void setSource(string source){
		this->Source=source;
	}
	void setDest(string dest){
		this->Desti=dest;
	}
	void setTAmount(double amount){
		this->TicAmount=amount;
	}
	void setDepartT(time_t dT){
		this->DepartT=dT;
	}
	void setCusInfo(string id, string name, string ic){
		this->CusIC=ic;
		this->CusID=id;
		this->CusName=name;
	}
	void showTicketDetails(){
		cout<<"Transaction ID: "<<this->TransID<<endl<<"Ticket ID: "<<this->TicketID<<endl;
		cout<<"Source Station: "<<this->Source<<endl<<"Destination Station: "<<this->Desti<<endl;
		cout<<"Ticket Amount: "<<"RM"<<this->TicAmount<<endl;
		cout<<"Transaction Date & Time: " <<this->TransDT;
		cout<<"Departure Time: "<<DepartT<<endl;
	}
	void showAll(){
		showTicketDetails();
		cout<<"Customer ID: "<<this->CusID<<endl<<"Customer Name: "<<this->CusName<<endl;
		cout<<"Customer IC/Passport Details: "<<this->CusIC<<endl;
	}
};



#endif /* TICKET_H_ */
