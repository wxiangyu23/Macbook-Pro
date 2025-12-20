#  Vital Signs Monitoring System - Project Summary

This C-based project implements a real-time monitoring system that simulates and tracks vital signs including heart rate, blood oxygen, and temperature. The system features a multi-threaded architecture with three core components: a sensor thread that generates realistic simulated data, a display thread that renders real-time metrics using ncurses terminal UI, and data processing for anomaly detection.

Technically, the project leverages pthreads for concurrent execution, using mutex locks to ensure thread-safe access to shared data structures. The `VitalSigns` struct serves as the central data model, protected by a mutex to prevent race conditions during multi-threaded access. The alert system triggers visual (red text) and auditory warnings for abnormal readings, while all data is persisted to a CSV log file with formatted timestamps.

The system includes graceful shutdown handling for SIGINT/SIGTERM signals, ensuring clean resource release. With its modular design (sensor simulation, alert management, data logging, UI display), the project demonstrates effective use of C language features, system programming concepts, and concurrent programming principles in a practical monitoring application.


## Overview
A real-time C-based monitoring system that simulates and tracks factory vital signs (heart rate, blood oxygen, temperature) with alert mechanisms and data logging.

## Features
- **Sensor Simulation**: Generates realistic vital sign data at configurable intervals
- **Real-time Monitoring**: Displays live metrics using ncurses terminal UI
- **Anomaly Detection**: Triggers visual and auditory alerts for abnormal readings
- **Data Logging**: Records all vital signs to CSV format for analysis
- **Thread-Safe Design**: Uses pthreads and mutex locks to ensure data consistency
- **Graceful Shutdown**: Handles SIGINT/SIGTERM signals for clean termination

## Technical Stack
- **Language**: C
- **Libraries**: ncurses, pthreads, standard C libraries
- **Threading**: Multi-threaded architecture (sensor, display, processing)
- **Data Format**: CSV logging with timestamp, heart rate, oxygen, temperature

## Installation & Usage
```bash
# Compile
make

# Run
./bin/factory

# Stop
Press Ctrl+C to terminate gracefully
```

## Data Logging
Vital signs are logged to `vital_log.csv` with the format:
 



## Alert System
- Red text alerts for abnormal readings
- Supports heart rate, blood oxygen, and temperature anomalies
- Auditory notification via system bell

## License
MIT
