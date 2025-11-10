# C++ Car Service Management System

This is a comprehensive, menu-driven C++ console application developed for the "Programming Fundamentals 2" (Programozás alapjai 2.) course. It simulates a complete management system for a car service station, allowing for the tracking of clients, vehicles, and their detailed, polymorphic service histories.

The project is built from scratch in C++ and serves as a practical demonstration of core object-oriented programming (OOP) principles, dynamic memory management, and custom data structures.

## 🌟 Core Features

* **Client & Vehicle Management:** Full CRUD (Create, Read, Update, Delete) operations for clients and their associated vehicles.
* **Detailed Service History:** Track all service events (Repairs, Maintenance, Technical Inspections) linked to a specific vehicle.
* **Service Reminders:** Automatically generate warnings for upcoming technical inspections or required oil changes based on stored mileage and service dates.
* **Persistent Storage:** Save the entire system state (all clients, cars, and histories) to custom-formatted `.txt` files and load them back at runtime.
* **Text-Based UI (TUI):** A user-friendly, menu-driven console interface for all operations, with clear ASCII-art branding.

## 🛠️ Technical Implementation & OOP Concepts

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

## 🏛️ Class Diagram (UML)

The following UML diagram illustrates the high-level architecture and relationships between the core classes.

*(User: Illeszd be ide a `Terv.pdf` vagy `NHF4 - Dokumentáció.pdf` (6. oldal) fájlban található UML diagram képét. Egy jó link pl.: `![UML Class Diagram](https://i.imgur.com/your-uml-image.png)`)*

## 💾 File-Based Persistence

The system saves and loads data using two custom `.txt` file formats:

* **Client File (`*_ufl.txt`):** Stores client data.
    * *Format:* `nev-telefonszam-email`
* **Auto File (`*_auo.txt`):** Stores vehicle and service data.
    * *Format:* `rendszam-marka-tipus-km_ora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_nev`
    * The `szervizmuveletek` field is a complex, semi-colon-delimited list of polymorphic service records.

*(User: A build/használat részhez add hozzá a saját fordítási lépéseidet, pl. CMake, g++, stb.)*
