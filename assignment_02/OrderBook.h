#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include <vector>
#include <string>
#include <fstream>

class OrderBook
{
private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
    float lastTradedPrice;
    int currentTime;

    void sortOrders();
    void matchOrders(std::ofstream &outFile);

public:
    OrderBook(float initialPrice);
    void addOrder(const Order &order, std::ofstream &outFile);
    void printPendingOrders() const;
    float getLastTradedPrice() const;
};

#endif // ORDERBOOK_H
