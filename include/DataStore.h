#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "Appointment.h"
#include "Doctor.h"
#include "Patient.h"

#include <string>
#include <vector>

using namespace std;

class DataStore {
private:
    string doctorsFile;
    string patientsFile;
    string appointmentsFile;

    void loadDoctors(vector<Doctor>& doctors) const;
    void loadPatients(vector<Patient>& patients) const;
    void loadAppointments(vector<Appointment>& appointments) const;

public:
    explicit DataStore(const string& dataDirectory = "data");

    void load(vector<Doctor>& doctors,
              vector<Patient>& patients,
              vector<Appointment>& appointments) const;

    void save(const vector<Doctor>& doctors,
              const vector<Patient>& patients,
              const vector<Appointment>& appointments) const;
};

#endif
