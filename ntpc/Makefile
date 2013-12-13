main.exe: functions.o training.o
	g++ -L/usr/local/lib -lgsl -lgslcblas -lm -lpcap functions.o training.o -omain.exe
debug: functions.o training.o
	g++ -lpcap -g functions.o training.o -omain.exe
release: functions.o training.o
	g++ -lpcap -O2 functions.o training.o -omain.exe
functions.o: functions.c
	g++ -g -c -Wall -I/usr/local/include functions.c
training.o: training.c
	g++ -g -c -Wall -I/usr/local/include training.c
clean:
	rm -rf *.o
