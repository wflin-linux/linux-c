INCLUDE = -I/home/ubuntu/dbus-demo/lib/dbus/include/dbus-1.0 -I/home/ubuntu/dbus-demo/lib/dbus/lib -ldbus-1 -I/home/ubuntu/dbus-demo/lib/dbus/lib/dbus-1.0/include
LIB_PATH = -L/home/ubuntu/dbus-demo/lib/dbus/lib

TARGET1 = send
TARGET2 = recive

GCC = gcc

.PHONY: all
all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).o
	$(GCC) -o $@ $^ $(LIB_PATH) -ldbus-1

$(TARGET2): $(TARGET2).o
	$(GCC) -o $@ $^ $(LIB_PATH) -ldbus-1

# build object
%.o: %.c
	$(GCC) -c $< -o $@ $(INCLUDE)

.PHONY: clean
clean:
	-rm -f $(TARGET1) $(TARGET1).o
	-rm -f $(TARGET2) $(TARGET2).o
