# SIC Assembler & Memory Simulator

A complete Two-Pass Assembler for the Simplified Instructional Computer (SIC) architecture, developed for the **Systems Programming (CC410)** course.

## 🚀 Features
- **Pass 1:** - Generates the Symbol Table.
  - Calculates addresses (Location Counter).
- **Pass 2:** - Generates Object Code (Header, Text, and End records).
  - Handles `Forward References` and `Indexed Addressing`.
- **Formatting:** - Outputs a load-ready Object Program compatible with SIC Simulators.

## 🛠️ How to Build & Run
1. **Compile the Assembler:**
   ```bash
   g++ src/main.cpp -o sic_assembler

