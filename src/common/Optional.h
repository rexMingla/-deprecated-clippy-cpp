/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <stddef.h>

/**
 * @brief Class to allow optional objects that are either null or have a value.
 *
 *        Stupidly based on Google Guava (https://code.google.com/p/guava-libraries/wiki/UsingAndAvoidingNullExplained)
 *        rather than std lib or boost (really would make sense to have the interfaces similar). Also, ideally it would
 *        just use std lib, but this project can't be build with C++11 *sad face*.
 */
template <typename T>
class Optional
{
private:
  T data_;
  bool isAbsent_;

private:
  Optional(T& data) : data_(data), isAbsent_(false) { }
  Optional() : isAbsent_(true) { }

public:
  ~Optional() { }

  const T& get() const {
    return data_;
  }

  bool isAbsent() const {
    return isAbsent_;
  }

  bool isPresent() const {
    return !isAbsent_;
  }

  static Optional<T> of(T data) {
    return Optional<T>(data);
  }

  static Optional<T> absent() {
    return Optional<T>();
  }
};

#endif // OPTIONAL_H
