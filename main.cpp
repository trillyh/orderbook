#include <iostream>
#include <chrono>
#include <map>
#include <list>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;


struct Order {
	private:
		static int next_id;
		int order_id;
		double price;
		double quantity;
		bool isBuy;
		TimePoint now;

	public:
		void setID(int new_id) { order_id = new_id;}
		int getId() const {return order_id;}

	//Constructor 
	Order(double price, double quantity, bool isBuy): 
		order_id(next_id++),  // assign id to order_id, then increment next_id
		price(price), 
		quantity(quantity), 
		isBuy(isBuy),
		now(std::chrono::system_clock::now()) {}
};

std::string formatTime(TimePoint tp) {
	std::time_t time = std::chrono::system_clock::to_time_t(tp);
	// convert to local time
	std::tm* tm = std::localtime(&time);

	char Buffer[30];
	std::strftime(Buffer, sizeof(Buffer), "%Y-%m-%d %H:%M:%S", tm);

	return std::string(Buffer);
}

void insert_order(std::map<double, std::list<Order>>& orders, double price, double quantity, bool isBuy) {
	Order order(price, quantity, isBuy);

	if (orders.count(price)) {
		orders[quantity].push_back(order);
	} else {
		std::list<Order> new_linkedlist;
		new_linkedlist.push_back(order);
		orders[quantity] = new_linkedlist;
	}

	std::cout << "Created order " << order.getId() << std::endl;
}

void show_orders(std::map<double, std::list<Order>> & orders) {
	for (const auto& pair: orders)  {
		const double& price = pair.first;
		const std::list<Order>& orders_list = pair.second;
		for (const auto& order: orders_list) {
			std::cout << price << " " << order.getId() << std::endl;
		}
	}
}

int Order::next_id = 1;

int main() {
	std::map<double, std::list<Order>> buy_orders;	
	insert_order(buy_orders, 100.5, 10, true);
    insert_order(buy_orders, 101.0, 5, false);
    insert_order(buy_orders, 99.5, 15, true);
    insert_order(buy_orders, 102.0, 8, false);

	show_orders(buy_orders);
    return 0;
}
