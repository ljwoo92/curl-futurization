#include <iostream>

#include "CurlGet.hpp"

int main(int argc, char** argv)
{
  CurlGet curlGet;
  auto future = curlGet.get("http://www.google.com");
  auto response = future.get();
  std::cout << "Response code " << response.first << std::endl;
}
