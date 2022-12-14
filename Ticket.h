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
	string TransID, TicketID, Source, Desti, CusName, CusIC, TransDT, DepartT;
	double TicAmount;
	int CusID;
public:
	Ticket() = default;

	Ticket(string TrID, string TiID, string source, string dest, double amount, int cid, string cname, string cic, string tdt,string dT){
		this->TransID=TrID;
		this->TicketID=TiID;
		this->Source=source;
		this->Desti=dest;
		this->TicAmount=amount;
		this->CusID=cid;
		this->CusName=cname;
		this->CusIC=cic;
		this->TransDT= tdt;
		this->DepartT=dT;
	}
	Ticket(string TrID, string TiID, string source, string dest, double amount, string dT){
		this->TransID=TrID;
		this->TicketID=TiID;
		this->Source=source;
		this->Desti=dest;
		this->TicAmount=amount;
		this->CusID=0;
		this->CusName="";
		this->CusIC="";
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
	int getCusID(){
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
	void setDepartT(string dT){
		this->DepartT=dT;
	}
	void setCusInfo(int id, string name, string ic){
		this->CusIC=ic;
		this->CusID=id;
		this->CusName=name;
	}
	void showTicketDetails(){
		cout<<"Transaction ID: "<<this->TransID<<endl<<"Ticket ID: "<<this->TicketID<<endl;
		cout<<"Source Station: "<<formatInfoTabsForTable(this->Source)<<endl<<"Destination Station: "<<formatInfoTabsForTable(this->Desti)<<endl;
		cout<<"Ticket Amount: "<<"RM"<<this->TicAmount<<endl;
		cout<<"Transaction Date & Time: " <<this->TransDT;
		cout<<"Departure Time: "<<DepartT<<endl;
	}
	void showAll(){
		showTicketDetails();
		cout<<"Customer ID: "<<this->CusID<<endl<<"Customer Name: "<<this->CusName<<endl;
		cout<<"Customer IC/Passport Details: "<<this->CusIC<<endl;
	}
	string formatInfoTabsForTable(string info) {
		if (info.length() < 8) {
			return info + "\t\t";
		}
		else {
			return info + "\t";
		}
	};
};



#endif /* TICKET_H_ */
