// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


namespace ez_open_app {


template <class T>
class Singleton {
 public:
  static T* Instance() {
    static T inst;
    return &inst;
  }

  Singleton() = delete;
  ~Singleton() = delete;
  Singleton(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton& operator=(const Singleton &) = delete;
  Singleton& operator=(Singleton &&) = delete;
};


}  // namespace ez_open_app
