#include <iostream>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

// 1. 1
// 2. 3
// 3. 1
// 4. 4
// 5. 3

std::set<int> get_even_elements(const std::set<int>& set) {
    std::set<int> result;
    for (int value : set) {
        if (value % 2 == 0)
            result.insert(value);
    }
    return result;
}

void print_set(const std::set<int>& set) {
    for (int i: set)
        std::cout << i << " ";
    std::cout << std::endl;
}

int main() {
    // 1. Input from console
    std::set<int> U, A, B;
    int N, temp;
    std::cout << "Input number of elements in set: ";
    std::cin >> N;
    std::cout << "Input elements of set: ";
    for (int i = 0; i < N; i++) {
        std::cin >> temp;
        U.insert(temp);
    }

    // 2. Find A
    A = get_even_elements(U);

    // 3. Find B
    const int col_width = 6;
    std::cout << std::setw(col_width) << "Number" << std::setw(col_width) << "Value" << std::endl;
    std::cout << std::string(col_width * 2, '-') << std::endl;
    int i = 1;
    std::vector<int> U_array = std::vector<int>(U.begin(), U.end());
    for (auto iter = U_array.begin(); iter != U_array.end(); iter++, i++)
        std::cout << std::setw(col_width) << i << std::setw(col_width) << *iter << std::endl;
    std::cout << "Input number of chosen elements: ";
    std::cin >> N;
    std::cout << "Choose numbers of elements: ";
    for (i = 0; i < N; i++) {
        std::cin >> temp;
        B.insert(U_array[temp - 1]);
    }

    // Printing A and B
    std::cout << "A: ";
    print_set(A);
    std::cout << "B: ";
    print_set(B);

    // 4. not (A or B) == not A and not B
    std::set<int> first_method, second_method;

    // first method
    std::set<int> A_B_union;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(A_B_union, A_B_union.begin()));
    std::set_difference(U.begin(), U.end(), A_B_union.begin(), A_B_union.end(), std::inserter(first_method, first_method.begin()));

    // second method
    std::set<int> A_addition, B_addition;
    std::set_difference(U.begin(), U.end(), A.begin(), A.end(), std::inserter(A_addition, A_addition.begin()));
    std::set_difference(U.begin(), U.end(), B.begin(), B.end(), std::inserter(B_addition, B_addition.begin()));
    std::set_intersection(A_addition.begin(), A_addition.end(), B_addition.begin(), B_addition.end(), std::inserter(second_method, second_method.begin()));

    // printing results of first method and second method
    std::cout << "First method: ";
    print_set(first_method);
    std::cout << "Second method: ";
    print_set(second_method);
    if (first_method == second_method)
        std::cout << "Correct!" << std::endl;
    else
        std::cout << "Incorrect..." << std::endl;

    // 5. Printing odd elements from result
    std::set<int> odd_elements, even_elements;
    even_elements = get_even_elements(first_method);
    std::set_difference(first_method.begin(), first_method.end(), even_elements.begin(), even_elements.end(), std::inserter(odd_elements, odd_elements.begin()));
    std::cout << "Odd elements of result: ";
    print_set(odd_elements);

    return 0;
}
