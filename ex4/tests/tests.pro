QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += ../node.hpp ../tree.hpp ../CustomEllipseItem.hpp ../complex.hpp
SOURCES += tests.cpp ../CustomEllipseItem.cpp ../complex.cpp

# Add the -std=c++2a flag to the C++ compiler
QMAKE_CXXFLAGS += -std=c++2a -g

QMAKE_CLEAN += test

# Define a custom target to run the program with `make run`
run.target = run
run.commands = ./test
run.depends = first # Depend on the first build target, ensuring the program is built before running

# Define a custom target to run the program with `make valgrind`
valgrind.target = valgrind
valgrind.commands = valgrind ./test --tool=memcheck -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
valgrind.depends = first

QMAKE_EXTRA_TARGETS += run valgrind