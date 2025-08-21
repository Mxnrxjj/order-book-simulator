#include "OrderBook.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

void OrderBook::addOrder(const Order& newOrder) {
	//Add new order to master list
	allOrders[newOrder.id] = newOrder;
	
	//Place order to correct side
	if(newOrder.type == OrderType::BUY) {
		buyOrders.push(newOrder);
	} else {
		sellOrders.push(newOrder);
	}
	
	std::cout<<"\nOrder "<<newOrder.id<<" accepted.\n";
	
	matchOrders();
}

void OrderBook::matchOrders() {
	
	while( !buyOrders.empty() && !sellOrders.empty() && buyOrders.top().price >= sellOrders.top().price) {
		
		Order topBuyer = buyOrders.top();
		Order topSeller = sellOrders.top();
		
		buyOrders.pop();
		sellOrders.pop();
		
		int tradeQuantity = std::min(topBuyer.quantity, topSeller.quantity);
		
		std::cout << "\n*** TRADE EXECUTED ***\n";
        std::cout << tradeQuantity << " shares traded @ " << topSeller.price << "\n";
        std::cout << "Buyer ID: " << topBuyer.id << ", Seller ID: " << topSeller.id << "\n";
        std::cout << "********************\n";
		
		
		topBuyer.quantity -= tradeQuantity;
		topSeller.quantity -= tradeQuantity;
		
		if(topBuyer.quantity > 0) {
			buyOrders.push(topBuyer);
			allOrders[topBuyer.id] = topBuyer; //Update in master list
		} else {
			//Erase from master list
			allOrders.erase(topBuyer.id);
		}
		if(topSeller.quantity > 0) {
			sellOrders.push(topSeller);
			allOrders[topSeller.id] = topSeller; //Update in master list
		} else {
			//Erase from master list
			allOrders.erase(topSeller.id);
		}
		
	}
	
}

void OrderBook::displayBook() {
	//Copying queues
	auto buyQ = buyOrders;
	auto sellQ = sellOrders;
	
	//Using vector to store and sort
	std::vector<Order> buyList;
	while(!buyQ.empty()) {
		buyList.push_back(buyQ.top());
		buyQ.pop();
	}
	
	std::vector<Order> sellList;
	while(!sellQ.empty()) {
		sellList.push_back(sellQ.top());
		sellQ.pop();
	}
	
	//Sell price lowest to highest
	std::reverse(sellList.begin(), sellList.end());
	
	//Printing
	std::cout << "\n================ ORDER BOOK ================\n";
    std::cout << "ASKS (SELL ORDERS):\n";
    std::cout << "+----------+----------+--------------------+\n";
    std::cout << "|  OrderID | Quantity |              Price |\n";
    std::cout << "+----------+----------+--------------------+\n";
	for (const auto& order : sellList) {
        std::cout << "| " << std::setw(8) << order.id << " | " << std::setw(8) << order.quantity << " | " << std::fixed << std::setprecision(8) << std::setw(18) << order.price << " |\n";
    }
	
	std::cout << "+----------+----------+--------------------+\n\n";

    std::cout << "BIDS (BUY ORDERS):\n";
    std::cout << "+----------+----------+--------------------+\n";
    std::cout << "|  OrderID | Quantity |              Price |\n";
    std::cout << "+----------+----------+--------------------+\n";
	for (const auto& order : buyList) {
        std::cout << "| " << std::setw(8) << order.id << " | " << std::setw(8) << order.quantity << " | " << std::fixed << std::setprecision(8) << std::setw(18) << order.price << " |\n";
    }
    
	std::cout << "+----------+----------+--------------------+\n";
    std::cout << "============================================\n";
	
}

void OrderBook::removeOrder(int orderId) {
	//Removes Order
	
}

