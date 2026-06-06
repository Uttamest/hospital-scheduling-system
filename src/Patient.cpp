#include "Patient.h"
#include "HospitalException.h"
#include "TextUtils.h"

#include <ostream>
#include <sstream>
using namespace std;

Patient::Patient(int id, const string &name, const string &phone, int age, const string &medicalNote) : Person(id, name, phone) {
    setAge(age);
    setMedicalNote(medicalNote);
}

int Patient::getAge() const {
    return age;
}

const string &Patient::getMedicalNote() const {
    return medicalNote;
}

void Patient::setAge(int newAge) {
    if ((newAge < 0) || (newAge > 130)) {
        throw ValidationException("Age must be between 0 and 130.");
    }
    age = newAge;
}

void Patient::setMedicalNote(const string &newMedicalNote) {
    text::requireNoDelimiter(newMedicalNote, "Medical note");
    const string trimmed = text::trim(newMedicalNote);
    medicalNote = trimmed.empty() ? "None" : trimmed;
}

string Patient::role() const {
    return "Patient";
}

void Patient::printSummary(ostream &out) const {
    out << "[" << role() << " #" << getId() << "] "
        << getName() << " | Age: " << age
        << " | Phone: " << getPhone()
        << " | Note: " << medicalNote << '\n';
}

string Patient::serialize() const {
    ostringstream out;
    out << getId() << '|'
        << getName() << '|'
        << getPhone() << '|'
        << age << '|'
        << medicalNote;
    return out.str();
}

Patient Patient::deserialize(const string &line) {
    const vector<string> parts = text::split(line, '|');
    if (parts.size() != 5)
    {
        throw ValidationException("Patient record must have 5 fields.");
    }

    return Patient(text::toInt(parts[0], "Patient id"),
                   parts[1],
                   parts[2],
                   text::toInt(parts[3], "Age"),
                   parts[4]);
}
