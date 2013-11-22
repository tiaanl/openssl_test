// OpenSSLTest

#ifndef SCOPED_OPENSSL_H_
#define SCOPED_OPENSSL_H_

namespace net {

template <typename T, void(*Destructor)(T*)>
class ScopedOpenSSL {
public:
  ScopedOpenSSL() : _ptr(nullptr) {}

  explicit ScopedOpenSSL(T* ptr) : _ptr(ptr) {}

  ~ScopedOpenSSL() {
    Reset(nullptr);
  }

  T* Get() const { return _ptr; }

  T* Release() {
    T* ptr = _ptr;
    _ptr = nullptr;
    return ptr;
  }

  void Reset(T* ptr) {
    if (ptr != _ptr) {
      if (_ptr)
        (*Destructor)(_ptr);
      _ptr = ptr;
    }
  }

private:
  T* _ptr;

  ScopedOpenSSL(const ScopedOpenSSL&);
  ScopedOpenSSL& operator=(const ScopedOpenSSL&);
};

}  // namespace net

#endif  // SCOPED_OPENSSL_H_
