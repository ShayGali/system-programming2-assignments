QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += node.hpp tree.hpp CustomEllipseItem.hpp complex.hpp
SOURCES += main.cpp CustomEllipseItem.cpp complex.cpp

# Define a custom target to run the program with `make run`
run.target = run
run.commands = ./main
run.depends = first # Depend on the first build target, ensuring the program is built before running

# Define a custom target to run the program with `make tree`
tree.target = tree
tree.commands = ./main
tree.depends = first # Depend on the first build target, ensuring the program is built before running

# Define a custom target to run the tests with `make test`  
test.target = test
test.commands = make -C tests run

# Define a custom target to run the tests with `make valgrind`
# we add qt to suppression list to avoid false positives
valgrind.target = valgrind
valgrind.commands = valgrind ./main --tool=memcheck -v --leak-check=full --show-leak-kinds=all --suppressions=qt.supp --error-exitcode=99
valgrind.depends = first

# Add the tree executable to the clean files
QMAKE_CLEAN += main .qmake.stash test

# Add the -std=c++2a flag to the C++ compiler
QMAKE_CXXFLAGS += -std=c++2a -g

# Add the custom targets to the list of extra targets
QMAKE_EXTRA_TARGETS += run tree test valgrind
