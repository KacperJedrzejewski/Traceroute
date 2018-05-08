Flags = -Wall -Wextra -std=c99
CPP = gcc

traceroute: Makefile traceroute.o send.o receive.o print.o 
	$(CPP) $(Flags)  traceroute.o send.o receive.o print.o -o traceroute

traceroute.o : Makefile traceroute.c send.o receive.o print.o
	$(CPP) -c $(Flags) traceroute.c -o traceroute.o

send.o : Makefile send.c send.h receive.o print.o
	$(CPP)	-c $(Flags)  send.c -o send.o

receive.o : Makefile receive.c receive.h print.o
	$(CPP)	-c $(Flags)  receive.c -o receive.o

print.o : Makefile print.c print.h
	$(CPP)	-c $(Flags) print.c  -o print.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp

