#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include "Order.h"


struct BuyOrderComparator{
	bool operator()(const Order& a, const Order& b) const{
		// If same price order, priority will be given to the older one
		if(a.price == b.price) {
			return a.timestamp > b.timestamp;
		}
		// Otherwise higher price gets priority
		return a.price < b.price;
	}
};

struct SellOrderComparator{
	bool operator()(const Order& a, const Order& b) const{
		// If same price order, priority will be given to the older one
		if(a.price == b.price) {
			return a.timestamp > b.timestamp;
		}
		// Otherwise higher price gets priority
		return a.price > b.price;
	}
};

class OrderBook {
private:
	
	//Bids
	std::priority_queue<Order, std::vector<Order>, BuyOrderComparator> buyOrders;
	
	//Asks
	std::priority_queue<Order, std::vector<Order>, SellOrderComparator> sellOrders;
	
	//Map to track orders
	std::unordered_map<int, Order> allOrders;
	
	//Private helper function containing matching logic
	void matchOrders();
	
public:
	OrderBook() {
		std::cout<<"\nOrderBook has been created."<<std::endl;
	}
	
	// Function to add Orders
	void addOrder(const Order& order);
	
	// Function to remove Orders
	void removeOrder(int orderId);
	
	// Function to display current state of order book
	void displayBook();
};

#endif
