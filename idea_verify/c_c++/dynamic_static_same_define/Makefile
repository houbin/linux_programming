all:   
	#g++ -c -fPIC -o mylib_i.o mylib_i.cc   
	g++ -c -fvisibility=hidden -fPIC -o mylib_i.o mylib_i.cc   
	g++ -c -fPIC -o mylib.o mylib.cc   
	g++ -shared -o libmylib.so mylib.o mylib_i.o   
	g++ -c -o main.o main.cc   
	g++ -o main main.o -L. -lmylib
