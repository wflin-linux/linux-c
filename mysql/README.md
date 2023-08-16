# 安装 mysql-dev
>   apt-get install libmysqlclient-dev #mysql-8 的
# 创建数据库

```sql
-- 创建数据库
create database rank

-- 使用数据库
use rank

-- 创建数据表t_user
CREATE TABLE `t_user` (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '主键id',
  `user_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '用户名',
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '密码',
  `age` int DEFAULT NULL COMMENT '年龄',
  `adress` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '地址',
  `create_time` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2004 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
```

# 关键api说明

```c
# 创建连接
mysql_real_connect(MYSQL *mysql, const char *host,
                                  const char *user, const char *passwd,
                                  const char *db, unsigned int port,
                                  const char *unix_socket,
                                  unsigned long clientflag);
#其他的api请看 /usr/mysql/mysql.h 文件中的内容，这个 api 拿出来的内容是因为端口参数，如果为0，则是默认 3306 如果是其他端口 覆盖即可
```



# C语言连接 mysql，并查询出 t_user 的内容

main.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>

MYSQL *conn_ptr;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
unsigned int timeout = 7; // 超时时间7秒
int main()
{
    int ret = 0;
    conn_ptr = mysql_init(NULL); // 初始化
    if (!conn_ptr)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

    ret = mysql_options(conn_ptr, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&timeout); // 设置超时选项
    if (ret)
    {
        printf("Options Set ERRO!\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr, "192.168.100.130", "root", "nba1234567", "rank", 0, NULL, 0); // 连接MySQL testdb数据库
    if (conn_ptr)
    {
        printf("Connection Succeed!\n");

        ret = mysql_query(conn_ptr, "SELECT * FROM t_user"); // 执行SQL语句,查找大于5岁的孩子
        if (!ret)
        {
            res_ptr = mysql_store_result(conn_ptr);
            if (res_ptr)
            {
                printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr)); // 在结果集合中返回行的数量
                while ((sqlrow = mysql_fetch_row(res_ptr)))                             // 返回store_result中得到的结构体，并从中检索单行
                {
                    for (int i = 0; i < mysql_num_fields(res_ptr); ++i)
                    {
                        printf("%s ", sqlrow[i] ? sqlrow[i] : "NULL");
                    }
                    printf("\n");
                    // printf("Fetched data\n");
                }
            }

            if (mysql_errno(conn_ptr))
            {
                printf("Connect Erro:%d %s\n", mysql_errno(conn_ptr), mysql_error(conn_ptr)); // 返回错误代码、错误消息
                return -2;
            }

            mysql_free_result(res_ptr);
        }
        else
        {
            printf("Connect Erro:%d %s\n", mysql_errno(conn_ptr), mysql_error(conn_ptr)); // 返回错误代码、错误消息
            return -3;
        }

        mysql_close(conn_ptr);
        printf("Connection closed!\n");
    }
    else // 错误处理
    {
        printf("Connection Failed!\n");
        if (mysql_errno(conn_ptr))
        {
            printf("Connect Erro:%d %s\n", mysql_errno(conn_ptr), mysql_error(conn_ptr)); // 返回错误代码、错误消息
        }
        return -2;
    }

    return 0;
}

```

# 编译运行

> ​	gcc main.c -lmysqlclient -o main.out



结果

```txt
ubuntu@server:~/linux-c/mysql$ ./main.out 
Connection Succeed!
Retrieved 10 rows
1 tom 123 23 四川成都 2023-08-16 13:05:29 2023-08-16 13:05:29 
2 tim 123 24 四川巴中 2023-08-16 13:05:29 2023-08-16 13:05:29 
3 mary 1234 25 四川宜宾 2023-08-16 13:05:29 2023-08-16 13:05:29 
4 Xiong Jialun RduelvJwP0 936 EPkte701Ih 2010-01-06 14:50:58 2021-07-06 14:06:00 
5 Fong Ming Sze z004Ja0ydF 650 FwHQpFjesg 2007-01-09 21:22:47 2010-11-11 00:51:04 
6 Mori Ikki y4vNSVYFHt 633 Pe1Q1iCvRL 2022-04-19 20:57:02 2002-11-28 19:50:35 
7 Sun Zhennan Hu8f8mESTn 630 CffaBtumw9 2023-02-12 03:06:20 2009-08-25 13:58:24 
8 Uchida Momoka JA2D1jXEG9 313 Jow0NJJXbI 2001-02-12 20:12:16 2000-07-03 16:50:59 
9 Zhao Lu azjF5uDZHF 516 EJ2HUN3GPE 2010-03-23 09:22:53 2000-06-08 10:06:49 
10 Ishida Daichi 3GhUPHufCv 496 ApXqGkQVO9 2015-12-27 08:47:10 2005-07-11 18:16:16 
Connection closed!
```

