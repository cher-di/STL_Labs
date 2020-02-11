#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// a = 4, b = 29
// x: x + 2, y: y * 2 - 1
// проходит через 9 или 19

enum OPERATIONS {
    X, Y
};

std::string trajectory_to_string(int start, const std::vector<OPERATIONS> &trajectory) {
    auto result = std::string(trajectory.size(), '(');
    result += std::to_string(start);
    for (OPERATIONS operation: trajectory)
        result += operation == X ? " + 2)" : " * 2 - 1)";
    return result;
}

std::vector<int> trajectory_to_vector(int start, const std::vector<OPERATIONS> &trajectory) {
    int result = start;
    auto trajectory_vector = std::vector<int>(trajectory.size());
    auto route_point = trajectory_vector.begin();
    for (auto operation = trajectory.begin(); operation != trajectory.end(); operation++, route_point++) {
        result = *operation == X ? result + 2 : result * 2 - 1;
        *route_point = result;
    }
    return trajectory_vector;
}

void _direct_calculation(int start, int finish, std::vector<std::vector<OPERATIONS> > &trajectories,
                         const std::vector<OPERATIONS> &trajectory = std::vector<OPERATIONS>()) {
    if (start == finish)
        trajectories.push_back(trajectory);
    else if (start > finish)
        return;
    else {
        auto new_trajectory_X = std::vector<OPERATIONS>(trajectory);
        new_trajectory_X.push_back(X);
        auto new_trajectory_Y = std::vector<OPERATIONS>(trajectory);
        new_trajectory_Y.push_back(Y);

        _direct_calculation([](int x) { return x + 2; }(start), finish, trajectories, new_trajectory_X);
        _direct_calculation([](int x) { return 2 * x - 1; }(start), finish, trajectories, new_trajectory_Y);
    }
}

std::vector<std::vector<OPERATIONS> > direct_calculation(int start, int finish, const int* route_point = nullptr) {
    auto trajectories = std::vector<std::vector<OPERATIONS> >();
    _direct_calculation(start, finish, trajectories);

    if (route_point) {
        for (auto trajectory = trajectories.begin(); trajectory != trajectories.end();) {
            std::vector<int> trajectory_vector = trajectory_to_vector(start, *trajectory);
            if (std::find(trajectory_vector.begin(), trajectory_vector.end(), *route_point) == trajectory_vector.end())
                trajectories.erase(trajectory);
            else
                trajectory++;
        }
    }
    
    return trajectories;
}


int main() {
    int start = 4, finish = 29, route_point1 = 9, route_point2 = 19;
    
    auto trajectories = direct_calculation(start, finish);
    std::cout << "Direct calculation: " << trajectories.size() << std::endl;
    for (const std::vector<OPERATIONS> &trajectory: trajectories) {
        std::cout << trajectory_to_string(start, trajectory) << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    auto trajectories_route_point1 = direct_calculation(start, finish, &route_point1);
    std::cout << "Route point: " << route_point1 << std::endl;
    std::cout << "Direct calculation: " << trajectories_route_point1.size() << std::endl;
    for (const std::vector<OPERATIONS> &trajectory: trajectories_route_point1) {
        std::cout << trajectory_to_string(start, trajectory) << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    auto trajectories_route_point2 = direct_calculation(start, finish, &route_point2);
    std::cout << "Route point: " << route_point2 << std::endl;
    std::cout << "Direct calculation: " << trajectories_route_point2.size() << std::endl;
    for (const std::vector<OPERATIONS> &trajectory: trajectories_route_point2) {
        std::cout << trajectory_to_string(start, trajectory) << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;
    
    return 0;
}
