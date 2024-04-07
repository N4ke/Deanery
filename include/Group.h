// Copyright 2024 Nikitos


#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include "../include/Student.h"


class Student;


class Group {
 private:
    std::string group_title;
    std::string specialization;
    std::vector<Student*> list_of_students;
    Student* head;

 public:
    Group();

    Group(std::string group_title, std::string specialization);

    Group(const Group& second);

    Group& operator= (const Group& second);

    Group(Group&& second) noexcept;

    Group& operator= (Group&& second) noexcept;

    ~Group();


    void add_student(Student* student);

    void choose_head(Student* student);

    Student* get_student(std::string id_or_fio);

    float get_average_mark();

    Student* get_head();

    void remove_student(Student* student);

    bool contains_student(Student* student);

    bool is_empty();

    std::string get_title();

    std::string get_spec();

    size_t get_group_size();

    std::vector<Student*> get_list();
};


#endif  // GROUP_H
