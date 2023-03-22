#include "PCA/I2CPeripheral.h"


namespace PiPCA9685 {
I2CPeripheral::I2CPeripheral(const std::string& device, const uint8_t address) {}
I2CPeripheral::~I2CPeripheral() {}
void I2CPeripheral::WriteRegisterByte(const uint8_t register_address, const uint8_t value) {}
uint8_t I2CPeripheral::ReadRegisterByte(const uint8_t register_address) { return 0; }
void I2CPeripheral::OpenBus(const std::string& device) {}
void I2CPeripheral::ConnectToPeripheral(const uint8_t address) {}
}  // namespace PiPCA9685
