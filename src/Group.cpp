// Copyright 2024 Nikitos


#include "../include/Group.h"
#include <algorithm>
#include <numeric>


Group::Group() :
    group_title(nullptr),
    specialization(nullptr),
    head(nullptr) {}

Group::Group(std::string _group_title, std::string _specialization) :
    group_title(_group_title),
    specialization(_specialization),
    head(nullptr) {}

Group::Group(const Group& second) :
    group_title(second.group_title),
    specialization(second.specialization),
    head(second.head) {}

Group& Group::operator= (const Group& second) {
    if (this != &second) {
        this->group_title = second.group_title;
        this->specialization = second.specialization;
        this->head = second.head;
    }
    return *this;
}

Group::Group(Group&& second) noexcept :
    group_title(std::move(second.group_title)),
    specialization(std::move(second.specialization)) {}

Group& Group::operator= (Group&& second) noexcept {
    if (this != &second) {
        this->group_title = std::move(second.group_title);
        this->specialization = std::move(second.specialization);
    }
    return *this;
}

Group::~Group() {}


void Group::add_student(Student* student) {
    list_of_students.push_back(student);
}

void Group::choose_head(Student* student) {
    head = student;
}

Student* Group::get_student(std::string id_or_fio) {
    for (int i = 0; i < list_of_students.size(); i++) {
        if (list_of_students[i]->get_id() == id_or_fio
        || list_of_students[i]->get_fio() == id_or_fio) {
            return list_of_students[i];
        }
    }
    return nullptr;
}

float Group::get_average_mark() {
    float sum;
    std::vector<float> av_marks;

    for (Student* student : list_of_students) {
        av_marks.push_back(student->get_average_mark());
    }

    sum = std::accumulate(av_marks.begin(),
                        av_marks.end(),
                        0.0f);

    return sum / static_cast<float>(list_of_students.size());
}

Student* Group::get_head() {
    return head;
}

void Group::remove_student(Student* student) {
    list_of_students.erase(
        std::remove(
            list_of_students.begin(),
            list_of_students.end(),
            student),
        list_of_students.end());
}

bool Group::contains_student(Student* student) {
    return get_student(student->get_id()) == student;
}

bool Group::is_empty() {
    return list_of_students.empty();
}

std::string Group::get_spec() {
    return specialization;
}

std::string Group::get_title() {
    return group_title;
}

size_t Group::get_group_size() {
    return list_of_students.size();
}

std::vector<Student*> Group::get_list() {
    return list_of_students;
}
