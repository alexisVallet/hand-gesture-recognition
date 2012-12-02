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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Pfisher.o \
	${OBJECTDIR}/utilsFunctions.o \
	${OBJECTDIR}/ClassifieurDistHistogramm.o \
	${OBJECTDIR}/ClassifieursProfils.o \
	${OBJECTDIR}/Crop.o \
	${OBJECTDIR}/main.o \
<<<<<<< Updated upstream
	${OBJECTDIR}/HandDirection.o \
	${OBJECTDIR}/ClassifieurDistEuclidienne.o \
	${OBJECTDIR}/pClearHand.o \
	${OBJECTDIR}/_ext/603711641/Segmentation.o \
	${OBJECTDIR}/StatisticalClassifier.o \
=======
	${OBJECTDIR}/Crop.o \
	${OBJECTDIR}/HandDirection.o \
	${OBJECTDIR}/ClassifieurDistEuclidienne.o \
	${OBJECTDIR}/newfile.o \
	${OBJECTDIR}/pClearHand.o \
	${OBJECTDIR}/TrainableClassifier.o \
>>>>>>> Stashed changes
	${OBJECTDIR}/RadialHistogram.o \
	${OBJECTDIR}/ConvexityClassifier.o \
	${OBJECTDIR}/RadialHistogramClassifier.o \
	${OBJECTDIR}/Classifier.o \
	${OBJECTDIR}/rotateHand.o \
	${OBJECTDIR}/convert.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
<<<<<<< Updated upstream
=======
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition \
>>>>>>> Stashed changes
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Pfisher.o: Pfisher.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Pfisher.o Pfisher.cpp

${OBJECTDIR}/utilsFunctions.o: utilsFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/utilsFunctions.o utilsFunctions.cpp

${OBJECTDIR}/ClassifieurDistHistogramm.o: ClassifieurDistHistogramm.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieurDistHistogramm.o ClassifieurDistHistogramm.cpp

${OBJECTDIR}/ClassifieursProfils.o: ClassifieursProfils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieursProfils.o ClassifieursProfils.cpp

${OBJECTDIR}/Crop.o: Crop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Crop.o Crop.cpp

