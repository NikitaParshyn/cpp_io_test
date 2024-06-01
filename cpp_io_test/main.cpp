#include <iostream>
#include <fstream>
#include <chrono>

void testBufferedOutput(size_t bufferSize) {
    std::ofstream outFile("buffered_output.txt", std::ios::out | std::ios::binary);
    outFile.rdbuf()->pubsetbuf(new char[bufferSize], bufferSize);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        outFile << "This is a test line\n";
    }
    outFile.flush();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Buffered output with buffer size " << bufferSize << " took " << duration.count() << " seconds\n";
}

void testUnbufferedOutput() {
    std::ofstream outFile("unbuffered_output.txt", std::ios::out | std::ios::binary);
    outFile.rdbuf()->pubsetbuf(0, 0);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        outFile << "This is a test line\n";
    }
    outFile.flush();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Unbuffered output took " << duration.count() << " seconds\n";
}

int main() {
    testBufferedOutput(1024);    
    testBufferedOutput(4096);    
    testBufferedOutput(16384);   
    testUnbufferedOutput();

    return 0;
}
