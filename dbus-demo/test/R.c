#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>

int main() {
    DBusError error;
    DBusConnection *connection;
    DBusMessage *message;
    DBusMessageIter args;
    int ret;

    dbus_error_init(&error);

    // 连接到DBus系统总线
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "连接到DBus总线失败：%s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    // 发送请求消息
    message = dbus_message_new_method_call("org.example.TestService",
                                           "/org/example/TestObject",
                                           "org.example.TestInterface",
                                           "TestMethod");
    if (message == NULL) {
        fprintf(stderr, "创建DBus消息失败\n");
        dbus_connection_unref(connection);
        return 1;
    }

    // 设置方法参数
    dbus_message_iter_init_append(message, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, "Hello, DBus!")) {
        fprintf(stderr, "添加方法参数失败\n");
        dbus_message_unref(message);
        dbus_connection_unref(connection);
        return 1;
    }

    // 发送消息并等待响应
    ret = dbus_connection_send_with_reply_and_block(connection, message, -1, &error);
    if (ret == DBUS_HANDLER_RESULT_HANDLED) {
        // 处理响应消息
        dbus_message_iter_init(message, &args);
        if (dbus_message_iter_get_arg_type(&args) == DBUS_TYPE_STRING) {
            char *reply;
            dbus_message_iter_get_basic(&args, &reply);
            printf("收到响应：%s\n", reply);
        } else {
            fprintf(stderr, "无效的响应参数类型\n");
        }
    } else {
        fprintf(stderr, "发送DBus消息失败：%s\n", error.message);
        dbus_error_free(&error);
    }

    // 释放资源
    dbus_message_unref(message);
    dbus_connection_unref(connection);

    return 0;
}
