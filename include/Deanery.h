// Copyright 2024 Nikitos


#ifndef DEANERY_H
#define DEANERY_H

#include <vector>
#include <fstream>
#include <string>
#include "../include/Group.h"


class Deanery {
 private:
    std::vector<Group*> groups;
    std::vector<Student*> list_of_students;

 public:
    Deanery();

    Deanery(const Deanery&);

    Deanery& operator= (const Deanery&);

    Deanery(Deanery&&);

    Deanery& operator= (Deanery&&);

    ~Deanery();


    void create_groups(const std::string& file_name);

    void hire_students(const std::string& file_name);

    void add_marks_to_all();

    void get_statistics();

    void move_student(Student* student, Group* new_group);

    void save_staff();

    void fire_student(Student* student);

    void fire_students_with_bad_marks();

    void init_heads();

    std::vector<Student*> get_students_list();

    std::vector<Group*> get_groups_list();
};


#endif  // DEANERY_H
