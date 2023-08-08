# 伪目标 .PHONY:clean
# 声明伪目标之后，makefile将不会判断目标是否存在该目标是否需要更新


.PHONY:clean show

OBJ = add.o sub.o multi.o calc.o
TARGET=calc

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@

# .o 依赖于对应的 .cpp 

%.o:%.cpp
	$(CXX) -c $^ -o $@

clean:	
	$(RM) $(OBJ) $(TARGET)

show:
	@echo $(AS)
	@echo $(CC)
	@echo $(CPP)
	@echo $(CXX)
	@echo $(RM)

	@echo $(wildcard ./*.cpp)
	@echo $(patsubst .%.cpp,%.o,./*.cpp)
	@echo $(OBJ)




