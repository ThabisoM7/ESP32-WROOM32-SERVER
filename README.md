ESP32 WebServer
A lightweight web server hosted on the ESP32-WROOM-32 microcontroller, designed to allow users to monitor and control connected devices through a browser. This project demonstrates how to set up an ESP32 as a Wi-Fi access point or connect it to an existing network, then serve HTML/JavaScript pages for user interaction.

Features
Wi-Fi Access Point / STA mode – Connect the ESP32 to your network or let it create its own.

Embedded Web Pages – Served directly from the ESP32 flash memory.

Real-Time Data – Display sensor readings or device states instantly.

Interactive Controls – Toggle GPIO pins or send commands from the web UI.

Lightweight & Fast – Uses ESPAsyncWebServer or Arduino WebServer for low latency.

Tools & Technologies Used
ESP32-WROOM-32 - Microcontroller hosting the web server
Arduino IDE / PlatformIO - Development environment for writing, compiling, and flashing code to the ESP32
C++ (Arduino Framework) - Main programming language for firmware
HTML, CSS, JavaScript	Frontend code served to the browser
Wi-Fi Library	Handles network connection and AP/STA modes
ESPAsyncWebServer or WebServer Library	Manages HTTP requests and serves files/pages
Serial Monitor	Debugging and monitoring output during development
