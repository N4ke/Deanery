// Copyright 2024 Nikitos


#include "../include/Student.h"
#include <numeric>


Student::Student() :
    id(nullptr),
    fio(nullptr),
    group(nullptr) {}

Student::Student(std::string _id, std::string _fio) :
    id(_id),
    fio(_fio),
    group(nullptr) {}

Student::Student(const Student& second) :
    id(second.id),
    fio(second.fio),
    group(second.group) {}

Student& Student::operator= (const Student& second) {
    if (this != &second) {
        this->id = second.id;
        this->fio = second.fio;
        this->group = second.group;
    }
    return *this;
}

Student::Student(Student&& second) noexcept :
    id(std::move(id)),
    fio(std::move(fio)),
    group(std::move(group)) {}

Student& Student::operator= (Student&& second) noexcept {
    if (this != &second) {
        this->id = std::move(second.id);
        this->fio = std::move(second.fio);
        this->group = std::move(second.group);
    }
    return *this;
}

Student::~Student() {}


void Student::add_to_group(Group* _group) {
    group = _group;
}

void Student::add_mark(int mark) {
    marks.push_back(mark);
}

float Student::get_average_mark() {
    float sum;
    sum = std::accumulate(marks.begin(), marks.end(), 0.0f);
    return sum / static_cast<float>(marks.size());
}

std::string Student::get_id() {
    return id;
}

std::string Student::get_fio() {
    return fio;
}

Group* Student::get_group() {
    return group;
}

bool Student::is_head_of_group() {
    Student* head = group->get_head();
    return id == head->get_id();
}
