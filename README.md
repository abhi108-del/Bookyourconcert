# Concert Ticket Booking System

## 👥 Team Members

| Name | Roll No | Email |
|------|---------|-------|
| ABHIRAM | IMT2023108 | Mopuri.Abhiram@iiitb.ac.in |
| RAJDEEP | IMT2023592 | Alapati.Rajdeep@iiitb.ac.in |
| NANDA | IMT2023583 | Nanda.Mitra@iiitb.ac.in |
| REVANTH | IMT2023118 | Revanth.Puppala@iiitb.ac.in |
| ADITYA REDDY | IMT2023114 | Aditya.Chintala@iiitb.ac.in |
| PARTHIV | IMT2023559 | Kotyada.Parthiv@iiitb.ac.in |

## 📝 Project Overview

A terminal-based concert ticket booking system that enables user registration, login, seat selection, booking, and ticket cancellation. Designed for efficiency, using C++ for core functionality and Java for user interaction.

## 🎯 Objectives

- Develop core functions in C++ for user registration, booking, and venue management
- Use Java to call C++ functions, managing user interface and terminal interactions
- Allow admins to add and manage venues

## 🖥️ System Architecture

### Programming Languages
- **Java**: Main function and user interaction, handles terminal-based interface
- **C++**: Backend logic, manages core operations like data processing, ticket booking
- **JNI (Java Native Interface)**: Bridges communication between Java and C++

## ✨ Functional Requirements

- User Registration and Login
- City Selection
- Genre and Date Selection
- Venue and Showtime Selection
- Seat Availability Matrix
- Ticket Booking and Cancellation
- Admin Venue Management

## 🛠️ Non-functional Requirements

- Performance: Fast response time
- Usability: Simple, terminal-based UI
- Security: User authentication, admin access control, password encryption

## 📦 Development Setup

- Install prerequisites
- 1. Install C++ and Java
- 2. Set up JNI for C++ and Java interaction


## 🔧 Project Setup and Installation

### Prerequisites
- Java Development Kit (JDK) 8 or higher
- C++ Compiler (g++)
- Git

### Step-by-Step Installation

1. **Clone the Repository**
- git clone <repository-url>
- cd concert-ticket-booking-system

# Install dependencies and configure environment
# Run the application
- java -Djava.library.path=path_to_jni mainApp

#### Set Up Java Environment
# Verify Java installation
- java -version
- javac -version

#### Generate JNI Header File
# Compile Java file
- javac BookYourConcert.java

# Generate JNI header
- javac -h . BookYourConcert.java
#### Compile C++ Code
#### For Linux/macOS:
- g++ -shared -fpic -o libBookYourConcertLib.so draft.cpp \-I"$JAVA_HOME/include" \-I"$JAVA_HOME/include/linux"

#### For Windows:
- g++ -shared -o BookYourConcert.dll draft.cpp \-I"%JAVA_HOME%/include" \-I"%JAVA_HOME%/include/win32"
#### Run the Application
# Set library path and run
- java -Djava.library.path=. BookYourConcert
## 🔄 Workflow

- **Backend (C++)**: Manages core functions with concurrency controls
- **Frontend (Java)**: Captures user input, handles UI, calls C++ functions
- **Middleware (JNI)**: Bridges Java and C++ communication

## 🧪 Testing & Logging

- Unit tests for C++ and Java modules
- Logs errors and key actions for each session

## 📦 Data Storage

### Customer Management
- `Customers.txt`: Stores user credentials
- Tracks booking history
- Supports user authentication

### Concert Information
- `Concerts.txt`: Maintains list of available concerts
- Includes concert details and metadata

### Venue Management
- `Venues.txt`: Contains comprehensive venue information
- Supports admin venue additions and modifications

## 🔒 Security Features

- User authentication system
- Password encryption
- Admin access control
- Secure data management

## 💻 Technical Specifications

### Input Methods
- Terminal-based interface
- Interactive menu-driven navigation
- Real-time user input processing

### Performance Characteristics
- Fast response times
- Efficient seat allocation

## 🚧 Limitations

- No online payment integration
- No graphical user interface
- Terminal-only interaction

