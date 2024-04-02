FLAGS = -Werror

main.exe: main.o database.o util.o
	g++ -o main.exe main.o database.o util.o
main.o: main.cpp
	g++ ${FLAGS} -c main.cpp
database.o: database.cpp
	g++ ${FLAGS} -c database.cpp
util.o: util.cpp
	g++ ${FLAGS} -c util.cpp

clean:
	rm *.o
	rm main
