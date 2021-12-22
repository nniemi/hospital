/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Contains the commands for careperiod.cpp
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

     // Getter for next_
     CarePeriod* get_next() const;
     
     // Setter for next_
     void set_next(CarePeriod* ptr);
    
     // Getter for patient
     Person* get_patient() const;

     // Setter for end date
     void set_end(Date end);


     // Getter for staff_members
     std::vector<std::string> get_staff_members();

     // Setter for staff_members
     void set_staff(std::vector<std::string> staff_mem);

     // Getter for start date.
     Date get_start();

     // Getter for end date.
     Date get_end();

     // Prints info of a careperiod
     void print_careperiod_info(CarePeriod* current_careperiod);

     // Prints staff info
     void print_staff_info(std::vector<std::string> staff_vector);

     // Prints date info
     void print_date_info(CarePeriod* current_careperiod);




private:
    Person* patient_;
    Date start_;
    Date end_;

    CarePeriod* next_ = nullptr;
   
    std::vector<std::string> staff_member_;
};

#endif // CAREPERIOD_HH
