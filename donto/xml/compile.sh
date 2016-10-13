#!/bin/bash -x

g++-6 main.cpp my_option_parser.cpp rule.cpp xml_composer.cpp -std=c++14 -Bstatic -lboost_program_options -lboost_system -lboost_filesystem -oaludjunkRa
