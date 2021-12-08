# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/interprocess
    REF boost-1.77.0
    SHA512 59ccd15b58a8ba343ca4c009a3c6a59a06248d7f9829dbb355320d7184b6476dcbf98d68853fe9d2522e7d8500e39ce36073fde1f17cbab01003abb8e5d2d425
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})