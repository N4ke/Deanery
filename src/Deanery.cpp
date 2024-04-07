// Copyright 2024 Nikitos


#include "../include/Deanery.h"
#include <random>
#include <iostream>


Deanery::Deanery() {}

Deanery::Deanery(const Deanery& second) :
    groups(second.groups) {}

Deanery& Deanery::operator= (const Deanery& second) {
    if (this != &second) {
        this->groups = second.groups;
    }
    return *this;
}

Deanery::Deanery(Deanery&& second) :
    groups(std::move(second.groups)) {}

Deanery& Deanery::operator= (Deanery&& second) {
    if (this != &second) {
        this->groups = std::move(second.groups);
    }
    return *this;
}

Deanery::~Deanery() {}


void Deanery::create_groups(const std::string& file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string spec, title;
        while (file >> spec) {
            std::getline(file, title);
            Group* group = new Group(title, spec);
            groups.push_back(group);
        }
        file.close();
    } else {
        std::cout << "Invalid file: " << file_name << std::endl;
    }
}

void Deanery::hire_students(const std::string& file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string id, fio;
        while (file >> id) {
            std::getline(file, fio);
            Student* student = new Student(id, fio);
            list_of_students.push_back(student);
        }
        file.close();
    } else {
        std::cout << "Invalid file: " << file_name << std::endl;
    }
}

void Deanery::add_marks_to_all() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    for (Group* group : groups) {
        for (Student* student : group->get_list()) {
            int mark = dist(gen);
            student->add_mark(mark);
        }
    }

    save_staff();
}

void Deanery::get_statistics() {
    for (Group* group : groups) {
        std::cout << "---Group: " << group->get_spec()
            << " " << group->get_title() << "---"
            << "\nAverage mark: " << group->get_average_mark()
            << "\nList of students: " << std::endl;
        for (Student* student : group->get_list()) {
            std::cout << "- " << student->get_id() << " " << student->get_fio()
                << ", Av.mark: " << student->get_average_mark() << std::endl;
        }
    }
}

void Deanery::move_student(Student* student, Group* new_group) {
    if (!new_group->contains_student(student)
        && student->get_group() != nullptr) {
        student->get_group()->remove_student(student);
        student->add_to_group(new_group);
        new_group->add_student(student);
        save_staff();
    } else if (!new_group->contains_student(student)) {
        student->add_to_group(new_group);
        new_group->add_student(student);
        save_staff();
    } else {
        std::cout << "Student is already in this group" << std::endl;
    }
}

void Deanery::save_staff() {
    std::string studs = "../data new/students.txt";
    std::ofstream students_file(studs, std::ofstream::trunc);

    if (students_file.is_open()) {
        for (Student* student : list_of_students) {
            students_file << student->get_id() << " "
                << student->get_fio() << " - Group: ";
                if (student->get_group() != nullptr) {
                    students_file <<
                        student->get_group()->get_spec() << " - Av.mark: ";
                } else {
                    students_file << "None - Av.mark: ";
                }
                students_file << student->get_average_mark() << std::endl;
        }
    }

    std::string grs = "../data new/groups.txt";
    std::ofstream groups_file(grs, std::ofstream::trunc);

    if (groups_file.is_open()) {
        for (Group* group : groups) {
            groups_file << group->get_spec() << " "
                << group->get_title() << " - Head: ";
            if (group->get_head() != nullptr) {
                groups_file << group->get_head()->get_fio() << std::endl;
            } else {
                groups_file << "None" << std::endl;
            }
        }
    }
}

void Deanery::fire_student(Student* student) {
    student->get_group()->remove_student(student);
    student->add_to_group(nullptr);
    save_staff();
}

void Deanery::fire_students_with_bad_marks() {
    std::vector<Student*> studs;

    for (Group* group : groups) {
        for (Student* student : group->get_list()) {
            if (student->get_average_mark() < 4.0) {
                studs.push_back(student);
                std::cout << student->get_fio()
                    << " from " << student->get_group()->get_spec()
                    << " fired for academic failure" << std::endl;
            }
        }
    }

    for (const auto& student : studs) {
        fire_student(student);
    }
}

void Deanery::init_heads() {
    for (Group* group : groups) {
        if (group->get_group_size() > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            size_t gr_size = group->get_group_size() - 1;
            std::uniform_int_distribution<> dist(0, gr_size);
            int rand = dist(gen);

            group->choose_head(group->get_list()[rand]);
        }
    }
    save_staff();
}

std::vector<Student*> Deanery::get_students_list() {
    return list_of_students;
}

std::vector<Group*> Deanery::get_groups_list() {
    return groups;
}
