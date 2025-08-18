#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include "Order.h"

class OrderBook
{
public:
	OrderBook() {
		std::cout<<"\nOrderBook has been created."<<std::endl;
	}
	void addOrder(const Order& order);
	
	void removeOrder(int orderId);
	
	void displayBook();
};

#endif