<<<<<<< Updated upstream
${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp
=======
${OBJECTDIR}/Crop.o: Crop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Crop.o Crop.cpp
>>>>>>> Stashed changes

${OBJECTDIR}/HandDirection.o: HandDirection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HandDirection.o HandDirection.cpp

${OBJECTDIR}/ClassifieurDistEuclidienne.o: ClassifieurDistEuclidienne.cpp 
<<<<<<< Updated upstream
=======
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieurDistEuclidienne.o ClassifieurDistEuclidienne.cpp

${OBJECTDIR}/newfile.o: newfile.cpp 
>>>>>>> Stashed changes
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieurDistEuclidienne.o ClassifieurDistEuclidienne.cpp

${OBJECTDIR}/pClearHand.o: pClearHand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/pClearHand.o pClearHand.cpp

<<<<<<< Updated upstream
${OBJECTDIR}/_ext/603711641/Segmentation.o: /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/Segmentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/603711641
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/603711641/Segmentation.o /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/Segmentation.cpp

${OBJECTDIR}/StatisticalClassifier.o: StatisticalClassifier.cpp 
=======
${OBJECTDIR}/TrainableClassifier.o: TrainableClassifier.cpp 
>>>>>>> Stashed changes
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TrainableClassifier.o TrainableClassifier.cpp

${OBJECTDIR}/RadialHistogram.o: RadialHistogram.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/RadialHistogram.o RadialHistogram.cpp

${OBJECTDIR}/ConvexityClassifier.o: ConvexityClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ConvexityClassifier.o ConvexityClassifier.cpp

${OBJECTDIR}/RadialHistogramClassifier.o: RadialHistogramClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/RadialHistogramClassifier.o RadialHistogramClassifier.cpp

${OBJECTDIR}/Classifier.o: Classifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Classifier.o Classifier.cpp

${OBJECTDIR}/rotateHand.o: rotateHand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/rotateHand.o rotateHand.cpp

${OBJECTDIR}/convert.o: convert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/convert.o convert.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/classifieurDecodeurTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/ConversionTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/HandDirectionTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/RadialHistogramClassifierTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/RadialHistogramTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/tests/rotateHandTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

<<<<<<< Updated upstream
${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition: ${TESTDIR}/_ext/549880278/SegmentationTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition $^ ${LDLIBSOPTIONS} 

=======
>>>>>>> Stashed changes

${TESTDIR}/tests/classifieurDecodeurTest.o: tests/classifieurDecodeurTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/classifieurDecodeurTest.o tests/classifieurDecodeurTest.cpp


${TESTDIR}/tests/ConversionTest.o: tests/ConversionTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ConversionTest.o tests/ConversionTest.cpp


${TESTDIR}/tests/HandDirectionTest.o: tests/HandDirectionTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/HandDirectionTest.o tests/HandDirectionTest.cpp


${TESTDIR}/tests/RadialHistogramClassifierTest.o: tests/RadialHistogramClassifierTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/RadialHistogramClassifierTest.o tests/RadialHistogramClassifierTest.cpp


${TESTDIR}/tests/RadialHistogramTest.o: tests/RadialHistogramTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/RadialHistogramTest.o tests/RadialHistogramTest.cpp


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${TESTDIR}/tests/rotateHandTest.o: tests/rotateHandTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/rotateHandTest.o tests/rotateHandTest.cpp


<<<<<<< Updated upstream
${TESTDIR}/_ext/549880278/SegmentationTest.o: /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/SegmentationTest/SegmentationTest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/549880278
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/_ext/549880278/SegmentationTest.o /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/SegmentationTest/SegmentationTest.cpp


${OBJECTDIR}/Pfisher_nomain.o: ${OBJECTDIR}/Pfisher.o Pfisher.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Pfisher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Pfisher_nomain.o Pfisher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Pfisher.o ${OBJECTDIR}/Pfisher_nomain.o;\
	fi

=======
>>>>>>> Stashed changes
${OBJECTDIR}/utilsFunctions_nomain.o: ${OBJECTDIR}/utilsFunctions.o utilsFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utilsFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/utilsFunctions_nomain.o utilsFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utilsFunctions.o ${OBJECTDIR}/utilsFunctions_nomain.o;\
	fi

${OBJECTDIR}/ClassifieurDistHistogramm_nomain.o: ${OBJECTDIR}/ClassifieurDistHistogramm.o ClassifieurDistHistogramm.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ClassifieurDistHistogramm.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieurDistHistogramm_nomain.o ClassifieurDistHistogramm.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ClassifieurDistHistogramm.o ${OBJECTDIR}/ClassifieurDistHistogramm_nomain.o;\
	fi

${OBJECTDIR}/ClassifieursProfils_nomain.o: ${OBJECTDIR}/ClassifieursProfils.o ClassifieursProfils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ClassifieursProfils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieursProfils_nomain.o ClassifieursProfils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ClassifieursProfils.o ${OBJECTDIR}/ClassifieursProfils_nomain.o;\
	fi

${OBJECTDIR}/Crop_nomain.o: ${OBJECTDIR}/Crop.o Crop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Crop.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Crop_nomain.o Crop.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Crop.o ${OBJECTDIR}/Crop_nomain.o;\
	fi

<<<<<<< Updated upstream
${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
=======
${OBJECTDIR}/Crop_nomain.o: ${OBJECTDIR}/Crop.o Crop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Crop.o`; \
>>>>>>> Stashed changes
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
<<<<<<< Updated upstream
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
=======
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Crop_nomain.o Crop.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Crop.o ${OBJECTDIR}/Crop_nomain.o;\
>>>>>>> Stashed changes
	fi

${OBJECTDIR}/HandDirection_nomain.o: ${OBJECTDIR}/HandDirection.o HandDirection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HandDirection.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HandDirection_nomain.o HandDirection.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HandDirection.o ${OBJECTDIR}/HandDirection_nomain.o;\
	fi

${OBJECTDIR}/ClassifieurDistEuclidienne_nomain.o: ${OBJECTDIR}/ClassifieurDistEuclidienne.o ClassifieurDistEuclidienne.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ClassifieurDistEuclidienne.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClassifieurDistEuclidienne_nomain.o ClassifieurDistEuclidienne.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ClassifieurDistEuclidienne.o ${OBJECTDIR}/ClassifieurDistEuclidienne_nomain.o;\
	fi

${OBJECTDIR}/newfile_nomain.o: ${OBJECTDIR}/newfile.o newfile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/newfile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/newfile_nomain.o newfile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/newfile.o ${OBJECTDIR}/newfile_nomain.o;\
	fi

<<<<<<< Updated upstream
${OBJECTDIR}/_ext/603711641/Segmentation_nomain.o: ${OBJECTDIR}/_ext/603711641/Segmentation.o /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/Segmentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/603711641
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/603711641/Segmentation.o`; \
=======
${OBJECTDIR}/pClearHand_nomain.o: ${OBJECTDIR}/pClearHand.o pClearHand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pClearHand.o`; \
>>>>>>> Stashed changes
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
<<<<<<< Updated upstream
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/603711641/Segmentation_nomain.o /C/Users/Quentin/Documents/GI05/IN54/Projet/in5x-gesture-recognition/gesture-recognition/Segmentation.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/603711641/Segmentation.o ${OBJECTDIR}/_ext/603711641/Segmentation_nomain.o;\
=======
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/pClearHand_nomain.o pClearHand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/pClearHand.o ${OBJECTDIR}/pClearHand_nomain.o;\
>>>>>>> Stashed changes
	fi

${OBJECTDIR}/TrainableClassifier_nomain.o: ${OBJECTDIR}/TrainableClassifier.o TrainableClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TrainableClassifier.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/TrainableClassifier_nomain.o TrainableClassifier.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TrainableClassifier.o ${OBJECTDIR}/TrainableClassifier_nomain.o;\
	fi

${OBJECTDIR}/RadialHistogram_nomain.o: ${OBJECTDIR}/RadialHistogram.o RadialHistogram.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/RadialHistogram.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/RadialHistogram_nomain.o RadialHistogram.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/RadialHistogram.o ${OBJECTDIR}/RadialHistogram_nomain.o;\
	fi

${OBJECTDIR}/ConvexityClassifier_nomain.o: ${OBJECTDIR}/ConvexityClassifier.o ConvexityClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ConvexityClassifier.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ConvexityClassifier_nomain.o ConvexityClassifier.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ConvexityClassifier.o ${OBJECTDIR}/ConvexityClassifier_nomain.o;\
	fi

${OBJECTDIR}/RadialHistogramClassifier_nomain.o: ${OBJECTDIR}/RadialHistogramClassifier.o RadialHistogramClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/RadialHistogramClassifier.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/RadialHistogramClassifier_nomain.o RadialHistogramClassifier.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/RadialHistogramClassifier.o ${OBJECTDIR}/RadialHistogramClassifier_nomain.o;\
	fi

${OBJECTDIR}/Classifier_nomain.o: ${OBJECTDIR}/Classifier.o Classifier.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Classifier.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Classifier_nomain.o Classifier.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Classifier.o ${OBJECTDIR}/Classifier_nomain.o;\
	fi

${OBJECTDIR}/rotateHand_nomain.o: ${OBJECTDIR}/rotateHand.o rotateHand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/rotateHand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/rotateHand_nomain.o rotateHand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/rotateHand.o ${OBJECTDIR}/rotateHand_nomain.o;\
	fi

${OBJECTDIR}/convert_nomain.o: ${OBJECTDIR}/convert.o convert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/convert.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/convert_nomain.o convert.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/convert.o ${OBJECTDIR}/convert_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
<<<<<<< Updated upstream
=======
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition || true; \
>>>>>>> Stashed changes
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gesture-recognition.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
