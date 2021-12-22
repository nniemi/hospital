/* Hospital database
 *
 * Description:
 * This program is a basic database for hospital. The user can:
 * Recruit <staff id>: Inputs a staff member. Stores it to staff_ vector
 * ENTER <id>: Inputs a patient, creates a linked list
 *             where the careperiod of a patient is stored.
 *             Adds the patient to current_patients.
 * Leave <id>: Removes the patient from current_patients. Adds an end
 *             date to a careperiod.
 * Assign_staff <staff_id> <patient_id>: Assigns a staff member to a
 *              patient.
 * Add_medicine <medicine> <strength> <dosage> <patient>: Adds a medicine
 *              to a patients careperiod
 * Remove_medicine <Med
 * icine> <patient_id>: Removes a medicine from a
 *              patients careperiod
 * Print_patient_info <patient_id>: Prints info of a careperiod.
 * Print_care_periods_per_staff <staff_id>: Prints all the careperiods
 *              which are assigned to a staff member.
 * Print_all_medicines: Prints all the medicines and all the patients which
 *              have the medicine assigned to them.
 * Print_all_staff: Prints all staff members which exist in the hospital
 * Print_all_patients: Prints all patients and their careperiods if they
 *              have visited the hospital.
 * Print_current_patients: Prints information of each patient which is in
 *              the hospital currently.
 * Set_date <day> <month> <year>: Sets the date to a particular date.
 * Advance_date <amount>: Advances the date for <amount> of days.
 *
 */


#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
    first_ = nullptr;
    last_ = nullptr;
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }

    CarePeriod* current = first_;
    while (current != nullptr) {
        CarePeriod* temp = current;
        current = temp->get_next();
        delete temp;

    }
}

void Hospital::recruit(Params params)
/* Inputs a staff member. Stores it to staff_ vector
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
/* Inputs a patient, creates a linked list where the careperiod of
 * a patient is stored. Adds the patient to current_patients.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) != current_patients_.end())
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;

    }
    Person* new_patient = new Person(patient_id);

    current_patients_.insert({patient_id, new_patient});
    all_patients_.insert({patient_id, new_patient});

    CarePeriod* new_careperiod = new CarePeriod(utils::today,new_patient);
    
    if (first_ == nullptr)
    {
        first_ = new_careperiod;
        last_ = new_careperiod;


    } else {

        last_->set_next(new_careperiod);
        last_ = new_careperiod;

    }
    
    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
/* Removes the patient from current_patients. Adds an end date to
 * a careperiod.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string patient_id = params.at(0);
    CarePeriod* current_careperiod = first_;

    // Checks if the current_careperiod is in the hospital.
    if( current_patients_.find(patient_id) != current_patients_.end())
    {
        //Erases the patient from current_patients
        current_patients_.erase(patient_id);

        // Loops through CarePeriod linked list to find correct user
        // Adds an end date to CarePeriod
        while(current_careperiod != nullptr)
        {

            if(current_careperiod->get_patient()->get_id() == patient_id)
            {

                Date end_date = utils::today;
                current_careperiod->set_end(end_date);
                break;
            }
            // Moves the pointer to the next patient.
            current_careperiod = current_careperiod->get_next();
        }
        std::cout << PATIENT_LEFT << std::endl;
    } else {
        std::cout << CANT_FIND << patient_id << std::endl;
    }

}

void Hospital::assign_staff(Params params)
/* Assigns a staff member to a patiants careperiod.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 *
 */
{

    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    CarePeriod* current_careperiod = first_;

    // Loops through patients and checks if a patient is found.
    while(current_careperiod != nullptr)
    {
        std::vector<std::string> staff_vector =
                current_careperiod->get_staff_members();

        // Checks if the staff member is recruited.
        if( staff_.find(staff_id) == staff_.end() )
        {
            std::cout << CANT_FIND << staff_id << std::endl;
            return;

        }

        if (all_patients_.find(patient_id) == all_patients_.end())
        {
            std::cout << CANT_FIND << patient_id << std::endl;
            return;
        }

        if(current_careperiod->get_patient()->get_id() == patient_id)
        {

            // If the staff member has already been assigned to a patient,
            // function will return.
            if( std::find(staff_vector.begin(), staff_vector.end(), staff_id)
                    != staff_vector.end())
            {
                std::cout << STAFF_ASSIGNED << patient_id << std::endl;
                return;
            }

            // Checks if the staff member is already added to the patient.
            // If not, push_backs the staff member.
            if(std::find(staff_vector.begin(), staff_vector.end(),
                         staff_id) == staff_vector.end())
            {
                staff_vector.push_back(staff_id);
                std::cout << STAFF_ASSIGNED << patient_id << std::endl;
                current_careperiod->set_staff(staff_vector);


            }

        }



        // Moves the pointer to the next patient
        staff_vector.clear();
        current_careperiod = current_careperiod->get_next();
    }

}

