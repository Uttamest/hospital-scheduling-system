#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Appointment.h"
#include "DataStore.h"
#include "Doctor.h"
#include "Patient.h"

#include <iosfwd>
#include <vector>

using namespace std;

class Scheduler {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
    DataStore dataStore;

    int nextDoctorId() const;
    int nextPatientId() const;
    int nextAppointmentId() const;

    const Doctor* findDoctorById(int id) const;
    const Patient* findPatientById(int id) const;
    Appointment* findAppointmentById(int id);
    const Appointment* findAppointmentById(int id) const;

    string doctorNameOrUnknown(int id) const;
    string patientNameOrUnknown(int id) const;
    void printAppointment(ostream& out, const Appointment& appointment) const;

public:
    explicit Scheduler(const DataStore& dataStore = DataStore());

    void load();
    void save() const;

    bool hasDoctors() const;
    bool hasPatients() const;
    bool hasAppointments() const;

    int addDoctor(const string& name, const string& phone, const string& specialization);
    int addPatient(const string& name, const string& phone, int age, const string& medicalNote);
    int createAppointment(int doctorId,
                          int patientId,
                          const string& date,
                          const string& time,
                          const string& reason);
    void cancelAppointment(int appointmentId);

    void listDoctors(ostream& out) const;
    void listPatients(ostream& out) const;
    void listAppointments(ostream& out) const;
    void listDoctorSchedule(int doctorId, ostream& out) const;
    void listPatientSchedule(int patientId, ostream& out) const;
    void listAllPeoplePolymorphic(ostream& out) const;
};

#endif
