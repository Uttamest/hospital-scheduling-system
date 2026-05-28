#include "<Scheduler.h>"

#include "<HospitalException.h>"
#include "Person.h"

#include <algorithm>
#include <ostream>
#include <sstream>

using namespace std;

Scheduler::Scheduler(const DataStore& dataStore)
    : dataStore(dataStore) {}

void Scheduler::load() {
    dataStore.load(doctors, patients, appointments);
}

void Scheduler::save() const {
    dataStore.save(doctors, patients, appointments);
}

bool Scheduler::hasDoctors() const {
    return !doctors.empty();
}

bool Scheduler::hasPatients() const {
    return !patients.empty();
}

bool Scheduler::hasAppointments() const {
    return !appointments.empty();
}

int Scheduler::addDoctor(const string& name, const string& phone, const string& specialization) {
    const int id = nextDoctorId();
    doctors.push_back(Doctor(id, name, phone, specialization));
    return id;
}

int Scheduler::addPatient(const string& name, const string& phone, int age, const string& medicalNote) {
    const int id = nextPatientId();
    patients.push_back(Patient(id, name, phone, age, medicalNote));
    return id;
}

int Scheduler::createAppointment(int doctorId,
                                 int patientId,
                                 const string& date,
                                 const string& time,
                                 const string& reason) {
    if (findDoctorById(doctorId) == nullptr) {
        throw NotFoundException("Doctor #" + to_string(doctorId) + " was not found.");
    }
    if (findPatientById(patientId) == nullptr) {
        throw NotFoundException("Patient #" + to_string(patientId) + " was not found.");
    }

    Appointment candidate(nextAppointmentId(), doctorId, patientId, date, time, reason);
    // Prevent double-booking the same doctor or patient at the same date and time.
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        if (!it->isActive() || it->dateTimeKey() != candidate.dateTimeKey()) {
            continue;
        }

        if (it->getDoctorId() == doctorId) {
            throw ScheduleConflictException("The doctor already has an appointment at that date and time.");
        }
        if (it->getPatientId() == patientId) {
            throw ScheduleConflictException("The patient already has an appointment at that date and time.");
        }
    }

    const int id = candidate.getId();
    appointments.push_back(candidate);
    return id;
}

void Scheduler::cancelAppointment(int appointmentId) {
    Appointment* appointment = findAppointmentById(appointmentId);
    if (appointment == nullptr) {
        throw NotFoundException("Appointment #" + to_string(appointmentId) + " was not found.");
    }

    appointment->cancel();
}

void Scheduler::listDoctors(ostream& out) const {
    out << "\nDoctors\n";
    out << "-------\n";
    if (doctors.empty()) {
        out << "No doctors have been registered yet.\n";
        return;
    }

    for (vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
        it->printSummary(out);
    }
}

void Scheduler::listPatients(ostream& out) const {
    out << "\nPatients\n";
    out << "--------\n";
    if (patients.empty()) {
        out << "No patients have been registered yet.\n";
        return;
    }

    for (vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        it->printSummary(out);
    }
}

void Scheduler::listAppointments(ostream& out) const {
    out << "\nAppointments\n";
    out << "------------\n";
    if (appointments.empty()) {
        out << "No appointments have been created yet.\n";
        return;
    }

    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        printAppointment(out, *it);
    }
}

void Scheduler::listDoctorSchedule(int doctorId, ostream& out) const {
    const Doctor* doctor = findDoctorById(doctorId);
    if (doctor == nullptr) {
        throw NotFoundException("Doctor #" + to_string(doctorId) + " was not found.");
    }

    out << "\nSchedule for Dr. " << doctor->getName() << "\n";
    out << "-------------------------\n";
    bool found = false;
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->getDoctorId() == doctorId) {
            printAppointment(out, *it);
            found = true;
        }
    }
    if (!found) {
        out << "No appointments found for this doctor.\n";
    }
}

void Scheduler::listPatientSchedule(int patientId, ostream& out) const {
    const Patient* patient = findPatientById(patientId);
    if (patient == nullptr) {
        throw NotFoundException("Patient #" + to_string(patientId) + " was not found.");
    }

    out << "\nSchedule for " << patient->getName() << "\n";
    out << "-------------------------\n";
    bool found = false;
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->getPatientId() == patientId) {
            printAppointment(out, *it);
            found = true;
        }
    }
    if (!found) {
        out << "No appointments found for this patient.\n";
    }
}

void Scheduler::listAllPeoplePolymorphic(ostream& out) const {
    out << "\nHospital People\n";
    out << "---------------\n";

    // Runtime polymorphism: derived objects are used through base class pointers.
    vector<const Person*> people;
    for (vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
        people.push_back(&(*it));
    }
    for (vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        people.push_back(&(*it));
    }

    if (people.empty()) {
        out << "No people have been registered yet.\n";
        return;
    }

    for (vector<const Person*>::const_iterator it = people.begin(); it != people.end(); ++it) {
        (*it)->printSummary(out);
    }
}

int Scheduler::nextDoctorId() const {
    int maxId = 0;
    for (vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
        maxId = max(maxId, it->getId());
    }
    return maxId + 1;
}

int Scheduler::nextPatientId() const {
    int maxId = 0;
    for (vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        maxId = max(maxId, it->getId());
    }
    return maxId + 1;
}

int Scheduler::nextAppointmentId() const {
    int maxId = 0;
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        maxId = max(maxId, it->getId());
    }
    return maxId + 1;
}

const Doctor* Scheduler::findDoctorById(int id) const {
    for (vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return nullptr;
}

const Patient* Scheduler::findPatientById(int id) const {
    for (vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return nullptr;
}

Appointment* Scheduler::findAppointmentById(int id) {
    for (vector<Appointment>::iterator it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return nullptr;
}

const Appointment* Scheduler::findAppointmentById(int id) const {
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return nullptr;
}

string Scheduler::doctorNameOrUnknown(int id) const {
    const Doctor* doctor = findDoctorById(id);
    if (doctor == nullptr) {
        return "Unknown doctor #" + to_string(id);
    }
    return doctor->getName();
}

string Scheduler::patientNameOrUnknown(int id) const {
    const Patient* patient = findPatientById(id);
    if (patient == nullptr) {
        return "Unknown patient #" + to_string(id);
    }
    return patient->getName();
}

void Scheduler::printAppointment(ostream& out, const Appointment& appointment) const {
    appointment.printSummary(out,
                             doctorNameOrUnknown(appointment.getDoctorId()),
                             patientNameOrUnknown(appointment.getPatientId()));
}
