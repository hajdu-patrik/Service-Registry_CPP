![C++](https://img.shields.io/badge/C%2B%2B-11-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/Build-CMake-064F8C?style=flat&logo=cmake&logoColor=white)
![Gradle](https://img.shields.io/badge/Build-Gradle-02303A?style=flat&logo=gradle&logoColor=white)
![OOP](https://img.shields.io/badge/Concept-Polymorphism-blueviolet?style=flat)
![Pattern](https://img.shields.io/badge/Pattern-Prototype_(Clone)-blueviolet?style=flat)
![Data Structure](https://img.shields.io/badge/Container-Custom_Vector_template-critical?style=flat)
![Memory](https://img.shields.io/badge/Memory-Manual_Mgmt_%2F_Leak_Free-important?style=flat)
![GTest](https://img.shields.io/badge/Test-GTest--lite-02553D?style=flat&logo=google&logoColor=white)

# Service Registry C++

This is a comprehensive, menu-driven C++ console application developed for the "Programming Fundamentals 2" course. It simulates a complete management system for a car service station, allowing for the tracking of clients, vehicles, and their detailed, polymorphic service histories.

The project is built from scratch in C++ and serves as a practical demonstration of core object-oriented programming (OOP) principles, dynamic memory management, and custom data structures.

---

## 📚 Features

* **Client & Vehicle Management:** Full CRUD (Create, Read, Update, Delete) operations for clients and their associated vehicles.
* **Detailed Service History:** Track all service events (Repairs, Maintenance, Technical Inspections) linked to a specific vehicle.
* **Service Reminders:** Automatically generate warnings for upcoming technical inspections or required oil changes based on stored mileage and service dates.
* **Persistent Storage:** Save the entire system state (all clients, cars, and histories) to custom-formatted `.txt` files and load them back at runtime.
* **Text-Based UI (TUI):** A user-friendly, menu-driven console interface for all operations, with clear ASCII-art branding.

## 🛠️ Technical Implementation

This project was built to demonstrate proficiency in C++ and object-oriented design. The key technical features are:

### 1. Polymorphism & Inheritance

The core of the service tracking system is built on polymorphism.
* An abstract base class `VegzettMuvelet` (Completed Operation) defines a common interface.
* Concrete classes `Javitas` (Repair), `Karbantartas` (Maintenance), and `Vizsga` (Inspection) inherit from this base class.
* The `Auto` (Car) class stores the service history in a `Vector<VegzettMuvelet*>`, allowing it to manage different service types dynamically.

### 2. Custom Templated `Vector` Container

Instead of `std::vector`, this project uses a custom-built, templated `Vector.hpp` container. This class implements the core functionality of a dynamic array, including:
* Dynamic memory allocation (`new[]`, `delete[]`).
* Capacity and size management (`reserve`, `resize`, `push_back`).
* Iterator support (`begin()`, `end()`).

### 3. Manual Memory & Resource Management

The use of raw pointers (`VegzettMuvelet*` in the `Vector`) necessitates careful manual memory management to prevent leaks and ensure deep copies.
* **`clone()` Method:** A virtual `clone()` function is implemented in the `VegzettMuvelet` hierarchy (part of the Prototype design pattern).
* **Deep Copy Semantics:** The `Auto` class's copy constructor and assignment operator use the `clone()` method to perform a deep copy of the service history, ensuring that copied objects have their own independent data.
* **`memtrace.h`:** The project integrates the `memtrace.h` utility to detect memory leaks and double-free errors during testing.

### 4. Testing

The system is validated using:
* **GTest-lite:** A lightweight testing framework is used for functional tests, covering adding, updating, deleting, and searching for clients, cars, and service records.
* **Interface Tests:** The `teszt.cpp` file contains basic interface-level tests to ensure all public methods are callable as specified.

---

## 📂 Modular Folder Structure

To enforce clarity and the separation of concerns (OOP principle), the project uses a standard, Gradle-compatible directory layout:

- **`src/main/cpp/`:** Contains all C++ implementation files (`.cpp`). This is where the core logic resides (e.g., `Auto.cpp`, `Ugyfel.cpp`, `Memtrace.cpp`).
- **`src/main/public/`:** Contains all public header files (`.h`, `.hpp`). This defines the interfaces and data structures used throughout the project (e.g., `Auto.h`, `Vector.hpp`).
- **`data/`:** Stores input files for persistence, like initial client or vehicle data (`init_ugyfel_ufl.txt`, `init_auto_auo.txt`).
- **`build/`:** The target output directory for all generated files (object files and the final executable).
- **`build.gradle.kts`:** The configuration file for the Gradle build system (Modern Build Tool).
- **`CMakeLists.txt`:** The configuration file for the CMake build system (Standard Build Tool).

---

## ⚙️ Compilation & Execution

The project supports **Gradle** (recommended for modern automation).

### A. Modern Method (Using Gradle)
The project is configured with a modern Kotlin DSL Gradle build script, which handles compilation, linking, and dependency management (including copying data files) automatically.

1.  **Build (Compile & Link):**
    ```bash
    gradle clean build
    ```
    *Note: This task automatically compiles the code and copies the required `.txt` files to the output directory.*

2.  **Run Application:**
    Navigate to the build directory and run the executable:
    ```bash
    ./build/exe/main/debug/szerviz_app.exe
    ```

3.  **Create Release:**
    To create an optimized release build:
    ```bash
    gradle installRelease
    ```

### B. Direct GCC/G++ Compilation (Fallback Method)
This is the most reliable method in minimal environments. It explicitly links all source files and enables the necessary features.

1.  **Prerequisites:** The build/ directory must exist.

2.  **Compile and Link:**
    ```bash
    g++ -Wall -Wextra -std=c++11 -g -I src/main/public -DMEMTRACE src/main/cpp/*.cpp -o build/szerviz_app.exe -lstdc++
    ```

3.  **Run Application:**
    Make sure to copy the txt files from `data/` next to the executable before running.
    ```bash
    ./build/szerviz_app.exe
    ```

---

## 💾 File-Based Persistence

The system saves and loads data using two custom `.txt` file formats:

* **Client File (`*_ufl.txt`):** Stores client data.
    * *Format:* `nev-telefonszam-email`
* **Auto File (`*_auo.txt`):** Stores vehicle and service data.
    * *Format:* `rendszam-marka-tipus-km_ora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_nev`
    * The `szervizmuveletek` field is a complex, semi-colon-delimited list of polymorphic service records.

---

## 📦 Releases

| Version | Description | Download |
| :--- | :--- | :--- |
| **v1.0.0** | **Service Registry v1.0.0** - Initial release of the comprehensive car service management system. Features full CRUD operations, polymorphic service tracking, custom memory management logic, and file-based persistence. | [Source code (zip)](https://github.com/hajdu-patrik/Service-Registry_CPP/archive/refs/tags/v1.0.0.zip) |
