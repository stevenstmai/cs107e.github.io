MinIMU-9 v5 Gyro, Accelerometer, and Compass (LSM6DS33 and LIS3MDL Carrier)
- https://www.pololu.com/product/2738

LSM6DS33  3D Accelerometer and Gyro 
- https://www.pololu.com/product/2736

A minimum of four connections are necessary to use these I2C devices.
VIN (red), GND (black), SCL (white), and SDA (yellow). 
- SDA is GPIO_PIN2
- SCL is GPIO_PIN3

VIN should be connected to a 2.5 V to 5.5 V source. Current demo
uses 5V.

SCL and SDA should be connected to an I²C bus operating at the same
logic level as VIN..

(Alternatively, if you are using the board with a 3.3 V system, you
can leave VIN disconnected and bypass the built-in regulator by
connecting 3.3 V directly to VDD.)

MinIMU-9 v5 board and pins
- doc/minimu.jpg
LSM6DS33 breakout board and pins
- doc/lsm6ds33.jpg

Below are the i2c addresses for https://www.pololu.com/product/2738
    LSM6DS33 (gyro and accelerometer)    0b1101011  0x6b
    LIS3MDL (magnetometer)               0b0011110  0x1e

NOTE: The address for your sensor may be different! Read spec sheet and
      check for label on your part. (This helpful advice brought to you by
      Jenna Ruzekowicz)

$ make run
- prints out acceleration in milli-g's
