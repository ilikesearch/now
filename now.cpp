#include <chrono>
#include <iomanip>
#include <iostream>

#include "cxxopts.hpp"

using namespace std;
using namespace chrono;
using namespace cxxopts;

int main(int argc, char **argv) {
  Options opts("now");

  opts.add_options()(
      "f,format", "specify time format",
      value<string>()->default_value("%Y-%m-%d %X %a"),
      "<string>")("h,help", "print help and exit");

  ParseResult args;
  try {
    args = opts.parse(argc, argv);
  } catch (const OptionException &) {
    cout << opts.help() << endl;
    exit(-1);
  }

  if (args.count("help"))
  {
    cout << opts.help() << endl;
    exit(0);
  }

  auto time = system_clock::to_time_t(system_clock::now());
  auto format = args["format"].as<string>().c_str();
  auto formatted = put_time(localtime(&time), format);
  cout << formatted << endl;
}