# Install script for directory: /cefs/higgs/pzlai/JES/Product/Product_zz_sl_240

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/lib:/afs/ihep.ac.cn/users/m/manqi/ArborV3Deve/SL6/Marlin/v01-05/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcio/v02-04-03/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gear/v01-04/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CLHEP/2.1.3.1/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ilcutil/v01-01/lib:/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6-gcc49/external/ROOT/5.34.18/install/lib")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser/lib/libmWMeasurement.so.0.0.0"
    "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser/lib/libmWMeasurement.so.0.0"
    "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser/lib/libmWMeasurement.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmWMeasurement.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/afs/ihep.ac.cn/users/m/manqi/ArborV3Deve/SL6/Marlin/v01-05/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcio/v02-04-03/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gear/v01-04/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CLHEP/2.1.3.1/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ilcutil/v01-01/lib:/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6-gcc49/external/ROOT/5.34.18/install/lib::::::::::::::::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/lib:/afs/ihep.ac.cn/users/m/manqi/ArborV3Deve/SL6/Marlin/v01-05/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcio/v02-04-03/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gear/v01-04/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CLHEP/2.1.3.1/lib:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ilcutil/v01-01/lib:/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6-gcc49/external/ROOT/5.34.18/install/lib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
