#ifndef PERSON_H
#define PERSON_H

#include <iosfwd>
#include <string>
using namespace std;

class Person {
private:
    int id;
    string name, phone;

public:
    Person(int id, const string &name, const string &phone);
    virtual ~Person() {}

    int getId() const;
    const string &getName() const;
    const string &getPhone() const;

    void setName(const string &name);
    void setPhone(const string &phone);

    virtual string role() const = 0;
    virtual void printSummary(ostream &out) const = 0;
    virtual string serialize() const = 0;
};
#endif
