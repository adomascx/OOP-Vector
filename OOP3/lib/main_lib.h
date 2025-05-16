#pragma once

#include <stdexcept>
using std::runtime_error;

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <iomanip>
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;

#include <algorithm>
using std::find_if;
using std::nth_element;
using std::sort;

#include <string>
using std::string;
using std::to_string;

#include <sstream>
using std::istringstream;
using std::stringstream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <chrono>
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::time_point;

#include <conio.h>

#include <iterator>
using std::make_move_iterator;

#include <utility>
using std::move;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;
using std::filesystem::create_directories;

static const char output_file[] = "txt/rezultatai.txt"; // failo, į kurį išvedami rezultatų duomenys, direktorija/pavadinimas

extern bool ar_skaiciuoti_laika;
extern time_point<high_resolution_clock> pradzios_laikas;

extern string vardai[];
extern string pavardes[];

void timer_prad();
void timer_pab(string operacija);