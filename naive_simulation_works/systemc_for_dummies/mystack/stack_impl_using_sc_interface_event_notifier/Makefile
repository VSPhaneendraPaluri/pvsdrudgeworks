CC			=	g++
CXXFLAGS		=	-g -O2
LIBS			=	-lsystemc
EXECUTABLE		=	exec

all	:	${EXECUTABLE}

${EXECUTABLE}	: *.o
		@echo "Linking all the object files..."
		${CC} ${CXXFLAGS} -o $@ $< -L${SYSTEMC_INSTALL_PATH}/lib-linux64/ ${LIBS}

%.o	:	%.cpp 
		@echo "Compiling the classes files... "
		${CC} ${CXXFLAGS} -c $^ -I${SYSTEMC_INSTALL_PATH}/include/

.PHONY	:	clean
clean	:
		@echo "Cleaning the folder... "
		rm -f ${EXECUTABLE} *.o *.h.* *.*~

