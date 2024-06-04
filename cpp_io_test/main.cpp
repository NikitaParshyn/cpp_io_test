#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdio>
#include <vector>
#include <numeric>

const int NUM_ITERATIONS = 5;
const int NUM_LINES = 1000000;
const std::string testLine = "This is a test line\n";

// Функція для обчислення середнього значення
template <typename T>
double average(const std::vector<T>& times) {
    return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
}

// Тестування std::ofstream з буферизацією
double testOfstreamBuffered(size_t bufferSize) {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        std::ofstream outFile("ofstream_buffered_output.txt", std::ios::out | std::ios::binary);
        outFile.rdbuf()->pubsetbuf(new char[bufferSize], bufferSize);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            outFile << testLine;
        }
        outFile.flush();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування std::ofstream без буферизації
double testOfstreamUnbuffered() {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        std::ofstream outFile("ofstream_unbuffered_output.txt", std::ios::out | std::ios::binary);
        outFile.rdbuf()->pubsetbuf(0, 0);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            outFile << testLine;
        }
        outFile.flush();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування std::cout з буферизацією
double testStdCoutBuffered(size_t bufferSize) {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        setvbuf(stdout, new char[bufferSize], _IOFBF, bufferSize);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            std::cout << testLine;
        }
        std::cout.flush();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування std::cout без буферизації
double testStdCoutUnbuffered() {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        setvbuf(stdout, nullptr, _IONBF, 0);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            std::cout << testLine;
        }
        std::cout.flush();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування printf з буферизацією
double testPrintfBuffered(size_t bufferSize) {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        setvbuf(stdout, new char[bufferSize], _IOFBF, bufferSize);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            printf("%s", testLine.c_str());
        }
        fflush(stdout);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування printf без буферизації
double testPrintfUnbuffered() {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        setvbuf(stdout, nullptr, _IONBF, 0);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            printf("%s", testLine.c_str());
        }
        fflush(stdout);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());
    }

    return average(durations);
}

// Тестування fprintf з буферизацією
double testFprintfBuffered(size_t bufferSize) {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        FILE* outFile = fopen("fprintf_buffered_output.txt", "w");
        setvbuf(outFile, new char[bufferSize], _IOFBF, bufferSize);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            fprintf(outFile, "%s", testLine.c_str());
        }
        fflush(outFile);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());

        fclose(outFile);
    }

    return average(durations);
}

// Тестування fprintf без буферизації
double testFprintfUnbuffered() {
    std::vector<double> durations;

    for (int j = 0; j < NUM_ITERATIONS; ++j) {
        FILE* outFile = fopen("fprintf_unbuffered_output.txt", "w");
        setvbuf(outFile, nullptr, _IONBF, 0);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_LINES; ++i) {
            fprintf(outFile, "%s", testLine.c_str());
        }
        fflush(outFile);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        durations.push_back(duration.count());

        fclose(outFile);
    }

    return average(durations);
}

int main() {
    std::ifstream bufferFile("buffer_sizes.dat");
    if (!bufferFile.is_open()) {
        std::cerr << "Failed to open buffer_sizes.dat\n";
        return 1;
    }

    std::ofstream resultFile("results.txt");
    if (!resultFile.is_open()) {
        std::cerr << "Failed to open results.txt\n";
        return 1;
    }

    int bufferSize;
    while (bufferFile >> bufferSize && bufferSize != 0) {
        resultFile << "Ofstream buffered output with buffer size " << bufferSize << " took " << testOfstreamBuffered(bufferSize) << " seconds on average\n";
    }
    resultFile << "Ofstream unbuffered output took " << testOfstreamUnbuffered() << " seconds on average\n";

    bufferFile.clear();
    bufferFile.seekg(0, std::ios::beg);
    while (bufferFile >> bufferSize && bufferSize != 0) {
        resultFile << "Std::cout buffered output with buffer size " << bufferSize << " took " << testStdCoutBuffered(bufferSize) << " seconds on average\n";
    }
    resultFile << "Std::cout unbuffered output took " << testStdCoutUnbuffered() << " seconds on average\n";

    bufferFile.clear();
    bufferFile.seekg(0, std::ios::beg);
    while (bufferFile >> bufferSize && bufferSize != 0) {
        resultFile << "Printf buffered output with buffer size " << bufferSize << " took " << testPrintfBuffered(bufferSize) << " seconds on average\n";
    }
    resultFile << "Printf unbuffered output took " << testPrintfUnbuffered() << " seconds on average\n";

    bufferFile.clear();
    bufferFile.seekg(0, std::ios::beg);
    while (bufferFile >> bufferSize && bufferSize != 0) {
        resultFile << "Fprintf buffered output with buffer size " << bufferSize << " took " << testFprintfBuffered(bufferSize) << " seconds on average\n";
    }
    resultFile << "Fprintf unbuffered output took " << testFprintfUnbuffered() << " seconds on average\n";

    return 0;
}
