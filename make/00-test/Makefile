
OBJ = add.o sub.o multi.o calc.o
TARGET=calc

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@

# add.o:add.cpp
# 	$(CXX) -c add.cpp -o add.o

# sub.o:sub.cpp
# 	$(CXX) -c sub.cpp -o sub.o

# multi.o:multi.cpp
# 	$(CXX) -c multi.cpp -o multi.o

# calc.o:calc.cpp
# 	$(CXX) -c calc.cpp -o calc.o

# clean:	
# 	$(RM) -fr *.o $(TARGET)

add.o:add.cpp
	$(CXX) -c $^ -o $@

sub.o:sub.cpp
	$(CXX) -c $^ -o $@
multi.o:multi.cpp
	$(CXX) -c $^ -o $@

calc.o:calc.cpp
	$(CXX) -c $^ -o $@

clean:	
	$(RM) $(OBJ) $(TARGET)


show:
	@echo $(AS)
	@echo $(CC)
	@echo $(CPP)
	@echo $(CXX)
	@echo $(RM)