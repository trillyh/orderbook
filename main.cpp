#include <iostream>
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;


struct Order {
private:
	int order_id;
	double price;
	double quantity;
	bool isBuy;
	TimePoint now = std::chrono::system_clock::now();

public:
	void setID(int new_id) { order_id = new_id;}
	int getId() {return order_id;}
};

std::string formatTime(TimePoint tp) {
	std::time_t time = std::chrono::system_clock::to_time_t(tp);
	// convert to local time
	std::tm* tm = std::localtime(&time);

	char Buffer[30];
	std::strftime(Buffer, sizeof(Buffer), "%Y-%m-%d %H:%M:%S", tm);

	return std::string(Buffer);
}


int main() {
    std::cout << "hello, world!" <<  std::endl;
    return 0;
}
