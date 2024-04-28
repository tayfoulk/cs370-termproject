CXX=gcc
#-Os optimizes for size, important for raspberry pi
CXXFLAGS=-Os
#All dependencies for executables defined here
DEPENDS=socket_conn.o sha1.o Encryption.o

#Main executables
server: socket_conn.o server.c
	$(CXX) $(CXXFLAGS) socket_conn.o server.c -o server
client: socket_conn.o client.c
	$(CXX) $(CXXFLAGS) socket_conn.o client.c -o client
Consumer: Consumer.c $(DEPENDS)
	$(CXX) $(CXXFLAGS) $(DEPENDS) Consumer.c -o Consumer
#Header compilation
socket_conn.o: socket_conn.c socket_conn.h
	$(CXX) $(CXXFLAGS) -c socket_conn.c

Encryption.o: Encryption.c Encryption.h
	$(CXX) $(CXXFLAGS) -c Encryption.c

sha1.o: sha1.c sha1.h
	$(CXX) $(CXXFLAGS) -c sha1.c

#Helper stuff
package:
	zip term_project.zip Makefile *.c *.h

clean:
	rm -rf *.o server client
