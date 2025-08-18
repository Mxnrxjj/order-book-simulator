enum OrderType {
	BUY,
	SELL
};

struct Order {
	int id;
	OrderType type;
	double price;
	int quantity;
	long long timestamp;
};
