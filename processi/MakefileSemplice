CC=g++

all:	1 2 3 4 5 6 7

1:	01_fork

2:	02_fork_var

3:	03_fork_exec

4:	04_fork_nosincro

5:	05_fork_sincro

6:	06_fork_zombie

7:	07_fork_orfano

01_fork:01_fork.cpp
	$(CC) -o 01_fork 01_fork.cpp

02_fork_var:02_fork_var.cpp
	$(CC) -o 02_fork_var 02_fork_var.cpp

03_fork_exec:03_fork_exec.cpp
	$(CC) -o 03_fork_exec 03_fork_exec.cpp

04_fork_nosincro:04_fork_nosincro.cpp
	$(CC) -o 04_fork_nosincro 04_fork_nosincro.cpp

05_fork_sincro:05_fork_sincro.cpp
	$(CC) -o 05_fork_sincro 05_fork_sincro.cpp

06_fork_zombie:06_fork_zombie.cpp
	$(CC) -o 06_fork_zombie 06_fork_zombie.cpp

07_fork_orfano:07_fork_orfano.cpp
	$(CC) -o 07_fork_orfano 07_fork_orfano.cpp

clean:
	-rm -f 01_fork 02_fork_var 03_fork_exec 04_fork_nosincro 05_fork_sincro 06_fork_zombie 07_fork_orfano