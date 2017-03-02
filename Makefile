GCC:=g++
LLVM_FLAGS:=`llvm-config-3.5 --cxxflags  --libs core native` `llvm-config-3.5 --ldflags` 
FLAGS:=-lpthread -ltinfo -ldl 
SOURCES:=tut1.cpp

all:
	$(GCC) -g $(SOURCES) $(LLVM_FLAGS) $(FLAGS) -o tut1

#c++ -g tut1.cpp `llvm-config-3.5 --cxxflags  --libs core native` `llvm-config-3.5 --ldflags` -lpthread -ltinfo -ldl -o tut1  

clean:
	@rm tut1
