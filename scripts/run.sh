#!/bin/sh

g++ src/main.cpp \
src/run/Runner.cpp \
src/model/Tree.cpp \
src/model/Noh.cpp \
src/model/Constants.cpp \
-o avltree && ./avltree