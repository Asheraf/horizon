# - Find Crypto++

if(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARIES)
  set(CRYPTOPP_FOUND TRUE)
  message(STATUS "Found Crypto++: ${CRYPTOPP_INCLUDE_DIR}, ${CRYPTOPP_LIBRARIES}")

else()
  find_path(CRYPTOPP_INCLUDE_DIR cryptlib.h
    /usr/include/crypto++
    /usr/include/cryptopp
    /usr/local/include/crypto++
    /usr/local/include/cryptopp
    /opt/local/include/crypto++
    /opt/local/include/cryptopp
    $ENV{SystemDrive}/Crypto++/include
    C:/vcpkg/installed/x64-windows/include/cryptopp
    C:/vcpkg/installed/x86-windows/include/cryptopp
  )

  find_library(CRYPTOPP_LIBRARIES NAMES cryptopp cryptopp-static
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      $ENV{SystemDrive}/Crypto++/lib
      C:/vcpkg/installed/x64-windows/lib
      C:/vcpkg/installed/x86-windows/lib
  )

  if(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARIES)
    set(CRYPTOPP_FOUND TRUE)
    message(STATUS "Found Crypto++: ${CRYPTOPP_INCLUDE_DIR}, ${CRYPTOPP_LIBRARIES}")
  else()
    set(CRYPTOPP_FOUND FALSE)
    message(STATUS "Crypto++ not found.")
  endif()

  mark_as_advanced(CRYPTOPP_INCLUDE_DIR CRYPTOPP_LIBRARIES)
endif()
