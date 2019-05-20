all: lib
	gcc solution.c -fPIC -ldl -Wl,-rpath=. -o solution
lib:
	gcc -shared -o libShared.so -L=. -ldl -fPIC Shared.c
clean:
	-rm -r *.so solution
