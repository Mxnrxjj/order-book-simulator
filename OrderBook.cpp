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
	
	//Lazy deletion begin
	
	while(!buyOrders.empty() && allOrders[buyOrders.top().id].isCancelled) {
		allOrders.erase(buyOrders.top().id); //Removes from master list
		buyOrders.pop(); //Removes from heap
	}
	while(!sellOrders.empty() && allOrders[sellOrders.top().id].isCancelled) {
		allOrders.erase(sellOrders.top().id); //Removes from master list
		sellOrders.pop(); //Removes from heap
	}
	//Lazy deletion end
	
	
	while(!buyOrders.empty() && !sellOrders.empty() && buyOrders.top().price >= sellOrders.top().price) {
		
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
		
		//Lazy deletion if some order in between was marked to be cancelled
		while(!buyOrders.empty() && allOrders[buyOrders.top().id].isCancelled) {
			allOrders.erase(buyOrders.top().id);
			buyOrders.pop();
		}
		while(!sellOrders.empty() && allOrders[sellOrders.top().id].isCancelled) {
			allOrders.erase(sellOrders.top().id);
			sellOrders.pop();
		}
		
	}
	
}

void OrderBook::displayBook() {
	
	//Using vector to store and sort
	std::vector<Order> buyList;
	std::vector<Order> sellList;
	
	for(const auto& pair : allOrders) {
		const Order& order = pair.second;
		if(!order.isCancelled) {
			if(order.type == OrderType::BUY) {
                buyList.push_back(order);
            } else {
                sellList.push_back(order);
            }
		}
	}
	
	std::sort(buyList.begin(), buyList.end(), BuyOrderComparator());
    std::sort(sellList.begin(), sellList.end(), SellOrderComparator());
    
	//Sell price lowest to highest
	std::reverse(sellList.begin(), sellList.end());
	//Buy price highest to lowest
	std::reverse(buyList.begin(), buyList.end());
	
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

void OrderBook::removeOrder(long long orderId) {
	//Removes Order
	auto it = allOrders.find(orderId);
	
	if(it == allOrders.end()) {
		std::cout<<"\nError: Order ID "<<orderId<<" not found!.\n";
		return;
	}
	
	if(it->second.isCancelled) {
		std::cout<<"\nError: Order ID "<<orderId<<" has already been cancelled.\n";
		return;
	}
	
	//Lazy deletion
	it->second.isCancelled = true;
	std::cout<<"\nOrder "<<orderId<<" has been cancelled!.\n";
}

