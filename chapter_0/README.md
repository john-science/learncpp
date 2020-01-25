# Chapter Zero - Installation, IDE, and Intro

## Installation

With Ubuntu 18.04 I had to do very little setup. To install Code::Blocks I had to do:

sudo apt install codeblocks
sudo apt-get install build-essential  # This was already on my machine

## Compiling on the Commandline

    g++ hello_world.cpp -o HelloWorld.exe

## Compiling in CodeBlocks

This seems straight forward enough:

* create a new project
* make sure you have GNU C++ selected
* enter code
* "build" in menus
* "run" in menus

## Final Notes

* These IDEs have standard "debug" and "release" building options. I assume to save you the trouble of learning all those damn C++ compiler flags; `-O3` and all that jazz.

* Let's just learn ISO C++, and not "compiler extensions" happen to be on my laptop at the moment:

    settings >> Compilers >> warnings >> "treat as errors warnings that the code doesn't follow ISO C++"

* learncpp.com uses C++17, but I seem to only have C++14, so I will use that:

    settings >> Compilers >> `-std=c++14`
