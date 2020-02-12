#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// a = 4, b = 29
// x: x + 2, y: y * 2 - 1
// проходит через 9 или 19

enum OPERATIONS {
    X, Y
};


struct Operation {
    Operation *X;
    Operation *Y;
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

Operation *_direct_calculation(int start, int finish) {
    if (start > finish)
        return nullptr;
    else {
        auto node = new Operation();
        if (start == finish)
            return node;
        else {
            node->X = _direct_calculation(start + 2, finish);
            node->Y = _direct_calculation(start * 2 - 1, finish);
        }

        if (!node->X && !node->Y) {
            delete node;
            return nullptr;
        }

        return node;
    }
}

void operations_tree_to_trajectories(int start, Operation *root, std::vector<std::vector<OPERATIONS> > &trajectories,
                                     std::vector<OPERATIONS> trajectory = std::vector<OPERATIONS>()) {
    if (!root) {
        return;
    }
    if (!root->X && !root->Y)
        trajectories.push_back(trajectory);
    else {
        trajectory.push_back(X);
        operations_tree_to_trajectories(start + 2, root->X, trajectories, trajectory);
        trajectory.pop_back();
        trajectory.push_back(Y);
        operations_tree_to_trajectories(start * 2 - 1, root->Y, trajectories, trajectory);
    }
}

std::vector<std::vector<OPERATIONS> > direct_calculation(int start, int finish) {
    auto root = _direct_calculation(start, finish);
    auto trajectories = std::vector<std::vector<OPERATIONS> >();
    operations_tree_to_trajectories(start, root, trajectories);
    return trajectories;
}

std::vector<std::vector<OPERATIONS> > direct_calculation_with_route_point(int start, int finish, int route_point) {
    auto trajectories = direct_calculation(start, finish);
    for (auto trajectory = trajectories.begin(); trajectory != trajectories.end();) {
        auto trajectory_vector = trajectory_to_vector(start, *trajectory);
        if (std::find(trajectory_vector.begin(), trajectory_vector.end(), route_point) == trajectory_vector.end())
            trajectories.erase(trajectory);
        else
            trajectory++;
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

    auto trajectories_route_point1 = direct_calculation_with_route_point(start, finish, route_point1);
    std::cout << "Route point: " << route_point1 << std::endl;
    std::cout << "Direct calculation: " << trajectories_route_point1.size() << std::endl;
    for (const std::vector<OPERATIONS> &trajectory: trajectories_route_point1) {
        std::cout << trajectory_to_string(start, trajectory) << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    auto trajectories_route_point2 = direct_calculation_with_route_point(start, finish, route_point2);
    std::cout << "Route point: " << route_point2 << std::endl;
    std::cout << "Direct calculation: " << trajectories_route_point2.size() << std::endl;
    for (const std::vector<OPERATIONS> &trajectory: trajectories_route_point2) {
        std::cout << trajectory_to_string(start, trajectory) << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    return 0;
}
