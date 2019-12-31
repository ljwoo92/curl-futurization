# Example C++ Future wrapper for Curl

Example project used to study how to wrap libcurl interface with
C++ Future.

Example provides minimalistic API for making a HTTP GET request.

``` c++
CurlGet curlGet;
auto future = curlGet.get("http://www.google.com");
auto response = future.get();
std::cout << "Response code " << response.first << std::endl;
// "response.second" contains actual response as std::string
```

## Usage

### Prerequisites

Needs libcurl, its development headers and cmake. Can be installed on Debian-like
systems with

``` sh
$ apt-get install libcurl4 libcurl4-openssl-dev cmake
```

You also need a C++ compiler.

### Compile and run

``` sh
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./cpp-async
```
