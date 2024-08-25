#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace doctest;

const int MIN_TESTS = 20;

int return_code = -1;

struct ReporterCounter : public ConsoleReporter {
    ReporterCounter(const ContextOptions &input_options)
        : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats &run_stats) override {
        if (run_stats.numAsserts >= MIN_TESTS) {
            return_code = 0;
        } else {
            std::cout << "Please write at least " << MIN_TESTS << " tests! " << std::endl;
            return_code = 1;
        }

        std::cout << "\033[1;36m\nTest run summary:\n\033[0m";
        std::cout << "\033[1;32mNumber of assertions: \033[0m" << run_stats.numAsserts << std::endl;
        std::cout << "\033[1;31mNumber of failed assertions: \033[0m" << run_stats.numAssertsFailed << std::endl;
        std::cout << "\033[1;32mNumber of test cases passed: \033[0m" << run_stats.numTestCases - run_stats.numTestCasesFailed << std::endl;
        std::cout << "\033[1;31mNumber of test cases failed: \033[0m" << run_stats.numTestCasesFailed << std::endl;

        if (run_stats.numTestCasesFailed > 0) {
            if (run_stats.numTestCasesFailed == run_stats.numTestCases) {
                std::cout << "\n\n\033[1;31m~~~ All tests failed! GO FIX YOUR CODE LOSER! ~~~\033[0m\n"
                          << std::endl;
            } else {
                std::cout << "\n\n\033[1;31m~~~ Some tests failed! ~~~\033[0m\n"
                          << std::endl;
            }
        } else {
            std::cout << "\n\n\033[1;32m~~~ All tests passed! ~~~\033[0m\n"
                      << std::endl;
        }
    }
};

REGISTER_REPORTER("counter", 1, ReporterCounter);

int main(int argc, char **argv) {
    Context context;
    context.addFilter("reporters", "counter");
    context.run();
    return return_code;
}