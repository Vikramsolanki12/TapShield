# 🛡️ TapShield – Wearable SOS Safety Device

TapShield is a compact wearable SOS device designed for emergency situations. With a simple tap pattern on the piezo sensor, users can trigger different safety responses — including sending SMS alerts to trusted contacts using the SIM800L GSM module. The device can also intelligently recognize tap patterns using TinyML for more personalized and secure actions.

---

## 🚀 Features

- 👆 **Tap-Activated SOS Alerts**
- 📡 **SIM800L GSM Module for SMS Sending**
- 🔋 **Battery Powered & Compact Design**
- 🧠 **TinyML Model for Pattern Classification (Optional)**
- 📊 **Real-time serial monitoring and debugging**
- 🛠️ **Modular and Customizable Hardware Setup**

---

## 📦 Components Used

| Component         | Description                                 |
|------------------|---------------------------------------------|
| Arduino Nano     | Main microcontroller                        |
| Piezo Sensor     | Detects tap vibrations                      |
| SIM800L Module   | Sends SMS messages via GSM network          |
| Battery (LiPo)   | Powers the wearable                         |
| LEDs/Buzzer      | Feedback indicators (optional)              |

---

## 🧠 TinyML Integration (Optional)

TapShield can recognize different tap patterns using a trained **TinyML model** deployed via **Edge Impulse**. Patterns like *double tap*, *triple tap*, or *long press* can trigger distinct safety actions.

---
## folder structure
|_arduino_code
|_ML
|_images
presention

### Example:
| Tap Pattern | Action                       |
|-------------|------------------------------|
| Single Tap  | Send SMS of safe       |
| Double Tap  | send SMS call me |
| Triple Tap  | Send SMS of Emergency       |

---

## 🛠️ Setup Instructions

1. **Connect Hardware** as per the [Fritzing diagram].
2. Upload the `TapShield.ino` Arduino sketch using Arduino IDE.
3. If using TinyML:
   - Generate and deploy the model using [Edge Impulse](https://edgeimpulse.com).
   - Include the model’s `.h` file in your sketch.
4. Insert a working SIM card into the SIM800L module.
5. Power on the device and start tapping!

---

## 📽️ Demo Video

> [🔗 Watch TapShield in Action](https://youtu.be/ucn77c47pr0?si=Vud8ySa1ZD4SDQ5O)

---

## 🧠 Future Scope

- 📍 **GPS Integration** – for real-time location sharing
- 🔋 **Battery Optimization** – smart sleep modes
- ☁️ **IoT Dashboard** – live monitoring and analytics

---

## 📝 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙋‍♂️ Author

**Vikram Solanki**  
🔗 [GitHub](https://github.com/Vikramsolanki12) | ✉️ [Email](mailto:solankijogaram5@gmail.com)

---



