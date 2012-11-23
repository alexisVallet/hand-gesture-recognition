#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pClearHand.o \
	${OBJECTDIR}/StatisticalClassifier.o \
	${OBJECTDIR}/Classifier.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../pandore/lib -L../opencv/lib ../opencv/lib/libopencv_calib3d243.dll.a ../opencv/lib/libopencv_contrib243.dll.a ../opencv/lib/libopencv_core243.dll.a ../opencv/lib/libopencv_features2d243.dll.a ../opencv/lib/libopencv_flann243.dll.a ../opencv/lib/libopencv_gpu243.dll.a ../opencv/lib/libopencv_highgui243.dll.a ../opencv/lib/libopencv_imgproc243.dll.a ../opencv/lib/libopencv_legacy243.dll.a ../opencv/lib/libopencv_ml243.dll.a ../opencv/lib/libopencv_nonfree243.dll.a ../opencv/lib/libopencv_objdetect243.dll.a ../opencv/lib/libopencv_photo243.dll.a ../opencv/lib/libopencv_stitching243.dll.a ../opencv/lib/libopencv_ts243.a ../opencv/lib/libopencv_video243.dll.a ../opencv/lib/libopencv_videostab243.dll.a -lpandore

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f1.exe

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_calib3d243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_contrib243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_core243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_features2d243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_flann243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_gpu243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_highgui243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_imgproc243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_legacy243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_ml243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_nonfree243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_objdetect243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_photo243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_stitching243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_ts243.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_video243.dll.a

${TESTDIR}/TestFiles/f1.exe: ../opencv/lib/libopencv_videostab243.dll.a

${TESTDIR}/TestFiles/f1.exe: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../opencv/include -I../pandore/include -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pClearHand.o: pClearHand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../opencv/include -I../pandore/include -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/pClearHand.o pClearHand.cpp

${OBJECTDIR}/StatisticalClassifier.o: StatisticalClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../opencv/include -I../pandore/include -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/StatisticalClassifier.o StatisticalClassifier.cpp

${OBJECTDIR}/Classifier.o: Classifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../opencv/include -I../pandore/include -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Classifier.o Classifier.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f1.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
