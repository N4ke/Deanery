// Copyright 2024 Nikitos


#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "../include/Group.h"


class Group;


class Student {
 private:
    std::string id;
    std::string fio;
    Group* group;
    std::vector<int> marks;

 public:
    Student();

    Student(std::string id, std::string fio);

    Student(const Student& second);

    Student& operator= (const Student& second);

    Student(Student&& second) noexcept;

    Student& operator= (Student&& second) noexcept;

    ~Student();


    void add_to_group(Group* group);

    void add_mark(int mark);

    float get_average_mark();

    std::string get_id();

    std::string get_fio();

    Group* get_group();

    bool is_head_of_group();
};


#endif  // STUDENT_H
