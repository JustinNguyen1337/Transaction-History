#ifndef _HISTORY_TRANSACTION_HPP_
#define _HISTORY_TRANSACTION_HPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project3.hpp"
#include "History.hpp"
#include "Transaction.hpp"



////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//

Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date, unsigned int month_date,  unsigned year_date,  bool buy_sell_trans,  unsigned int number_shares, double trans_amount ){
	//initializes values for transaction class
	symbol = ticker_symbol;
	day = day_date;
	month = month_date;
	year = year_date;
	buy_sell_trans == true ? trans_type = "Buy" : trans_type = "Sell";
	shares = number_shares;
	amount = trans_amount;
	trans_id = assigned_trans_id;
	assigned_trans_id++;
	acb = 0.0;
	acb_per_share = 0.0;
	share_balance = 0;
	cgl = 0.0;
	p_next = nullptr;
}




// Destructor
// TASK
//

Transaction::~Transaction(){

}



// TASK
// Overloaded < operator.
//

bool Transaction::operator < ( Transaction const &other ){
	//compares the years, months, and days, and returns true if the date is less than the second date
	if (this->year == other.year) {
		if (this->month == other.month){
			if (this->day < other.day){
				return true;
			} else {
				return false;
			}
		} else if (this->month < other.month){
			return true;
		} else {
			return false;
		}
	} else if (this->year < other.year) {
		return true;
	} else {
		return false;
	}


}


// GIVEN
// Member functions to get values. 
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values. 
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " " 
    << std::setw(4) << get_symbol() << " " 
    << std::setw(4) << get_day() << " "  
    << std::setw(4) << get_month() << " " 
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) { 
    std::cout << "  Buy  "; 
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " " 
    << std::setw(10) << get_amount() << " " 
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl() 
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK
//

History::History(){
	//initalizes p_head as nullptr
	p_head = nullptr;
}


// Destructor
// TASK
//
History::~History(){
	//loops through the linked list and deletes the linked list starting from the end of the list
	Transaction *douglas = p_head;
	unsigned int count = 0;
	while (douglas != nullptr){
		douglas = douglas ->get_next();
		count += 1;
	}
	for (unsigned int x = count; x >0; --x) {
		douglas = p_head;
		for (unsigned int k = 0; k < x; k++){
			douglas = douglas->get_next();
		}
		delete douglas;
		douglas = nullptr;
	}
	//deletes p_head
	delete p_head;
	p_head = nullptr;
}

// TASK
// read_transaction(...): Read the transaction history from file. <3
//
void History::read_history(){
	//opens the file for reading
	ece150::open_file();
	//loops through each transaction
	while (ece150::next_trans_entry()){
		//creates a new transaction pointer and inserts it into the linked list
		Transaction *trans = new Transaction( ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
		insert(trans);
	}
	//closes the file for reading
	ece150::close_file();
}

// insert(...): Insert transaction into linked list.
//
void History::insert( Transaction *p_new_trans){
	//sets the value for p_head if p_head is nullptr
	if (p_head == nullptr){
		p_head = p_new_trans;
		return;
	//loops though the linked list and makes the last value point to the new value
	} else {
		Transaction *pNext = p_head;
		while (pNext->get_next() != nullptr){
			pNext = pNext->get_next();
		}
		pNext->set_next(p_new_trans);
		//delete pNext;
		//pNext = nullptr;
	}


}

// TASK
// sort_by_date(): Sort the linked list by trade date.
//
void History::sort_by_date(){
	//returns if there is no value in p_head
	if (p_head == nullptr) {
		return;
	}
	//head pointer for second linked list
	Transaction *p_head2 = p_head;
	//loop to count how many values there are in the linked list
	unsigned int count = 1;
	Transaction *pFore = p_head;
	while (pFore != nullptr){
		pFore = pFore->get_next();
		count += 1;
	}

	//creates pointers for the two transactions before the current transaction being compared
	Transaction *pBefore = p_head;
	Transaction *beBefore = p_head;
	p_head = pBefore->get_next();
	p_head2->set_next(nullptr);
	//loops through each of elements in the original linked list to insert into the new linked list
	for (unsigned int k = 1; k < count-1; ++k){
		pFore = p_head;
		p_head = pFore->get_next();
		pBefore = p_head2;
		//loops through each value of the new linked list to compare
		for (unsigned int x = 0; x < k; x++){
			//takes the first element in the original linked list and compares it to the first in the new and sets it either before or after
			if ((x == 0) && (*pFore < *p_head2)){
				pFore->set_next(p_head2);
				p_head2 = pFore;
				break;
			} else if ((x == 0) && k == 1){
				pFore->set_next(p_head2->get_next());
				p_head2->set_next(pFore);
			//takes the first element in the original linked list and compares it to an element in the new and sets it either before or after
			} else if (*pFore < *pBefore){
				pFore->set_next(pBefore);
				beBefore->set_next(pFore);
				break;
			} else if (x == (k-1)){
				pFore->set_next(pBefore->get_next());
				pBefore->set_next(pFore);
			}
			beBefore = pBefore;
			pBefore = pBefore->get_next();
		}
	}
	p_head = p_head2;
}



// TASK
// sort_by_date(): Sort the linked list by trade date.
//



// TASK
// update_acb_cgl(): Updates the ACB and CGL values. 
//

void History::update_acb_cgl(){
	//returns if p_head is nullptr
	if (p_head == nullptr) {
		return;
	}
	//assigns the values for acb, shares, acb_per_share, cgl, share_balance
	double totalACB = 0;
	int totalShares = 0;
	Transaction *pCurrent = p_head;
	while (pCurrent != nullptr){
		if (pCurrent->get_trans_type()){
			totalACB += pCurrent->get_amount();
			totalShares += pCurrent->get_shares();
			pCurrent->set_acb_per_share(totalACB/totalShares);
		} else {
			totalACB -= totalACB/totalShares*(pCurrent->get_shares());
			totalShares -= pCurrent->get_shares();
			pCurrent->set_acb_per_share(totalACB/totalShares);
			pCurrent->set_cgl(pCurrent->get_amount() - (pCurrent->get_shares() * pCurrent->get_acb_per_share()));
		}
		pCurrent->set_acb(totalACB);
		pCurrent->set_share_balance(totalShares);
		pCurrent = pCurrent->get_next();

	}
}


// TASK
// compute_cgl(): )Compute the ACB, and CGL.
//

double History::compute_cgl(unsigned int year){
	//returns 0.0 if p_head is nullptr
	if (p_head == nullptr) {
		return 0.0;
	}
	Transaction *pNow = p_head;
	double totalCGL = 0.0;
	//loops while the year of the transaction is less than the inputed year and while it is not a nullptr after the current transaction
	while ( pNow != nullptr){
		if (pNow->get_year() > year){
			break;
		}
		if (pNow->get_year() == year) {
			//increases the totalCGL for the year
			totalCGL += pNow->get_cgl();
		}
		pNow = pNow->get_next();
	}

	return totalCGL;
}


// TASK
// print() Print the transaction history.
//
void History::print() {
	if (p_head == nullptr) {
		return;
	}
	//prints the entire linked list using the transaction::print()
	Transaction *pNext = p_head;
	while (pNext != nullptr){
		pNext->print();
		pNext = pNext->get_next();
	}

}


// GIVEN
// get_p_head(): Full access to the linked list.
// 

Transaction *History::get_p_head() { return p_head; }


#endif

