#pragma once

#include <curl/curl.h>
#include <future>
#include <string>

struct CurlGet {
  using Response = std::pair<long, std::string>;

  CurlGet();

  ~CurlGet();

  std::future<Response> get(const std::string& str);

private:
  void waitResponse();

  static size_t writeFunctionDispatcher(void *buffer, size_t sz, size_t n, void *curlGet);

  size_t writeFunction(void *ptr, size_t size, size_t nmemb);

  CURL* mRequestHandle;
  std::promise<Response> mPromise;
  std::string mResponseData;
};
