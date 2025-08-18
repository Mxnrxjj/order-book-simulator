	#include<iostream>
	#include<string>
	#include<sstream>
	#include<chrono>
	#include "OrderBook.h"
	
	int main() {
		std::cout<<"\nInitializing Order Matching Engine...\n";
		OrderBook obj;
		std::cout<<"\nOrder Matching Engine Is Ready\n";
		std::cout<<"\n-------------------------------\n";
	
		std::cout<<"\n----COMMANDS----\n";
		std::cout<<"\nBUY [quantity] [price]";
		std::cout<<"\nSELL [quantity] [price]";
		std::cout<<"\nCANCEL [OrderID]";
		std::cout<<"\nSHOW";
		std::cout<<"\nEXIT\n";
		
		static int nextOrderID = 1;
		std::string line;
		
		while(true) {
			std::cout<<"\n> ";
			std::getline(std::cin, line);
			
			if(line == "EXIT") {
				break;
			}
			
			if(line.empty()) {
				continue;
			}
			
			std::stringstream ss(line);
	        std::string command;
	        ss>>command;
	        
	        if(command == "BUY") {
	        	int quantity;
	        	double price;
	        	if(ss >> quantity && ss >> price) {
	        		
	        		long long timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
						std::chrono::system_clock::now().time_since_epoch()
					).count();
					
	        		Order newOrder = {nextOrderID++, OrderType::BUY, price, quantity, timeStamp};
	        		obj.addOrder(newOrder);
				} else {
					std::cout<<"\nInvalid format. Use : BUY [quantity] [price]\n";
				}
			}
			else if(command == "SELL") {
				int quantity;
				double price;
				if(ss >> quantity && ss >> price) {
					
					long long timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
						std::chrono::system_clock::now().time_since_epoch()
					).count();
					
					Order newOrder = {nextOrderID++, OrderType::SELL, price, quantity, timeStamp};
					obj.addOrder(newOrder);
				} else {
					std::cout<<"\nInvalid format. Use : SELL [quantity] [price]\n";
				}
			}
			else if(command == "CANCEL") {
				int orderID;
				if(ss >> orderID) {
					obj.removeOrder(orderID);
				} else {
					std::cout<<"\nInvalid format. Use : CANCEL [orderID]\n";
				}
			}
			else if(command == "SHOW") {
				obj.displayBook();
			}
			else {
				std::cout<<"\nUnknown command : '"<<command<<"'\n";
			}
				
		}
		
		std::cout<<"\nTERMINATING ENGINE...";
		return 0;	
	}
