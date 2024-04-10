# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/shangxin/esp/esp-idf/components/bootloader/subproject"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/tmp"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/src"
  "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/shangxin/esp-project/digital_twin_esp32c3/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
