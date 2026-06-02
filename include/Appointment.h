#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iosfwd>
#include <string>

using namespace std;

// Appointment status is stored in the data file as text.
enum class AppointmentStatus {
  Scheduled, Cancelled
};

string statusToString(AppointmentStatus status);
AppointmentStatus statusFromString(const string &status);

class Appointment {
private:
    int id, doctorId , patientId;
    string date, time, reason;
    AppointmentStatus status;

public:
Appointment(int id,int doctorId,int patientId,const string &date,const string &time,const string &reason,AppointmentStatus status =AppointmentStatus::Scheduled);

    int getId() const;
    int getDoctorId() const;
    int getPatientId() const;
    const string &getDate() const;
    const string &getTime() const;
    const string &getReason() const;
    AppointmentStatus getStatus() const;

    bool isActive() const;
    string dateTimeKey() const;
    void cancel();

    void printSummary(ostream &out, const string &doctorName, const string &patientName) const;
    string serialize() const;

    static Appointment deserialize(const string& line);
};
#endif