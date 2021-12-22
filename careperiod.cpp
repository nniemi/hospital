/* Careperiod for hospital.cpp
 *
 * Description: Implements the methods which are used to process patients
 * careperiod. This file contains methods which are the following:
 *
 * Get_next: Gets the next pointer from the private section of
 *            careperiod.hh file.
 * Set_next: Sets a new pointer to a next careperiod.
 * Get_patient: Gets the patient as in Person* object.
 * Set_end: Sets an end date to a careperiod.
 * Get_end: Gets the end value of a careperiod.
 * Get_staff_members: Gets the staff_members_ vector from careperiod.hh
 *            private file.
 * Set_staff: Updates the staff_member_ vector.
 * Get_start: Gets the start date of a careperiod.
 * Print_careperiod_info: Prints the careperiod info.
 * Print_staff_info: Prints the staff members of a careperiod.
 * Print_date_info: Prints the date info of a careperiod.
 *
 *
 */

#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)


{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
  
{
}

CarePeriod::~CarePeriod()
{
}

CarePeriod *CarePeriod::get_next() const
// Getter for next_
{
    return next_;
}

void CarePeriod::set_next(CarePeriod *ptr)
// Setter for next_
{
    next_ = ptr;
}

Person *CarePeriod::get_patient() const
// Getter for patient Person* object
{
    return patient_;
}

void CarePeriod::set_end(Date end)
// Sets the end for a careperiod.
{
    end_ = end;
}

Date CarePeriod::get_end()
// Getter for end date;
{
    return end_;
}


std::vector<std::string> CarePeriod::get_staff_members()
// Getter for staff members vector.
{
    return staff_member_;
}

void CarePeriod::set_staff(std::vector<std::string> staff_mem)
// Setter for staff vector.
{
    staff_member_ = staff_mem;
}

Date CarePeriod::get_start()
// Getter for start date
{
    return start_;
}


void CarePeriod::print_careperiod_info(CarePeriod *current_careperiod)
/* Prints the careperiod info.
 * PARAMS {current_careperiod}: Has a CarePeriod* object as a parameter
 *                              Used to control a particular careperiod.
 */
{
    std::cout << "* Care period: ";

    current_careperiod->get_start().print();
    std::cout << " - ";

    // Checks if the careperiod has ended
    if(!current_careperiod->get_end().is_default())
    {
        current_careperiod->get_end().print();
    }
    std::cout << std::endl;
}

void CarePeriod::print_staff_info(std::vector<std::string> staff_vector)
/* Prints the staff members of a careperiod.
 * PARAMS {current_careperiod}: Has a CarePeriod* object as a parameter
 *                              Used to control a particular careperiod.
 */
{
    std::cout << " - Staff: ";
    if(staff_vector.size() > 0)
    {
        for (int i = 0; i < int(staff_vector.size()); i++)
        {
            std::cout << staff_vector.at(i) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "None" << std::endl;
    }
}

void CarePeriod::print_date_info(CarePeriod *current_careperiod)
/* Prints the date info of a careperiod.
 * PARAMS {current_careperiod}: Has a CarePeriod* object as a parameter
 *                              Used to control a particular careperiod.
 */
{
    current_careperiod->get_start().print();
    std::cout << " - ";

    // If the careperiod has an end_date, prints it
    if (!current_careperiod->get_end().is_default())
    {
        current_careperiod->get_end().print();
    }

    std::cout << std::endl;
    std::cout << "* Patient: " <<
                 current_careperiod->get_patient()->get_id() << std::endl;
}






