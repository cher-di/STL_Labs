#include <iostream>
#include <map>
#include <string>

class Person {
    std::string surname;
    std::string initials;

public:
    Person(const std::string& surname, const std::string& initials) {
        this->surname = surname;
        this->initials = initials;
    };

    const std::string &getSurname() const {
        return surname;
    }

    const std::string &getInitials() const {
        return initials;
    }
};

bool compare_people(const Person& person1, const Person& person2) {
    return person1.getSurname() + person1.getInitials() < person2.getSurname() + person2.getInitials();
}

class ExamResults {
    int russian;
    int math;
    int informatics;

public:
    ExamResults(int russian, int math, int informatics) {
        this->russian = russian;
        this->math = math;
        this->informatics = informatics;
    }

    int sum() {
        return russian + math + informatics;
    }

    int getRussian() const {
        return russian;
    }

    int getMath() const {
        return math;
    }

    int getInformatics() const {
        return informatics;
    }
};

int main() {
    int N;
    std::cin >> N;
    std::map<Person, ExamResults*, bool(*)(const Person&, const Person&)> exam_results(compare_people);
    std::string surname, initials;
    int russian, math, informatics;
    for (int i = 0; i < N; i++) {
        std::cin >> surname >> initials >> russian >> math >> informatics;
        exam_results.insert(std::make_pair(Person(surname, initials), new ExamResults(russian, math, informatics)));
    }

    int max_sum = 0;
    for (auto iter = exam_results.begin(); iter != exam_results.end(); iter++) {
        if (iter->second->sum() > max_sum)
            max_sum = iter->second->sum();
    }

    for (auto iter = exam_results.begin(); iter != exam_results.end(); iter++) {
        if (iter->second->sum() == max_sum)
            std::cout << iter->first.getSurname() << " " << iter->first.getInitials() << " " << max_sum << std::endl;
    }

    return 0;
}
