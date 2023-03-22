
all:
	g++ -std=c++14 src/global.cpp src/mleg.cpp src/mservo.cpp src/main.cpp src/PCA/PCA9685.cpp src/PCA/I2CPeripheral.cpp -Iinclude/ -li2c -o spider

local:
	g++ -std=c++14 src/global.cpp src/mleg.cpp src/mservo.cpp src/main.cpp src/PCA/PCA9685.cpp src/PCA/I2CPeripheral_local.cpp -Iinclude/ -o spider