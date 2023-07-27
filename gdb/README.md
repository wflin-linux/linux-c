# gcc

* -g 加入调试信息,否则不能调试

  > gcc -g test.c -o test.out

* 可以理解为默认gcc 直接编译是 release
* -g 是使用 debug

# gdb 调试

## 进入调试

> gdb test.out

```txt
GNU gdb (Ubuntu 8.1.1-0ubuntu1) 8.1.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from test.out...done.
(gdb) 
```

## 打断点

* b main（函数名）

  或者

* b  绝对路径/文件.c:行数

## 运行

* r 代表run，就会在 断点处停止

  ```txt
  Reading symbols from test.out...done.
  (gdb) 
  (gdb) b main
  Breakpoint 1 at 0x651: file test.c, line 9.
  (gdb) r
  Starting program: /mnt/hgfs/ubuntu/code/linux-c/gdb/test.out 
  
  Breakpoint 1, main () at test.c:9
  9		f();
  (gdb) 
  ```

  

## 单步调试(不进函数体)

* n 

* 有一个语法糖（如果直接回车就是执行上一次运行的那个命令）

  ```txt
  eading symbols from test.out...done.
  (gdb) 
  (gdb) b main
  Breakpoint 1 at 0x651: file test.c, line 9.
  (gdb) r
  Starting program: /mnt/hgfs/ubuntu/code/linux-c/gdb/test.out 
  
  Breakpoint 1, main () at test.c:9
  9		f();
  (gdb) n
  f is function
  10		i = 4;
  (gdb) 
  11		printf("hello world\n");
  (gdb) 
  ```

  

## 单步调试(进入函数体)

* s

  ```txt
  (gdb) r
  Starting program: /mnt/hgfs/ubuntu/code/linux-c/gdb/test.out 
  
  Breakpoint 1, main () at test.c:9
  9		f();
  (gdb) s
  f () at test.c:4
  4		printf("f is function\n");
  (gdb) 
  ```

  

## 查看有哪些断点

* info b

  ```txt
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x0000555555554651 in main at test.c:9
  	breakpoint already hit 1 time
  (gdb) 
  
  ```

## 删除断点

* d

  ```txt
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x0000555555554651 in main at test.c:9
  	breakpoint already hit 1 time
  (gdb) b 3
  Breakpoint 2 at 0x55555555463e: file test.c, line 3.
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x0000555555554651 in main at test.c:9
  	breakpoint already hit 1 time
  2       breakpoint     keep y   0x000055555555463e in f at test.c:3
  (gdb) d 2
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x0000555555554651 in main at test.c:9
  	breakpoint already hit 1 time
  (gdb) 
  ```

  

## 从一个断点跳到另一个断点

* c 【continue】

  ```txt
  (gdb) b /home/ubuntu/ubuntu/code/linux-c/gdb/test.c:4
  Breakpoint 1 at 0x63e: file test.c, line 4.
  (gdb) b /home/ubuntu/ubuntu/code/linux-c/gdb/test.c:11
  Breakpoint 2 at 0x665: file test.c, line 11.
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x000000000000063e in f at test.c:4
  2       breakpoint     keep y   0x0000000000000665 in main at test.c:11
  (gdb) r
  Starting program: /mnt/hgfs/ubuntu/code/linux-c/gdb/test.out 
  
  Breakpoint 1, f () at test.c:4
  warning: Source file is more recent than executable.
  4		printf("f is function\n");
  (gdb) c
  Continuing.
  f is function
  
  Breakpoint 2, main () at test.c:11
  11		printf("hello world\n");
  (gdb)
  ```

## 查看函数调用栈

* bt

  ```txt
  (gdb) b /home/ubuntu/ubuntu/code/linux-c/gdb/test.c:4
  Breakpoint 1 at 0x63e: file test.c, line 4.
  (gdb) info b
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x000000000000063e in f at test.c:4
  (gdb) r
  Starting program: /mnt/hgfs/ubuntu/code/linux-c/gdb/test.out 
  
  Breakpoint 1, f () at test.c:4
  warning: Source file is more recent than executable.
  4		printf("f is function\n");
  (gdb) bt
  #0  f () at test.c:4
  #1  0x000055555555465b in main () at test.c:9
  (gdb) 
  ```

  * 解释：函数经过 main函数，再经过 f 函数 到了 printf("f is function\n") 这行【从下朝上看】

## 监视某个变量的值是否变化

​	值变化时，就会停下

* watch param

## 退出 gdb q

## 更多指令 help 或者 info 直接看