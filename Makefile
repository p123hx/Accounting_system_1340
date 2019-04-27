CXXFLAGS += -std=c++11

all: banking

banking: account.o controller.o fastrng.o interest.o ACCOUNTING.o AccountingSystem.o
	$(CXX) -o banking *.o

account.o: account.cpp
	$(CXX) -c $(CXXFLAGS) account.cpp

controller.o: controller.cpp
	$(CXX) -c $(CXXFLAGS) controller.cpp

fastrng.o: fastrng.c
	$(CC) -c $(CFLAGS) fastrng.c

interest.o: interest.cpp
	$(CXX) -c $(CXXFLAGS) interest.cpp

ACCOUNTING.o: ACCOUNTING.cpp
	$(CXX) -c $(CXXFLAGS) ACCOUNTING.cpp

AccountingSystem.o: AccountingSystem.cpp
	$(CXX) -c $(CXXFLAGS) AccountingSystem.cpp

clean:
	rm -rf *.o banking

.PHONY: all clean
