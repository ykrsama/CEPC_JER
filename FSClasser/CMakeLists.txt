########################################################
# cmake file for building Marlin example Package
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################


# project name
#PROJECT( FSClasser )


# project version
SET( FSClasser_VERSION_MAJOR 0 )
SET( FSClasser_VERSION_MINOR 1 )
SET( FSClasser_VERSION_PATCH 0 )


### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES )
FIND_PACKAGE( ROOT REQUIRED )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )


FIND_PACKAGE( Marlin 1.0 REQUIRED ) # minimum required Marlin version
FIND_PACKAGE( FastJet 2.4.2 REQUIRED ) # minimum required Marlin version
FIND_PACKAGE( MarlinKinfit 0.1.2 REQUIRED ) # minimum required Marlin version
#FIND_PACKAGE( LCFIPlus 0.5.2 REQUIRED ) # minimum required Marlin version

INCLUDE_DIRECTORIES( ${Marlin_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${MarlinKinfit_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${FastJet_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${LCFIPlus_INCLUDE} )


LINK_LIBRARIES( ${Marlin_LIBRARIES} )
ADD_DEFINITIONS( ${Marlin_DEFINITIONS} )

LINK_LIBRARIES( ${MarlinKinfit_LIBRARIES} )
LINK_LIBRARIES( ${FastJet_LIBRARIES} )

INCLUDE_DIRECTORIES( ${ROOT_INCLUDE_DIRS} )

# optional package
#FIND_PACKAGE( AIDA )
#IF( AIDA_FOUND )
#    INCLUDE_DIRECTORIES( ${AIDA_INCLUDE_DIRS} )
#    LINK_LIBRARIES( ${AIDA_LIBRARIES} )
#    ADD_DEFINITIONS( "-DMARLIN_USE_AIDA" )
#    MESSAGE( STATUS "AIDA -- found" )
#ELSE()
#    MESSAGE( STATUS "AIDA -- not found" )
#ENDIF()

FIND_PACKAGE( GSL 1.12 REQUIRED )
INCLUDE_DIRECTORIES( ${GSL_INCLUDE_DIRS} )
LINK_LIBRARIES( ${GSL_LIBRARIES} )


#FIND_PACKAGE( LCFIPlus ) # minimum required Marlin version

### DOCUMENTATION ###########################################################

OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" OFF )

IF( INSTALL_DOC AND EXISTS "${PROJECT_SOURCE_DIR}/doc/CMakeLists.txt" )
    ADD_SUBDIRECTORY( ./doc )
ENDIF()



### LIBRARY #################################################################

# definitions to pass to the compiler
ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-unused-variable -Wwrite-strings -Wno-unused-but-set-variable " )
ADD_DEFINITIONS( "-Wno-long-long -fvar-tracking-assignments-toggle" )

# include directories
INCLUDE_DIRECTORIES( ./include )
#INSTALL_DIRECTORY( ./include DESTINATION . FILES_MATCHING PATTERN "*.h" )

# add library
AUX_SOURCE_DIRECTORY( ./src library_sources )
ADD_SHARED_LIBRARY( FSClasser ${library_sources} )
INSTALL_SHARED_LIBRARY( FSClasser DESTINATION lib )

# display some variables and write them to cache
DISPLAY_STD_VARIABLES()

#SET( Marlin_DEPENDS_INCLUDE_DIRS /cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Framework/LCIO/02-04-03/include;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Simulation/GEAR/01-04/include;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Simulation/GEAR/01-04/include/gear;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/external/CLHEP/2.1.3.1/install/include;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Framework/ILCUTIL/01-01/include;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Analysis/MarlinKinfit/00-01-02/include;/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-sl6/cepcsoft/0.1.0-b7/Service/FastJet/2.4.2/install/include )
