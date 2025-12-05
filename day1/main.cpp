#include <cstdlib>
#include <fstream>
#include <iostream>

int solutionPart1(char *inputPath) {
    int result = 0;
    std::string line;
    auto inputFile = std::ifstream(inputPath);
    int a;

    // Initial conditions of the lock
    int position = 50, rotation = 0, direction = 0;

    if (!inputFile.is_open()) {
        std::cout << "Error: File does not exist\n";
        result = -1;
    } else {
        while (std::getline(inputFile, line)) {
            direction = (line[0] == 'L' ? -1 : 1);
            rotation = atoi(line.substr(1).c_str()) * direction;
            position = (position + (rotation % 100) + 100) % 100;
            std::cout << position << "\n";
            result += (position == 0 ? 1 : 0);
        }
    }
    inputFile.close();
    return result;
}

int solutionPart2(char *inputPath) {
    int result = 0;
    std::string line;
    auto inputFile = std::ifstream(inputPath);
    int clicksDuringRotation = 0;
    int clicksAtEnd = 0;

    // Initial conditions of the lock
    int position = 50, prevPosition = 50, rotation = 0, direction = 0;

    if (!inputFile.is_open()) {
        std::cout << "Error: File does not exist\n";
        result = -1;
    } else {
        while (std::getline(inputFile, line)) {
            direction = (line[0] == 'L' ? -1 : 1);
            rotation = atoi(line.substr(1).c_str()) * direction;
            position = (position + (rotation % 100) + 100) % 100;

            // Count number of clicks from very large rotations (every 100 turns
            // is a gurarnteed pass by 0)
            clicksDuringRotation += abs(rotation / 100);

            // Only consider these cases if previous position was not 0. This
            // prevents duplicate clicks.
            if (prevPosition != 0) {
                if (position == 0) {
                    clicksAtEnd++;
                } else if (direction == -1 && (position > prevPosition)) {
                    clicksDuringRotation++;
                } else if (direction == 1 && (position < prevPosition)) {
                    clicksDuringRotation++;
                }
            }

            prevPosition = position;
        }
    }
    inputFile.close();
    result += clicksAtEnd + clicksDuringRotation;
    std::cout << "CLICKS DURING ROTATION : " << clicksDuringRotation
              << "\tCLICKS AT END: " << clicksAtEnd << "\n";
    return result;
}
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./main <path-to-input> <part>\n";
    } else {
        int result;
        if (atoi(argv[2]) == 1)
            result = solutionPart1(argv[1]);
        else
            result = solutionPart2(argv[1]);
        std::cout << "Solution (Part " << atoi(argv[2]) << "): " << result
                  << "\n";
    }
}
