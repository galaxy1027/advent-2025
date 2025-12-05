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
            position = (position + rotation + 100) % 100;
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

    // Initial conditions of the lock
    int position = 50, prevPosition = -0, rotation = 0, direction = 0;

    if (!inputFile.is_open()) {
        std::cout << "Error: File does not exist\n";
        result = -1;
    } else {
        while (std::getline(inputFile, line)) {
            direction = (line[0] == 'L' ? -1 : 1);
            rotation = atoi(line.substr(1).c_str()) * direction;
            position = (position + rotation + 100) % 100;
            std::cout << position << "\n";

            if (direction == -1) {
                if (prevPosition > position) {
                    result += 1;
                }
            } else if (prevPosition < position) {
                result += 1;
            }

            // Figure out how many times 0 was passed due to excess rotation
            result += (rotation) / 100;
        }
    }
    inputFile.close();
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
