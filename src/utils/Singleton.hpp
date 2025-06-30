#pragma once

namespace Utils {
template <typename T> class Singleton {
  public:
    static T& GetInstance() {
        static T singleton;
        return singleton;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

  private:
    Singleton() = default;
    ~Singleton() = default;
};
} // namespace Utils
