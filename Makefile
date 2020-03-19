$(eval pyversion := $(shell python3 -c "import sys; print('{}.{}'.format(*sys.version_info[0:2]))"))
$(eval numpydir := $(shell python3 -c "import numpy; print(numpy.get_include())"))

pyFly.so: pyFly.o bfly.o
	gcc -shared -fPIC -o pyFly.so pyFly.o bfly.o -lpython$(pyversion)m -lflycapture

pyFly.o: pyFly.cpp bfly.h
	gcc -fPIC -c -o pyFly.o pyFly.cpp -I$(numpydir) -I/usr/include/python$(pyversion) -I/usr/include/flycapture -lflycapture

bfly.o: bfly.h bfly.cpp
	gcc -fPIC -c -o bfly.o bfly.cpp -I$(numpydir) -I/usr/include/python$(pyversion) -I/usr/include/flycapture -lflycapture 

clean:
	rm -f *.gch
	rm -f *.o
	rm -f *.so