void Hospital::add_medicine(Params params)
/* Adds a medicine to patients careperiod.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
            not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
/* Removes a medicine from a patients careperiod
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
/* Prints info of a careperiod.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string patient_id = params.at(0);


    CarePeriod* current_careperiod = first_;

    if(all_patients_.find(patient_id) == all_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Loops through patients
    while (current_careperiod != nullptr)
    {
        std::vector<std::string> staff_vector =
                current_careperiod->get_staff_members();

        std::sort(staff_vector.begin(),staff_vector.end());


        // Checks the id for the current careperiod
        if(current_careperiod->get_patient()->get_id() == patient_id)
        {
            // Checks if the patient has ever been in the hospital
            if(all_patients_.find(current_careperiod->get_patient()->get_id())
                    == all_patients_.end())
            {
                std::cout << CANT_FIND << patient_id << std::endl;
                return;

            }

            current_careperiod->print_careperiod_info(current_careperiod);

            current_careperiod->print_staff_info(staff_vector);


        }

        // Moves the pointer to the next patient
        current_careperiod = current_careperiod->get_next();

    }
    // Prints the medicines for each patient
    current_careperiod = first_;
    std::cout << "* Medicines: ";


    // Loops through the linked list.
    while (current_careperiod != nullptr)
    {
        std::string patient = current_careperiod->get_patient()->get_id();
        if (all_patients_.at(patient)->get_id() == patient_id) {

            if( current_patients_.find(patient_id) != current_patients_.end() &&
                    all_patients_.at(patient)->get_medicines().size() == 0)
            {
                current_patients_.at(patient)->print_medicines(" - ");
                return;
            } else {
                all_patients_.at(patient)->print_medicines(" - ");
                return;
            }




    }
        current_careperiod = current_careperiod->get_next();
}


}

void Hospital::print_care_periods_per_staff(Params params)
/* Prints all the careperiods which are assigned to a staff member.
     * PARAMS {params}: Vector which includes a parameter ie. patient id
     */
{

    std::string staff_id = params.at(0);
    CarePeriod* current_careperiod = first_;

    if (first_ == nullptr)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Loops through careperiods
    while (current_careperiod != nullptr)
    {
        for (std::string staff_member : current_careperiod->get_staff_members())
        {
            // Checks if the patient has ever been in the hospital
            if( all_patients_.find(current_careperiod->get_patient()->get_id())
                    == all_patients_.end())
            {
                std::cout << CANT_FIND << std::endl;
                return;

            }

            // Checks if the current is the staff member in question
            if(staff_member == staff_id)
            {

                current_careperiod->print_date_info(current_careperiod);

            } else {
                std::cout << CANT_FIND << staff_id << std::endl;
                return;

            }
        }
        // Sets the pointer to the next careperiod
        current_careperiod = current_careperiod->get_next();
    }

}

void Hospital::print_all_medicines(Params)
/* Prints all the medicines and all the patients which have the medicine
 * assigned to them
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */

{
    CarePeriod* current_careperiod = first_;
    std::map<std::string,std::set<std::string>> med_map = {};


    if(current_careperiod == nullptr) {
        std::cout << "None" << std::endl;
    }

    while (current_careperiod != nullptr) {

        std::set<std::string> temp_set;

        // Loops through medicines of the current_careperiod
        for(std::string med :
            current_careperiod->get_patient()->get_medicines())
        {
            // Checks if the medicine is already in the med_map
            if (med_map.find(med) == med_map.end())
            {
                temp_set.insert(current_careperiod->get_patient()->get_id());
                med_map.insert({med,temp_set});

            } else {

                med_map.at(med).insert
                        (current_careperiod->get_patient()->get_id());

            }

        }
        current_careperiod = current_careperiod->get_next();
    }

    // Prints which patient has which medicine
    for (std::pair<std::string,std::set<std::string>> med : med_map)
    {
        std::cout << med.first << " prescribed for" << std::endl;
        for(std::string patient : med.second)
        {
            std::cout << "* " << patient << std::endl;
        }
    }

}

void Hospital::print_all_staff(Params)
/* Prints all existing staff members.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 *
 */
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
/* Prints all patients and their careperiods if they
 * have visited the hospital.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 *
 */
{
    CarePeriod* current_careperiod = first_;
    std::vector<std::string> patient_vector = {};

    // Checks if there are any patients
    if(current_careperiod == nullptr)
    {
        std::cout << "None" << std::endl;
        return;
    }


    // Loops through the careperiods and stores the patient names to a vector
    while(current_careperiod != nullptr)
    {

        std::string patient_id = current_careperiod->get_patient()->get_id();
        if (std::find(patient_vector.begin(),patient_vector.end(), patient_id)
                == patient_vector.end())
        {
            patient_vector.push_back(patient_id);

        }
        current_careperiod = current_careperiod->get_next();

    }
    // Sorts the patient_vector alphabetically
    std::sort(patient_vector.begin(),patient_vector.end());

    // Loops through the patient vector and prints the info of a patient
    for(std::string id : patient_vector) {

        std::cout << id << std::endl;
        std::vector<std::string> temp_vec = {id};
        print_patient_info(temp_vec);
    }

}

void Hospital::print_current_patients(Params)
/* Prints information of each patient which is in the hospital currently.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    if (current_patients_.empty())
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(std::pair<std::string,Person*> patient : current_patients_)
    {

        std::string patient_id = patient.second->get_id();
        std::cout << patient_id << std::endl;
        std::vector<std::string> patient_vector = {patient_id};
        print_patient_info(patient_vector);

    }
}

void Hospital::set_date(Params params)
/* Sets the date to a particular date
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
            not utils::is_numeric(month, false) or
            not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
/* Advances a date for x amount of days.
 * PARAMS {params}: Vector which includes a parameter ie. patient id
 */
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}


