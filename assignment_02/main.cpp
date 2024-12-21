#include "OrderBook.h"
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./stock_sim <input_file>\n";
        return 1;
    }

    // Get the input file name
    std::string inputFileName = argv[1];

    // Create the output file name by replacing "input" with "output"
    std::string outputFileName = inputFileName;
    size_t pos = outputFileName.find("input");
    if (pos != std::string::npos)
    {
        outputFileName.replace(pos, 5, "output"); // Replace "input" with "output"
    }
    else
    {
        outputFileName += "_output"; // Fallback: Append "_output" if "input" is not found
    }

    std::ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        std::cerr << "Error: Cannot open input file.\n";
        return 1;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile)
    {
        std::cerr << "Error: Cannot open output file.\n";
        return 1;
    }

    std::string line;
    std::getline(inputFile, line);
    float lastTradedPrice = std::stof(line);

    OrderBook orderBook(lastTradedPrice);

    int currentTime = 0;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string id, typeStr;
        int quantity;
        float limitPrice = -1.0f;
        iss >> id >> typeStr >> quantity;
        if (iss >> limitPrice)
        {
        }

        Order::Type type = (typeStr == "B") ? Order::Type::BUY : Order::Type::SELL;
        Order newOrder(id, type, quantity, limitPrice, currentTime++);
        orderBook.addOrder(newOrder, outputFile);
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
