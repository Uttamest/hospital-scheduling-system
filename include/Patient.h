#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
using namespace std;

class Patient : public Person {
  private:
    int age;
    string medicalNote;

public:
    Patient(int id, const string &name, const string &phone, int age, const string &medicalNote);

    int getAge() const;
    const string &getMedicalNote() const;

    void setAge(int age);
    void setMedicalNote(const string &medicalNote);

    string role() const;
    void printSummary(ostream &out) const;
    string serialize() const;

    static Patient deserialize(const string &line);
};
#endif
