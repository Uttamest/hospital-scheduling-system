#include "DataStore.h"

#include "HospitalException.h"
#include "TextUtils.h"

#include <fstream>
#include <sstream>

using namespace std;

DataStore::DataStore(const string& dataDirectory)
    : doctorsFile(dataDirectory + "/doctors.txt"),
      patientsFile(dataDirectory + "/patients.txt"),
      appointmentsFile(dataDirectory + "/appointments.txt") {}

void DataStore::load(vector<Doctor>& doctors,
                     vector<Patient>& patients,
                     vector<Appointment>& appointments) const {
    // Reloading starts from a clean state so duplicate records are not kept in memory.
    doctors.clear();
    patients.clear();
    appointments.clear();

    loadDoctors(doctors);
    loadPatients(patients);
    loadAppointments(appointments);
}

void DataStore::save(const vector<Doctor>& doctors,
                     const vector<Patient>& patients,
                     const vector<Appointment>& appointments) const {
    ofstream doctorsOut(doctorsFile.c_str());
    if (!doctorsOut) {
        throw HospitalException("Could not write " + doctorsFile + ".");
    }
    for (vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
        doctorsOut << it->serialize() << '\n';
    }

    ofstream patientsOut(patientsFile.c_str());
    if (!patientsOut) {
        throw HospitalException("Could not write " + patientsFile + ".");
    }
    for (vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        patientsOut << it->serialize() << '\n';
    }

    ofstream appointmentsOut(appointmentsFile.c_str());
    if (!appointmentsOut) {
        throw HospitalException("Could not write " + appointmentsFile + ".");
    }
    for (vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
        appointmentsOut << it->serialize() << '\n';
    }
}

void DataStore::loadDoctors(vector<Doctor>& doctors) const {
    ifstream input(doctorsFile.c_str());
    if (!input) {
        // Missing data files are allowed on the first run of the program.
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        if (text::trim(line).empty()) {
            continue;
        }

        try {
            doctors.push_back(Doctor::deserialize(line));
        } catch (const HospitalException& error) {
            // Include the line number so a damaged data file is easy to fix.
            ostringstream message;
            message << "Could not load " << doctorsFile << " line " << lineNumber << ": " << error.what();
            throw HospitalException(message.str());
        }
    }
}

void DataStore::loadPatients(vector<Patient>& patients) const {
    ifstream input(patientsFile.c_str());
    if (!input) {
        // Missing data files are allowed on the first run of the program.
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        if (text::trim(line).empty()) {
            continue;
        }

        try {
            patients.push_back(Patient::deserialize(line));
        } catch (const HospitalException& error) {
            // Include the line number so a damaged data file is easy to fix.
            ostringstream message;
            message << "Could not load " << patientsFile << " line " << lineNumber << ": " << error.what();
            throw HospitalException(message.str());
        }
    }
}

void DataStore::loadAppointments(vector<Appointment>& appointments) const {
    ifstream input(appointmentsFile.c_str());
    if (!input) {
        // Missing data files are allowed on the first run of the program.
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        if (text::trim(line).empty()) {
            continue;
        }

        try {
            appointments.push_back(Appointment::deserialize(line));
        } catch (const HospitalException& error) {
            // Include the line number so a damaged data file is easy to fix.
            ostringstream message;
            message << "Could not load " << appointmentsFile << " line " << lineNumber << ": " << error.what();
            throw HospitalException(message.str());
        }
    }
}
