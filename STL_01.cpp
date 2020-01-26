#include <iostream>
#include <vector>
#include <algorithm>

int bigger_than_previous_max_num(std::vector<int> const& array) {
    auto prev = array.begin();
    int curr_len = 1;
    int max_len = 1;
    for (auto iter = array.begin(); iter != array.end(); iter++) {
        if (*iter > *prev) curr_len++;
        else {
            max_len = std::max(max_len, curr_len);
            curr_len = 1;
        }
        prev = iter;
    }
    max_len = std::max(max_len, curr_len);
    return max_len;
}

void row_with_odd_zeros_num(std::vector<std::vector<int> >& matrix) {
    int zero_num = 0;
    for (auto row = matrix.begin(); row != matrix.end(); row++) {
        zero_num = 0;
        for (auto col = row->begin(); col != row->end(); col++)
            if (*col == 0) zero_num++;
        if (zero_num % 2 != 0) {
            std::vector<int>::iterator last_zero;
            for (auto col = row->begin(); col != row->end(); col++) {
                if (*col == 0) last_zero = col;
            }
            std::vector<int> result(row->size());
            std::copy(last_zero + 1, row->end(), result.begin());
            result[std::distance(last_zero, row->end()) - 1] = 0;
            std::copy(row->begin(), last_zero - 1, result.begin() + std::distance(last_zero, row->end()));
            std::copy(result.begin(), result.end(), row->begin());
            return;
        }
    }
}

bool between(int x, int a, int b) {
    return x >= a && x <= b;
}

void move_to_end(std::vector<std::vector<int> >& matrix, int a, int b) {
    for (auto row = matrix.begin(); row != matrix.end(); row++) {
        std::vector<int> in_interval;
        std::vector<int> not_in_interval;
        for (auto col = row->begin(); col != row->end(); col++) {
            if (between(*col, a, b)) in_interval.push_back(*col);
            else not_in_interval.push_back(*col);
        }
        not_in_interval.insert(not_in_interval.end(), in_interval.begin(), in_interval.end());
        std::copy(not_in_interval.begin(), not_in_interval.end(), row->begin());
    }
}

void print_matrix(std::vector<std::vector<int> > const& matrix) {
    std::cout << std::endl;
    for (auto row = matrix.begin(); row != matrix.end(); row++) {
        for (auto col = row->begin(); col != row->end(); col++)
            std::cout << *col << " ";
        std::cout << std::endl;
    }
}

void add_col_with_max_negative_values_of_every_row(std::vector<std::vector<int> >& matrix) {
    int max_negative;
    for (auto row = matrix.begin(); row != matrix.end(); row++) {
        max_negative = *(std::min_element(row->begin(), row->end()));
        for (auto col = row->begin(); col != row->end(); col++) {
            if (*col < 0) max_negative = std::max(max_negative, *col);
        }
        row->push_back(max_negative);
    }
}

void delete_row_with_max_num_of_values_in_interval(std::vector<std::vector<int> >& matrix, int a, int b) {
    int max_num = 0;
    auto row_with_max_num = matrix.begin();
    int curr_num;
    for (auto row = matrix.begin(); row != matrix.end(); row++) {
        curr_num = 0;
        for (auto col = row->begin(); col != row->end(); col++) {
            if (between(*col, a, b)) curr_num++;
        }
        if (curr_num > max_num) {
            max_num = curr_num;
            row_with_max_num = row;
        }
    }
    matrix.erase(row_with_max_num);
}

int main() {
    // First exercise
    std::vector<int> array = {19, 23, 5, 22, 16, 30, 4, 10, 21, 20, 28, 11, 9,
                              2, 27, 3, 18, 7, 15, 14, 8, 25, 13, 26, 29, 1, 6, 12, 17, 24};
    std::cout << "First exercise: " << bigger_than_previous_max_num(array) << std::endl;

    // Second exercise
    std::cout << "\n\n####################################################" << std::endl;
    std::cout << "Second exercise" << std::endl;

    std::vector<std::vector<int> > matrix = {{-2, -1, 4, 0, 3, 0},
                                             {-3, -4, 0, 0, 0, 2},
                                             {-5, -6, 0, 7, 8, 9}};
    std::cout << "Source matrix" << std::endl;
    print_matrix(matrix);

    row_with_odd_zeros_num(matrix);
    std::cout << "\nChange first row with odd number of zeros" << std::endl;
    print_matrix(matrix);

    int a = 1, b = 7;
    move_to_end(matrix, a, b);
    std::cout << "\nMove to end elements which is in [" << a << ", " << b << "]" << std::endl;
    print_matrix(matrix);

    std::sort(matrix.back().begin(), matrix.back().end());
    std::cout << "\nSorted last row" << std::endl;
    print_matrix(matrix);

    add_col_with_max_negative_values_of_every_row(matrix);
    std::cout << "\nAdded column with max negative values of every row" << std::endl;
    print_matrix(matrix);

    delete_row_with_max_num_of_values_in_interval(matrix, a, b);
    std::cout << "\nDeleted row witn max number of values in [" << a << ", " << b << "]" << std::endl;
    print_matrix(matrix);

    return 0;
}
