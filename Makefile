

all:
	# g++ -std=c++11 src/mleg.cpp src/mservo.cpp src/main.cpp -Iinclude/ -L/usr/local/lib/static/ -lPiPCA9685 -li2c -o spider
	g++ -std=c++14 src/global.cpp src/mleg.cpp src/mservo.cpp src/main.cpp src/PCA/PCA9685.cpp src/PCA/I2CPeripheral.cpp -Iinclude/ -o spider