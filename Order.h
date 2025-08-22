#ifndef ORDER_H
#define ORDER_H

enum OrderType {
	BUY,
	SELL
};

struct Order {
	long long id;
	OrderType type;
	double price;
	int quantity;
	long long timestamp;
	bool isCancelled = false;
};

#endif
