#include "Doctor.h"
#include "HospitalException.h"
#include "TextUtils.h"

#include <ostream>
#include <sstream>
using namespace std;

Doctor::Doctor(int id, const string &name, const string &phone, const string &specialization) : Person(id, name, phone)
{
    setSpecialization(specialization);
}

const string &Doctor::getSpecialization() const
{
    return specialization;
}

void Doctor::setSpecialization(const string &newSpecialization)
{
    text::requireField(newSpecialization, "Specialization");
    specialization = text::trim(newSpecialization);
}

string Doctor::role() const
{
    return "Doctor";
}

void Doctor::printSummary(ostream &out) const
{
    out << "[" << role() << " #" << getId() << "] "
        << getName() << " | " << getSpecialization()
        << " | Phone: " << getPhone() << '\n';
}

string Doctor::serialize() const
{
    ostringstream out;
    out << getId() << '|'
        << getName() << '|'
        << getPhone() << '|'
        << specialization;
    return out.str();
}

Doctor Doctor::deserialize(const string &line)
{
    const vector<string> parts = text::split(line, '|');
    if (parts.size() != 4)
    {
        throw ValidationException("Doctor record must have 4 fields.");
    }

    return Doctor(text::toInt(parts[0], "Doctor id"), parts[1], parts[2], parts[3]);
}
