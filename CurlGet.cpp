#include "CurlGet.hpp"

#include <assert.h>

CurlGet::CurlGet() : mRequestHandle(nullptr) {}

CurlGet::~CurlGet() {
  // don't allow destruction before waiting for result
  assert(!mRequestHandle);
}

std::future<CurlGet::Response> CurlGet::get(const std::string& str) {
  // allow only one ongoing operation per CurlGet instance
  assert(!mRequestHandle);
  mRequestHandle = curl_easy_init();

  curl_easy_setopt(mRequestHandle, CURLOPT_URL, str.c_str());
  curl_easy_setopt(mRequestHandle, CURLOPT_WRITEFUNCTION, CurlGet::writeFunctionDispatcher);
  curl_easy_setopt(mRequestHandle, CURLOPT_WRITEDATA, this);

  std::async(std::launch::async, &CurlGet::waitResponse, this);

  return mPromise.get_future();
}

void CurlGet::waitResponse() {
  curl_easy_perform(mRequestHandle);

  long responseCode;
  curl_easy_getinfo(mRequestHandle, CURLINFO_RESPONSE_CODE, &responseCode);

  curl_easy_cleanup(mRequestHandle);
  mRequestHandle = nullptr;

  mPromise.set_value({responseCode, mResponseData});
}

size_t CurlGet::writeFunctionDispatcher(void *buffer, size_t sz, size_t n, void *curlGet) {
  return static_cast<CurlGet*>(curlGet)->writeFunction(buffer, sz, n);
}

size_t CurlGet::writeFunction(void *ptr, size_t size, size_t nmemb) {
  mResponseData.append((char*)ptr, size * nmemb);
  return size * nmemb;
}
