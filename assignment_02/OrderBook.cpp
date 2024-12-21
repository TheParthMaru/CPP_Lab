#include "OrderBook.h"
#include <algorithm>
#include <iomanip>

OrderBook::OrderBook(float initialPrice) : lastTradedPrice(initialPrice), currentTime(0) {}

void OrderBook::addOrder(const Order &order, std::ofstream &outFile)
{
    (order.type == Order::Type::BUY ? buyOrders : sellOrders).push_back(order);
    matchOrders(outFile);
    printPendingOrders();
}

void OrderBook::sortOrders()
{
    auto buyComparator = [](const Order &a, const Order &b)
    {
        if (a.isMarketOrder() != b.isMarketOrder())
            return a.isMarketOrder();
        if (a.limitPrice != b.limitPrice)
            return a.limitPrice > b.limitPrice;
        return a.arrivalTime < b.arrivalTime;
    };

    auto sellComparator = [](const Order &a, const Order &b)
    {
        if (a.isMarketOrder() != b.isMarketOrder())
            return a.isMarketOrder();
        if (a.limitPrice != b.limitPrice)
            return a.limitPrice < b.limitPrice;
        return a.arrivalTime < b.arrivalTime;
    };

    std::sort(buyOrders.begin(), buyOrders.end(), buyComparator);
    std::sort(sellOrders.begin(), sellOrders.end(), sellComparator);
}

void OrderBook::matchOrders(std::ofstream &outFile)
{
    sortOrders();
    while (!buyOrders.empty() && !sellOrders.empty())
    {
        Order &buy = buyOrders.front();
        Order &sell = sellOrders.front();

        if (!buy.matches(sell))
            break;

        int tradeQty = std::min(buy.quantity, sell.quantity);
        float execPrice = (buy.isMarketOrder() && sell.isMarketOrder()) ? lastTradedPrice
                                                                        : (buy.isMarketOrder() ? sell.limitPrice
                                                                                               : (sell.isMarketOrder() ? buy.limitPrice : std::min(buy.limitPrice, sell.limitPrice)));

        lastTradedPrice = execPrice;
        outFile << "order " << buy.id << " " << tradeQty << " shares purchased at price " << std::fixed << std::setprecision(2) << execPrice << "\n";
        outFile << "order " << sell.id << " " << tradeQty << " shares sold at price " << std::fixed << std::setprecision(2) << execPrice << "\n";

        buy.quantity -= tradeQty;
        sell.quantity -= tradeQty;

        if (buy.quantity == 0)
            buyOrders.erase(buyOrders.begin());
        if (sell.quantity == 0)
            sellOrders.erase(sellOrders.begin());
    }
}

void OrderBook::printPendingOrders() const
{
    std::cout << "Last trading price: " << std::fixed << std::setprecision(2) << lastTradedPrice << "\n";
    std::cout << "Buy                       Sell\n";
    std::cout << "------------------------------------------\n";

    size_t maxRows = std::max(buyOrders.size(), sellOrders.size());
    for (size_t i = 0; i < maxRows; ++i)
    {
        if (i < buyOrders.size())
            std::cout << buyOrders[i] << "\t";
        else
            std::cout << "\t\t\t";
        if (i < sellOrders.size())
            std::cout << sellOrders[i];
        std::cout << "\n";
    }
}
