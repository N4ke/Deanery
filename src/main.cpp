#include "../src/Student.cpp"
#include "../src/Group.cpp"
#include "../src/Deanery.cpp"
#include <iostream>


int main() {
    // создаем Deanery
    Deanery deanery;

    // создание группы и студентов из файлов
    deanery.create_groups("../data/groups.txt");
    deanery.hire_students("../data/students.txt");

    // разделяем студентов по группам
    int k = 0;
    for (const auto& student : deanery.get_students_list()) {
        if (k >= 20) {
            deanery.move_student(student, deanery.get_groups_list()[0]);
            k++;
        } else if (k >= 10) {
            deanery.move_student(student, deanery.get_groups_list()[1]);
            k++;
        } else {
            deanery.move_student(student, deanery.get_groups_list()[2]);
            k++;
        }
    }

    // добавим случайных оценок
    for (int i = 0; i < 10; i++) {
        deanery.add_marks_to_all();
    }

    // выберем старост
    deanery.init_heads();

    std::cout << "\n=======================================version 0=======================================\n";

    deanery.get_statistics();

    // переведем пару студентов в первую группу

    Student* st1 = deanery.get_groups_list()[1]->get_list()[0]; // первый студент из второй группы
    Student* st2 = deanery.get_groups_list()[2]->get_list()[0]; // первый студент из третьей группы
    deanery.move_student(st1, deanery.get_groups_list()[0]);
    deanery.move_student(st2, deanery.get_groups_list()[0]);

    std::cout << "\n=======================================version 1=======================================\n";

    deanery.get_statistics();

    // теперь отчислим студентов за неуспеваемость (возможно потребуется рерольнуть несколько раз из-за рандомных оценок)

    std::cout << "\n\nFired students:\n";
    deanery.fire_students_with_bad_marks();
    std::cout << "\n";

    std::cout << "\n=======================================version 2=======================================\n";

    deanery.get_statistics();

    // теперь можно посмотреть финальные данные в папке "data new"

    return 0;
}