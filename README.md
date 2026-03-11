# Smart Irrigation System using ESP32 and Blynk (IoT Project)
This project implements an IoT-based Smart Irrigation System using ESP32 and a soil moisture sensor.  
The system continuously monitors soil moisture levels and automatically activates a water pump when the soil becomes too dry.
The project integrates with the Blynk IoT platform to allow real-time monitoring and remote control of the irrigation system through a mobile application.

# Features
- Real-time soil moisture monitoring
- Automatic irrigation when soil moisture falls below threshold
- Manual pump control through the Blynk mobile app
- Remote monitoring of soil moisture levels
- Alert notifications when soil becomes too dry

# Hardware Components
- ESP32 Microcontroller
- Soil Moisture Sensor
- Water Pump
- Relay Module
- Power Supply

# Technologies
- Arduino IDE
- ESP32
- Blynk IoT Platform
- Embedded C++
- IoT Sensors

# Working Principle
1. The soil moisture sensor reads the moisture level from the soil.
2. The ESP32 processes this data and converts it into a percentage.
3. If the moisture level falls below a defined threshold, the system automatically turns on the water pump.
4. Data is sent to the Blynk cloud for real-time monitoring.
5. Users can manually control the pump through the Blynk mobile application.
