# Housing Office Management System

A robust C++20 application designed to streamline the management of residential buildings, tenant tracking, and utility payment calculations. Built with a strong emphasis on software architecture, performance, and extensibility.

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-green.svg)
![Tests](https://img.shields.io/badge/Tests-GoogleTest-orange.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

## 📖 Overview

The **Housing Office Management System** is a comprehensive desktop application that automates the administrative workflows of a housing office. It manages the complex relationships between houses, apartments, and different categories of tenants (ordinary and preferential). 

The system calculates utility payments, applies dynamic discounts, and provides a fully interactive interface for data manipulation. It is designed from the ground up to handle large datasets efficiently using multithreading and a custom-built template container.

## 📋 Project Specification

### General Description
Develop an application designed to manage the accounting of tenants (renters) of a residential building and utility payments. Tenants of a building (renters of a specific apartment) are divided into ordinary and preferential renters (those entitled to housing payment benefits). Information about tenants is stored in a tenant descriptor.

### Data Models

**Tenant Descriptor (Base Class):**
- Full name and initials
- Year of birth
- Gender
- Status (working / dependent)

**Preferential Tenant Descriptor (Derived Class):**
- Full name and initials
- Year of birth
- Gender
- Status (working / dependent)
- Benefit type (string)
- Benefit amount (in %)

**Apartment Table (Template Class — Ordered Table):**
Each element contains:
- Apartment number
- Apartment area
- Number of tenants
- Dynamic array of pointers to tenant descriptors

*Requirements:*
- Table elements are ordered by apartment numbers.
- The first element in the array must be the primary tenant (renter).
- For preferential tenants, payments are reduced by the benefit amount.

**House Descriptor:**
- Street name
- Building number and case
- Total payments per 1 sq.m.
- Total payments per one tenant
- Table of apartment descriptors

### Required Operations

**For the House Descriptor:**
- Insert a new element (maintaining order)
- Find an element by apartment number
- Delete an element by apartment number
- Display the table contents

**For an Apartment:**
- Print apartment information
- Get the number of tenants and area
- Modify the number of tenants and descriptors
- Get the count of ordinary/preferential tenants
- Get the tenant category

**For a Tenant:**
- Print tenant information
- Get the tenant category

**For a Preferential Tenant:**
- Get/modify the benefit amount

**For the Application:**
- Check-in to an apartment
- Correct apartment data
- Check-out from an apartment
- Calculate utility payments for an apartment
- Calculate house benefits (difference between max and real payment)

## ✨ Key Features

- **Hierarchical Data Model**: A rich class hierarchy representing `House`, `Apartment`, `Tenant`, and `PreferentialTenant` entities.
- **Custom Template Container**: A bespoke, high-performance template container built from scratch (no STL containers used for core logic). It features full iterator support (random access / bidirectional) and strictly adheres to C++ memory safety rules.
- **Modern C++20 Architecture**: Extensive use of move semantics, smart pointers, operator overloading, exception handling, and concepts for type safety.
- **MVC Design Pattern**: Strict separation of concerns using the Model-View-Controller paradigm, ensuring maintainability and testability.
- **Multithreading**: Parallel execution of utility payment calculations and discount aggregation using `std::thread`, `std::mutex`, and atomic operations to prevent race conditions.
- **Dynamic Plugin System**: Extensible architecture that allows dynamically loading `.so`/`.dll` libraries at runtime to add new tenant types or calculation strategies without recompiling the core application.
- **Comprehensive Test Suite**: High unit test coverage (exceeding 50%) utilizing GoogleTest, covering all critical business logic.
- **Interactive CLI**: A user-friendly, menu-driven interactive dialog interface for seamless navigation and data management.

## 🏗️ Architecture and Project Structure

The project follows a strict Model-View-Controller (MVC) architecture, divided into logical components to ensure high cohesion and low coupling. 

```text
.
├── app/
│   └── main.cpp                 # Application entry point and DI setup
├── include/                     # Public header files
│   ├── controller/              # Controller layer (business logic routing)
│   ├── model/                   # Model layer
│   │   ├── entity/              # Domain entities (Tenant, Apartment, House)
│   │   ├── repository/          # Data persistence and custom containers
│   │   ├── service/             # Domain services (Payment calculation, discounts)
│   │   └── table/               # Custom template container implementation
│   └── view/                    # View layer (UI abstraction)
├── src/                         # Implementation files (mirrors include/)
│   ├── controller/
│   ├── model/
│   └── view/
├── tests/                       # Unit tests (GoogleTest)
├── CMakeLists.txt               # Build configuration
└── .gitkeep
```

## 🚀 Technical Highlights

### Custom Template Container
Instead of relying on standard library containers, this project implements a custom dynamic array template class. 
- **Iterators**: Implements custom iterators that comply with the *Random Access Iterator* category (supporting `operator++`, `operator--`, `operator+`, `operator-`, `operator[]`), allowing seamless integration with standard algorithms.
- **Memory Management**: Implements perfect forwarding and move semantics to minimize deep copies during insertion and resizing.
- **Exception Safety**: Strong exception guarantee during element insertion and capacity changes.

### Multithreading & Performance
The payment calculation algorithm processes thousands of apartments simultaneously. 
- **Parallelism**: Utilizes `std::async` and thread pools to distribute the calculation load.
- **Synchronization**: Implements `std::mutex` and `std::shared_mutex` for read/write locks on shared data structures, ensuring thread safety without significant performance bottlenecks.
- **Race Condition Prevention**: ThreadSanitizer is used during development to guarantee no data races exist.

### Extensibility (Dynamic Loading)
The system supports a plugin architecture. Any dynamic library placed in the `plugins/` directory is automatically scanned, loaded, and registered at runtime, allowing new types of preferential tenants to be added dynamically.

## 🛠️ Getting Started

### Prerequisites
- C++20 compatible compiler (GCC 11+, Clang 14+, MSVC 19.30+)
- CMake 3.15 or higher
- GoogleTest (automatically fetched via CMake FetchContent)
- Doxygen (for documentation generation)

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/your-username/housing-office-management.git
cd housing-office-management

# Create build directory
mkdir build && cd build

# Configure CMake
cmake ..

# Build the project
cmake --build . --config Release

# Run the application
./bin/housing_office
```

### Running Tests
The project uses GoogleTest for unit testing. To run the test suite:
```bash
cd build
ctest --output-on-failure
# Or run the test binary directly
./tests/housing_office_tests
```

## 📊 UML Class Diagram

The architecture and class relationships are documented using UML. 

![Housing Office UML Class Diagram](docs/images/uml_diagram.png)

*(You can find the source `.puml` or `.modelio` files in the `docs/uml/` directory).*

## 📚 Documentation
The project uses Doxygen for code documentation. To generate the HTML documentation:
```bash
doxygen Doxyfile
# Open docs/html/index.html in your browser
```

## 🛡️ Code Quality & Static Analysis
The codebase adheres to the highest quality standards. 
- **Static Analysis**: Checked with Clang-Tidy and SonarQube. All warnings are treated as errors (`-Wall -Wextra -Werror`).
- **Dynamic Analysis**: Analyzed using Valgrind (Memcheck) and AddressSanitizer (ASan) to ensure zero memory leaks.
- **SOLID Principles**: Strictly follows SOLID principles, ensuring that classes have a single responsibility and are open for extension but closed for modification.

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
