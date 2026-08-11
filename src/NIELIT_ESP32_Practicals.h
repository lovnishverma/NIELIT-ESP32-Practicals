/*
  NIELIT ESP32 Practicals Library
  --------------------------------
  Course helper library for NIELIT Ropar ESP32 practicals.

  This library primarily provides a single installable package containing
  all practical examples (2.1 - 2.15). Install this ZIP using:
    Arduino IDE -> Sketch -> Include Library -> Add .ZIP Library

  After installation:
    File -> Examples -> NIELIT ESP32 Practicals

  The examples may require third-party libraries listed in README.md.
*/

#ifndef NIELIT_ESP32_PRACTICALS_H
#define NIELIT_ESP32_PRACTICALS_H

#define NIELIT_ESP32_PRACTICALS_VERSION "1.0.0"

#include <Arduino.h>

namespace NIELIT {

inline void printLibraryInfo(Stream &out = Serial) {
  out.println(F("NIELIT ESP32 Practicals Library"));
  out.print(F("Version: "));
  out.println(F(NIELIT_ESP32_PRACTICALS_VERSION));
}

inline void printPracticalHeader(Stream &out, const char *number, const char *title) {
  out.println();
  out.println(F("========================================"));
  out.print(F("NIELIT ESP32 Practical "));
  out.println(number);
  out.println(title);
  out.println(F("========================================"));
}

} // namespace NIELIT

#endif
