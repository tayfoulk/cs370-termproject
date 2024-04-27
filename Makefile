CXX=gcc
#-Os optimizes for size, important for raspberry pi
CXXFLAGS=-Os
#All dependencies for executables defined here
DEPENDS=socket_conn.o

server: socket_conn.o server.c
	$(CXX) $(CXXFLAGS) socket_conn.o server.c -o server
client: socket_conn.o client.c
	$(CXX) $(CXXFLAGS) socket_conn.o client.c -o client
#Header compilation and packaging
socket_conn.o: socket_conn.c socket_conn.h
	$(CXX) $(CXXFLAGS) -c socket_conn.c

package:
	zip term_project.zip Makefile *.c *.h

clean:
	rm -rf *.o server client
