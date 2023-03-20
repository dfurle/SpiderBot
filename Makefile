

all:
	g++ src/mleg.cpp src/mservo.cpp src/main.cpp -Iincludes/ -L/usr/local/lib/static/ -lPiPCA9685 -li2c -o spider