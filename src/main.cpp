#include "HospitalException.h"
#include "InputUtils.h"
#include "Scheduler.h"

#include <iostream>

using namespace std;

namespace
{

    void addDoctorFlow(Scheduler &scheduler)
    {
        cout << "\nAdd Doctor\n";
        cout << "----------\n";
        const string name = input::readRequiredLine("Name: ");
        const string phone = input::readRequiredLine("Phone: ");
        const string specialization = input::readRequiredLine("Specialization: ");

        const int id = scheduler.addDoctor(name, phone, specialization);
        scheduler.save();
        cout << "Doctor created with id #" << id << ".\n";
    }

    void addPatientFlow(Scheduler &scheduler)
    {
        cout << "\nAdd Patient\n";
        cout << "-----------\n";
        const string name = input::readRequiredLine("Name: ");
        const string phone = input::readRequiredLine("Phone: ");
        const int age = input::readInt("Age: ", 0, 130);
        const string medicalNote = input::readLine("Medical note (optional): ");

        const int id = scheduler.addPatient(name, phone, age, medicalNote);
        scheduler.save();
        cout << "Patient created with id #" << id << ".\n";
    }

    void createAppointmentFlow(Scheduler &scheduler)
    {
        if (!scheduler.hasDoctors() || !scheduler.hasPatients())
        {
            cout << "\nCreate at least one doctor and one patient before scheduling appointments.\n";
            return;
        }

        scheduler.listDoctors(cout);
        scheduler.listPatients(cout);

        cout << "\nCreate Appointment\n";
        cout << "------------------\n";
        const int doctorId = input::readInt("Doctor id: ", 1, 100000000);
        const int patientId = input::readInt("Patient id: ", 1, 100000000);
        const string date = input::readDate("Date (YYYY-MM-DD): ");
        const string time = input::readTime("Time (HH:MM): ");
        const string reason = input::readRequiredLine("Reason: ");

        const int id = scheduler.createAppointment(doctorId, patientId, date, time, reason);
        scheduler.save();
        cout << "Appointment created with id #" << id << ".\n";
    }

    void cancelAppointmentFlow(Scheduler &scheduler)
    {
        if (!scheduler.hasAppointments())
        {
            cout << "\nThere are no appointments to cancel.\n";
            return;
        }

        scheduler.listAppointments(cout);
        const int appointmentId = input::readInt("\nAppointment id to cancel: ", 1, 100000000);
        scheduler.cancelAppointment(appointmentId);
        scheduler.save();
        cout << "Appointment #" << appointmentId << " was cancelled.\n";
    }

    void doctorScheduleFlow(const Scheduler &scheduler)
    {
        scheduler.listDoctors(cout);
        const int doctorId = input::readInt("\nDoctor id: ", 1, 100000000);
        scheduler.listDoctorSchedule(doctorId, cout);
    }

    void patientScheduleFlow(const Scheduler &scheduler)
    {
        scheduler.listPatients(cout);
        const int patientId = input::readInt("\nPatient id: ", 1, 100000000);
        scheduler.listPatientSchedule(patientId, cout);
    }

    void doctorMenu(Scheduler &scheduler)
    {
        while (true)
        {
            cout << "\nDoctor Menu\n";
            cout << "-----------\n";
            cout << "1. Add doctor\n";
            cout << "2. View doctors\n";
            cout << "0. Back\n";

            const int choice = input::readInt("Choose: ", 0, 2);
            try
            {
                switch (choice)
                {
                case 1:
                    addDoctorFlow(scheduler);
                    input::pause();
                    break;
                case 2:
                    scheduler.listDoctors(cout);
                    input::pause();
                    break;
                case 0:
                    return;
                }
            }
            catch (const HospitalException &error)
            {
                cout << "Error: " << error.what() << '\n';
                input::pause();
            }
        }
    }

    void patientMenu(Scheduler &scheduler)
    {
        while (true)
        {
            cout << "\nPatient Menu\n";
            cout << "------------\n";
            cout << "1. Add patient\n";
            cout << "2. View patients\n";
            cout << "0. Back\n";

            const int choice = input::readInt("Choose: ", 0, 2);
            try
            {
                switch (choice)
                {
                case 1:
                    addPatientFlow(scheduler);
                    input::pause();
                    break;
                case 2:
                    scheduler.listPatients(cout);
                    input::pause();
                    break;
                case 0:
                    return;
                }
            }
            catch (const HospitalException &error)
            {
                cout << "Error: " << error.what() << '\n';
                input::pause();
            }
        }
    }

    void appointmentMenu(Scheduler &scheduler)
    {
        while (true)
        {
            cout << "\nAppointment Menu\n";
            cout << "----------------\n";
            cout << "1. Create appointment\n";
            cout << "2. Cancel appointment\n";
            cout << "3. View all appointments\n";
            cout << "4. View doctor schedule\n";
            cout << "5. View patient schedule\n";
            cout << "0. Back\n";

            const int choice = input::readInt("Choose: ", 0, 5);
            try
            {
                switch (choice)
                {
                case 1:
                    createAppointmentFlow(scheduler);
                    input::pause();
                    break;
                case 2:
                    cancelAppointmentFlow(scheduler);
                    input::pause();
                    break;
                case 3:
                    scheduler.listAppointments(cout);
                    input::pause();
                    break;
                case 4:
                    doctorScheduleFlow(scheduler);
                    input::pause();
                    break;
                case 5:
                    patientScheduleFlow(scheduler);
                    input::pause();
                    break;
                case 0:
                    return;
                }
            }
            catch (const HospitalException &error)
            {
                cout << "Error: " << error.what() << '\n';
                input::pause();
            }
        }
    }

}

int main()
{
    Scheduler scheduler;

    try
    {
        // Load saved file data before showing the menu.
        scheduler.load();
        cout << "Hospital Scheduling System\n";
        cout << "Data loaded from the data folder.\n";
    }
    catch (const HospitalException &error)
    {
        cout << "Startup warning: " << error.what() << '\n';
        cout << "The program will continue with empty in-memory data.\n";
    }

    bool running = true;
    while (running)
    {
        cout << "\nMain Menu\n";
        cout << "---------\n";
        cout << "1. Doctors\n";
        cout << "2. Patients\n";
        cout << "3. Appointments\n";
        cout << "4. View all people (runtime polymorphism demo)\n";
        cout << "5. Save data\n";
        cout << "0. Exit\n";

        try
        {
            const int choice = input::readInt("Choose: ", 0, 5);
            switch (choice)
            {
            case 1:
                doctorMenu(scheduler);
                break;
            case 2:
                patientMenu(scheduler);
                break;
            case 3:
                appointmentMenu(scheduler);
                break;
            case 4:
                scheduler.listAllPeoplePolymorphic(cout);
                input::pause();
                break;
            case 5:
                scheduler.save();
                cout << "Data saved.\n";
                input::pause();
                break;
            case 0:
                running = false;
                break;
            }
        }
        catch (const HospitalException &error)
        {
            cout << "Error: " << error.what() << '\n';
            if (!cin)
            {
                running = false;
            }
            else
            {
                input::pause();
            }
        }
    }

    try
    {
        scheduler.save();
        cout << "Goodbye. Data saved.\n";
    }
    catch (const HospitalException &error)
    {
        cout << "Exit warning: " << error.what() << '\n';
    }

    return 0;
}
