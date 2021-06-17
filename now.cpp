#include <chrono>
#include <iomanip>
#include <iostream>

#include "cxxopts.hpp"

using std::chrono::system_clock;

auto parse_args(cxxopts::Options &opts, int argc, char **argv)
{
  try
  {
    return opts.parse(argc, argv);
  }
  catch (const cxxopts::OptionException &)
  {
    std::cout << opts.help() << std::endl;
    exit(-1);
  }
}

int main(int argc, char **argv)
{
  cxxopts::Options opts("now");

  opts.add_options()(
      "f,format", "specify time format",
      cxxopts::value<std::string>()->default_value("%Y-%m-%d %X %a"),
      "<string>")("h,help", "print help and exit");

  auto args = parse_args(opts, argc, argv);

  if (args.count("help"))
  {
    std::cout << opts.help() << std::endl;
    exit(0);
  }

  auto time = system_clock::to_time_t(system_clock::now());
  auto format = args["format"].as<std::string>().c_str();
  auto formatted = std::put_time(std::localtime(&time), format);
  std::cout << formatted << std::endl;
}