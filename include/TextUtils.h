#ifndef HOSPITAL_EXCEPTION_H
#define HOSPITAL_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

// Custom exception hierarchy for project-specific validation and scheduling errors.
class HospitalException : public runtime_error {
public:
    explicit HospitalException(const string &message)
        : runtime_error(message) { }
};

class ValidationException : public HospitalException {
public:
    explicit ValidationException(const string &message)
        : HospitalException(message) { }
};

class NotFoundException : public HospitalException {
public:
    explicit NotFoundException(const string &message)
        : HospitalException(message) { }
};

class ScheduleConflictException : public HospitalException {
public:
    explicit ScheduleConflictException(const string &message)
        : HospitalException(message) { }
};
#endif