Flags = -Wall -Wextra -std=c99
CPP = gcc

traceroute: Makefile traceroute.o send.o receive.o print.o
	$(CPP) $(Flags) -o traceroute traceroute.o send.o receive.o print.o
traceroute.o : Makefile traceroute.c 
	$(CPP) $(Flags) traceroute.c -o traceroute.o
send.o : Makefile send.h
	$(CPP)	-c $(Flags) send.h -o send.o
receive.o : Makefile receive.h
	$(CPP)	-c $(Flags) receive.h -o receive.o
print.o : Makefile print.h
	$(CPP)	-c $(Flags) print.h -o print.o
clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp

