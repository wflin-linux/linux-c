gcc send.c -I/home/ubuntu/dbus-demo/lib/dbus/include/dbus-1.0 -I/home/ubuntu/dbus-demo/lib/dbus/lib/dbus-1.0/include  -L/home/ubuntu/dbus-demo/lib/dbus/lib -ldbus-1 -o send

gcc recive.c -I/home/ubuntu/dbus-demo/lib/dbus/include/dbus-1.0 -I/home/ubuntu/dbus-demo/lib/dbus/lib/dbus-1.0/include -lrt -lpthread  -L/home/ubuntu/dbus-demo/lib/dbus/lib -ldbus-1 -o recive
