#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

// Дан массив слов

// 1. Преобразовать исходный массив, вставив в каждое слово
// длиной более двух и менее 6 символов после второй буквы подстроку из двух
// конечных букв этого же слова.

// 2. Удалить из всех слов массива все латинские
//буквы.

// 3. Сформировать предложение из тех слов полученного массива,
//которые являются «перевертышами». Слова в предложении должны быть
//упорядочены по длине слов.


void print_array_of_words(const std::vector<std::string>& array) {
    static const int number_col_width = 7, word_col_width = 30;
    std::cout << std::left << std::setw(number_col_width) << "Number" << std::setw(word_col_width) << "Word" << std::endl;
    std::cout << std::string(number_col_width + word_col_width, '-') << std::endl;
    int i = 1;
    for (auto iter = array.begin(); iter != array.end(); iter++, i++)
        std::cout << std::setw(number_col_width) << i << std::setw(word_col_width) << *iter << std::endl;
}


void insert_two_last_letters(std::string& string) {
    char last_two_letters[2];
    string.copy(last_two_letters, 2, string.length() - 2);
    string.insert(2, last_two_letters, 2);
}


std::string delete_latin_letters(const std::string& string) {
    static const std::string LATIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
    std::string string_without_latin_letters = std::string();
    for (char letter: string) {
        if (LATIN_LETTERS.find(std::tolower(letter)) == -1)
            string_without_latin_letters += letter;
    }
    return string_without_latin_letters;
}


bool is_palindrome(const std::string& string) {
    int right_border = string.length() % 2 == 0 ? (int)(string.length() / 2) : (int)(string.length() / 2) + 1;
    for (int i = 0, j = string.length() - 1; i < right_border; i++, j--) {
        if (string.at(i) != string.at(j))
            return false;
    }
    return true;
}


bool compare(const std::string& string1, const std::string& string2) {
    return string1.length() < string2.length();
}


void first_exercise(std::vector<std::string>& array) {
    for (auto iter = array.begin(); iter != array.end(); iter++) {
        if (2 < iter->length() && iter->length() < 6)
            insert_two_last_letters(*iter);
    }
}

void second_exercise(std::vector<std::string>& array) {
    for (auto iter = array.begin(); iter != array.end(); iter++)
        *iter = delete_latin_letters(*iter);
}

std::string third_exercise(const std::vector<std::string>& array) {
    std::vector<std::string> palindromes = {};
    for (auto iter = array.begin(); iter != array.end(); iter++) {
        if (is_palindrome(*iter))
            palindromes.push_back(*iter);
    }
    std::sort(palindromes.begin(), palindromes.end(), compare);
    std::string sentence = *(palindromes.begin());
    for (auto iter = palindromes.begin() + 1; iter != palindromes.end(); iter++)
        sentence += " " + *iter;
    return sentence;
}


int main() {
    // Читаем массив
    int N;
    std::cout << "Введите количество слов: ";
    std::cin >> N;
    std::vector<std::string> array(N);
    std::cout << "Введите слова, разделяя их пробелом: ";
    for (auto iter = array.begin(); iter != array.end(); iter++)
        std::cin >> (*iter);

    std::cout << "Исходный массив:" << std::endl;
    print_array_of_words(array);
    std::cout << std::endl;

    first_exercise(array);
    std::cout << "Массив после преобразования 1:" << std::endl;
    print_array_of_words(array);
    std::cout << std::endl;

    second_exercise(array);
    std::cout << "Массив после преобразования 2:" << std::endl;
    print_array_of_words(array);
    std::cout << std::endl;

    std::string sentence = third_exercise(array);
    std::cout << "Предложение, составленное по правилам задания 3: " << sentence << std::endl;

    return 0;
}
