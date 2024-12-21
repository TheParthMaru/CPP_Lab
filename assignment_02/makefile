CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJS = main.o Order.o OrderBook.o

all: stock_sim

stock_sim: $(OBJS)
	$(CXX) $(CXXFLAGS) -o stock_sim $(OBJS)

main.o: main.cpp Order.h OrderBook.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Order.o: Order.cpp Order.h
	$(CXX) $(CXXFLAGS) -c Order.cpp

OrderBook.o: OrderBook.cpp OrderBook.h Order.h
	$(CXX) $(CXXFLAGS) -c OrderBook.cpp

clean:
	rm -f *.o stock_sim
