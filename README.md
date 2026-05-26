<div align="center">

# 🏥 Hospital Scheduling System

### OOP II Final Project — CLI-Based Hospital Appointment Management System in C++

<img src="https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/OOP-Final%20Project-success?style=for-the-badge" />
<img src="https://img.shields.io/badge/Platform-CLI-orange?style=for-the-badge" />
<img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge" />

</div>

---

# 📖 Project Overview

The **Hospital Scheduling System** is a command-line based hospital appointment management system developed in **C++** using core **Object-Oriented Programming (OOP)** principles.

The system allows users to:

- Manage doctors and patients
- Create and cancel appointments
- Prevent schedule conflicts
- View schedules by doctor or patient
- Save and reload records using text files
- Demonstrate advanced OOP concepts in a real-world application

---

# ✨ Features

<ul>
<li>➕ Add and manage doctors</li>
<li>➕ Add and manage patients</li>
<li>📅 Create appointments</li>
<li>❌ Cancel appointments</li>
<li>📋 View all appointments</li>
<li>👨‍⚕️ View doctor schedules</li>
<li>🧑‍🤝‍🧑 View patient schedules</li>
<li>💾 Save and reload records from files</li>
<li>🧠 Runtime polymorphism demonstration</li>
<li>⚠️ Custom exception handling</li>
</ul>

---

# 🧠 OOP Concepts Used

| Concept | Implementation |
|---|---|
| Encapsulation | Private data members with public getters/setters |
| Inheritance | `Doctor` and `Patient` inherit from `Person` |
| Abstraction | Abstract `Person` base class |
| Runtime Polymorphism | Virtual `printSummary()` function |
| Composition | `Scheduler` owns system components |
| Exception Handling | Custom hospital-related exceptions |
| File I/O | Persistent text file storage |

---

# 👥 Team Members And Responsibilities

<table>
<tr>
<th>No.</th>
<th>Name</th>
<th>Role</th>
<th>Main Responsibility</th>
</tr>

<tr>
<td>1</td>
<td><b>SHRESTHA UTTAM</b></td>
<td>Team Leader</td>
<td>
Project leadership, GitHub setup, CLI menus, integration, input handling, build/run setup, and final quality check
</td>
</tr>

<tr>
<td>2</td>
<td><b>RAI SURAJ</b></td>
<td>Models/OOP Classes</td>
<td>
OOP model classes, inheritance, abstraction, polymorphism support, and appointment model structure
</td>
</tr>

<tr>
<td>3</td>
<td><b>KHADKA SANTOSH</b></td>
<td>Scheduling Logic</td>
<td>
Appointment scheduling, cancellation logic, conflict checking, and schedule viewing
</td>
</tr>

<tr>
<td>4</td>
<td><b>KHAND THAKURI SHRADDHA</b></td>
<td>File I/O, UML, Testing</td>
<td>
File storage system, sample data files, UML documentation, README support, and testing
</td>
</tr>

</table>

---

# 👑 Team Leader Contribution

### SHRESTHA UTTAM

Responsible for integrating all modules into one fully working system.

### Main Contributions

- GitHub repository management
- Main CLI menu implementation
- Input validation and interaction
- VS Code and PowerShell build setup
- Final project integration
- Build testing and debugging
- Final documentation review
- Pull request review and merging

---

# 📂 Project Structure

```text
.
|-- .gitignore
|-- .vscode/
|   |-- settings.json
|   `-- tasks.json
|-- README.md
|-- build.ps1
|-- data/
|   |-- appointments.txt
|   |-- doctors.txt
|   `-- patients.txt
|-- docs/
|   |-- uml.md
|   `-- uml.mmd
|-- include/
|   |-- Appointment.h
|   |-- DataStore.h
|   |-- DateTime.h
|   |-- Doctor.h
|   |-- HospitalException.h
|   |-- InputUtils.h
|   |-- Patient.h
|   |-- Person.h
|   |-- Scheduler.h
|   `-- TextUtils.h
`-- src/
    |-- Appointment.cpp
    |-- DataStore.cpp
    |-- DateTime.cpp
    |-- Doctor.cpp
    |-- InputUtils.cpp
    |-- main.cpp
    |-- Patient.cpp
    |-- Person.cpp
    |-- Scheduler.cpp
    `-- TextUtils.cpp
```

---

# ⚙️ Build And Run

## Using PowerShell

```powershell
./build.ps1
```

---

# 📁 Files To Upload

## Upload These

```text
README.md
build.ps1
.gitignore
.vscode/
data/
docs/
include/
src/
```

---

## Do NOT Upload

```text
build/
*.exe
*.o
*.obj
```

The `.gitignore` file already excludes generated files.

---

# 🌿 Suggested Git Branches

| Team Member | Branch |
|---|---|
| SHRESTHA UTTAM | `uttam-team-leader-cli-input` |
| RAI SURAJ | `suraj-oop-models` |
| KHADKA SANTOSH | `santosh-scheduling-logic` |
| KHAND THAKURI SHRADDHA | `shraddha-fileio-docs-testing` |

---

# 💬 Suggested Commit Messages

## Team Leader

```text
Set up project structure and build files
Add CLI menu and input handling
Integrate team modules into final program
Finalize README and submission checklist
```

## Models/OOP

```text
Add Person Doctor and Patient model classes
Add Appointment model and validation helpers
Document inheritance and abstraction in model classes
```

## Scheduling Logic

```text
Add scheduler class and appointment creation logic
Add appointment conflict checking
Add doctor and patient schedule views
```

## File I/O And Testing

```text
Add file input output support
Add sample doctor patient and appointment data
Add UML class diagram and testing notes
```

---

# 📚 Technologies Used

<ul>
<li>C++17</li>
<li>Object-Oriented Programming</li>
<li>File Handling</li>
<li>PowerShell Build Script</li>
<li>VS Code</li>
<li>Git & GitHub</li>
</ul>

---

# 🏁 Final Notes

This project was developed as part of the **OOP II Final Project** and demonstrates practical usage of:

- OOP design principles
- File handling
- Scheduling systems
- CLI application development
- Team collaboration using GitHub

---

<div align="center">

## ⭐ If you like this project, give it a star on GitHub!

</div>
