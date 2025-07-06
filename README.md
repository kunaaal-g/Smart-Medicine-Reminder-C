# 💊 Smart Medicine Reminder System in C

A console-based medicine reminder system written in C that helps users remember to take their medicines at the right time every day.

## 📌 Features

- Add medicine name, dosage, and up to 5 reminder times per day
- View saved medicine schedules
- Real-time reminder system using system clock
- Beep beep alert sound
- AM/PM time format (Indian-style)
- Snooze feature (5-minute delay)
- Local file-based data storage

## 🧠 Tech Used

- `C Language`
- `Struct`, arrays
- `File handling` (`fopen`, `fread`, `fwrite`)
- `time.h` for system clock
- `sleep()` for background checking

## 🛠️ How to Compile & Run

### On Linux / Android Termux:
```bash
gcc medicine_reminder.c -o reminder
./reminder
