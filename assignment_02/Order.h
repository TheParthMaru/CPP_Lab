#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>

class Order
{
public:
    enum class Type
    {
        BUY,
        SELL
    };
    enum class OrderType
    {
        LIMIT,
        MARKET
    };

    std::string id;
    Type type;
    OrderType orderType;
    int quantity;
    float limitPrice;
    int arrivalTime; // To track order arrival for priority

    Order(const std::string &id, Type type, int quantity, float limitPrice, int arrivalTime);
    bool isMarketOrder() const;
    bool matches(const Order &other) const;
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Order &order);
};

#endif // ORDER_H
