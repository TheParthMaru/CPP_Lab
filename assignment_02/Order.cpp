#include "Order.h"

Order::Order(const std::string &id, Type type, int quantity, float limitPrice, int arrivalTime)
    : id(id), type(type), quantity(quantity), limitPrice(limitPrice), arrivalTime(arrivalTime)
{
    orderType = (limitPrice == -1.0f) ? OrderType::MARKET : OrderType::LIMIT;
}

bool Order::isMarketOrder() const
{
    return orderType == OrderType::MARKET;
}

bool Order::matches(const Order &other) const
{
    if (type == other.type)
        return false; // Cannot match same types
    if (isMarketOrder() || other.isMarketOrder())
        return true; // Market orders match anything
    return (type == Type::BUY) ? (limitPrice >= other.limitPrice) : (limitPrice <= other.limitPrice);
}

void Order::print() const
{
    std::cout << id << " " << (type == Type::BUY ? "B" : "S") << " " << quantity;
    if (!isMarketOrder())
        std::cout << " " << limitPrice;
    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Order &order)
{
    os << order.id << " " << (order.type == Order::Type::BUY ? "B" : "S") << " "
       << order.quantity << (order.isMarketOrder() ? "" : " " + std::to_string(order.limitPrice));
    return os;
}
