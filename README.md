# Smart-Bell-System-for-Educational-Institute
An Arduino-based smart bell system designed to automate school/college bell schedules. Integrates an RTC (DS3231), LCD display, EEPROM, and push buttons to allow customizable daily routines with real-time activation of period bells. Supports dynamic timetables for each weekday, reducing manual effort and improving time management.
# 🔔 Automatic Smart Bell System for Educational Institutes

An Arduino-based smart bell system designed to automate the scheduling and ringing of class period bells in schools and colleges. It offers dynamic weekday routines, real-time clock accuracy, and EEPROM memory for persistent settings—ensuring efficient and maintenance-free operation.

---

## 📌 Features

- ⏰ **Real-Time Clock (RTC DS3231):** Provides accurate timekeeping for scheduled bell activation.
- 📅 **Custom Weekly Routine:** Supports different subject-teacher routines for each weekday (Monday to Friday).
- 💾 **EEPROM Integration:** Saves all period and break timings even after power failure.
- 📺 **16x2 LCD Display:** Shows current time, active period, and subject details in real-time.
- 🔘 **Push Button Interface:** Easy input method to set/update class periods, breaks, and durations.
- 🔔 **Relay-Based Bell Control:** Rings bell automatically at the beginning of each period and break.

---

## 🏫 Use Case

This project is ideal for educational institutions looking to eliminate manual bell ringing and ensure timely class transitions. It minimizes human error and allows flexible schedule management across the week.

---

## 🛠️ Tech Stack / Components

- **Arduino Uno**
- **RTC Module (DS3231)**
- **LCD Display (16x2 with I2C)**
- **EEPROM (built-in)**
- **Relay Module**
- **Buzzer/Electric Bell**
- **Push Buttons**
- **Breadboard & Jumper Wires**

---

## 🔧 System Workflow

1. User sets the timetable for each weekday (Periods 1–8 + Breaks).
2. The system reads the time from the RTC module.
3. When current time matches a stored period/break time:
   - Relay is triggered to ring the bell.
   - LCD displays subject and teacher information.
4. EEPROM ensures saved settings remain after power loss.

---

## 🚀 Future Enhancements

- Add **web/mobile app** interface for remote schedule management
- Integrate **Bluetooth/Wi-Fi (ESP8266/ESP32)** for wireless configuration
- Add **password protection** for admin settings
- Include **special mode** for exam days or holidays

---


