#include "Person.h"

#include "HospitalException.h"
#include "TextUtils.h"

using namespace std;

Person::Person(int id, const string &name, const string &phone)
    : id(id)
{
    if (id <= 0)
    {
        throw ValidationException("Person id must be positive.");
    }
    setName(name);
    setPhone(phone);
}

int Person::getId() const
{
    return id;
}

const string &Person::getName() const
{
    return name;
}

const string &Person::getPhone() const
{
    return phone;
}

void Person::setName(const string &newName)
{
    text::requireField(newName, "Name");
    name = text::trim(newName);
}

void Person::setPhone(const string &newPhone)
{
    text::requireField(newPhone, "Phone");
    phone = text::trim(newPhone);
}
