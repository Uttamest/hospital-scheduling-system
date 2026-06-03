#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"

#include <string>

using namespace std;

class Doctor : public Person
{
private:
    string specialization;

public:
    Doctor(int id, const string &name, const string &phone, const string &specialization);

    const string &getSpecialization() const;
    void setSpecialization(const string &specialization);

    string role() const;
    void printSummary(ostream &out) const;
    string serialize() const;

    static Doctor deserialize(const string &line);
};

#endif
