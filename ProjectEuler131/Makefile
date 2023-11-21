INCLUDE=-I/usr/local/opt/flex/include/ -I/usr/local/opt/llvm/include
LDFLAGS=-L/usr/local/opt/llvm/lib -L/usr/local/opt/llvm/lib/c++ -Wl,-rpath,/usr/local/opt/llvm/lib/c++
DBGFLAGS=-fsanitize=address -g -fsanitize=leak 
FASTFLAGS=-Ofast -flto=full
CXXFLAGS=$(INCLUDE) $(FASTFLAGS) -std=c++2b
LIBS=

SOURCES=main.cpp
OBJS=$(SOURCES:.cpp=.o)

.PHONY: answer

answer: euler
	./euler 

euler: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(LDFLAGS) $^ -o $@

main.o: Sieve.hpp

.PHONY: clean

clean:
	rm -f euler
	rm -rf *.dSYM *.gcda *.gcno merge.out default.profraw
	rm -f $(OBJS)