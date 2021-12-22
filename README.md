## Hospital project / C++ classes and objects
This program is for controlling a hospital database using classes and objects. This was the first time I got deep into C++ classes. The repositorry contains some files which were provided from our base code such as cli.cpp and cli.hh, this was made so the implementation of the functions were more clear and focused on implementing the classes. 

This program has following functions to control the database:
 * Recruit <staff id>: Inputs a staff member. Stores it to staff_ vector
 * ENTER <id>: Inputs a patient, creates a linked list where the careperiod of a patient is stored. Adds the patient to current_patients.
 * Leave <id>: Removes the patient from current_patients. Adds an end date to a careperiod.
 * Assign_staff <staff_id> <patient_id>: Assigns a staff member to a patient.
 * Add_medicine <medicine> <strength> <dosage> <patient>: Adds a medicine to a patients careperiod
 * Remove_medicine <Medicine> <patient_id>: Removes a medicine from a patients careperiod
 * Print_patient_info <patient_id>: Prints info of a careperiod.
 * Print_care_periods_per_staff <staff_id>: Prints all the careperiods which are assigned to a staff member.
 * Print_all_medicines: Prints all the medicines and all the patients which have the medicine assigned to them.
 * Print_all_staff: Prints all staff members which exist in the hospital
 * Print_all_patients: Prints all patients and their careperiods if they have visited the hospital.
 * Print_current_patients: Prints information of each patient which is in the hospital currently.
 * Set_date <day> <month> <year>: Sets the date to a particular date.
 * Advance_date <amount>: Advances the date for <amount> of days.
  
  ![MP0Ouy4pzI](https://user-images.githubusercontent.com/70947133/147107271-ed435049-1e9e-4021-a146-0225cc4110fe.gif)

  *A simple example of the program running*
  
  
  The repository also contains an assignment.input, which contains some basic commands to initialize the database. This program was created with QT Creator, so it might not run as smoothly on other IDEs.
  
  
