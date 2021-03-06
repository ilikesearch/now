#include <chrono>
#include <iomanip>
#include <iostream>

#include "cxxopts.hpp"

using std::chrono::system_clock;

int main(int argc, char **argv) {
  cxxopts::Options opts("now");

  opts.add_options()(
      "f,format", "specify time format",
      cxxopts::value<std::string>()->default_value("%Y-%m-%d %X %a"),
      "<string>")("h,help", "print help and exit");

  cxxopts::ParseResult args;
  try {
    args = opts.parse(argc, argv);
  } catch (const cxxopts::OptionException &) {
    std::cout << opts.help() << std::endl;
    exit(-1);
  }

  if (args.count("help")) {
    std::cout << opts.help() << std::endl;
    exit(0);
  }

  auto time = system_clock::to_time_t(system_clock::now());
  auto format = args["format"].as<std::string>().c_str();
  auto formatted = std::put_time(std::localtime(&time), format);
  std::cout << formatted << std::endl;
}