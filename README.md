# SmartFan
Embedded system for fan control via WiFi. With this system, you will be able to turn the fan on/off through a web interface, as well as automate its activation at a configured temperature.

## 🛠️ Technologies used
- C++
- Arduino
- PlatformIO

## 🚀 How to run
Before running, you must configure the project. Rename the file `include/Config.h.example` to `include/Config.h` and modify it with credentials and settings to your liking.
```cpp
// Internal system parameters

#define NTC_PIN 33  // NTC pin
#define RELAY_PIN 4 // Relay pin
#define NTC_V 3.3   // NTC pin Voltage

#define ESP32_ADC_BITS 12
#define ADC_MAX (float)((1 << ESP32_ADC_BITS) - 1)

// NTC parameters (adjust for your project)

#define SERIES_RESISTOR 10000.0    // fixed resistor (10k)
#define NOMINAL_RESISTANCE 10000.0 // NTC in 25°C
#define NOMINAL_TEMPERATURE 25.0   // °C
#define B_COEFFICIENT 3950.0

// User config
#define RF_INACTIVITY_MS 60000     // Inactivity rf watchdog in ms
#define RF_TIMEOUT 5000            // Timeout for switching from ble to bt in ms
#define WIFI_RECONNECT_TIMER 60000 // Wifi reconnect timer time in ms
#define WIFI_SCAN_TASK_DELAY                                                   \
  15000                 // Delay for waiting before processing scan results
#define INDICATOR_PIN 2 // Pin for wifi indication
```

You can also use the `PIO_ENV` variable to access the ESP logs, with `PIO_ENV=dev` for source code logs and `PIO_ENV=verbose` for the entire system.

### Pre-requirements
- PlatformIO (Core or IDE)

Add uri `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to additional_urls in arduino-cli

### ✅ Running
```bash
# Clone repository
git clone https://github.com/avrahambenaram/smart-fan.git

# Access directory
cd smart-fan

# Upload firmware
pio run -t uploadfs && pio run -t upload

# Monitor serial
pio device monitor
```
