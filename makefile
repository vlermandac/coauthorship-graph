PRJ_NAME := CoauthorGraphAnalyze
CC = g++-12

### Paths ###
PRJ_ROOT        := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PRJ_SOURCE_CODE := ${PRJ_ROOT}/src
PRJ_OUTPUT_DIR  := ${PRJ_ROOT}/builds
PRJ_OBJECTS_DIR := ${PRJ_OUTPUT_DIR}/objects
PRJ_TESTS_DIR 	:= ${PRJ_ROOT}/tests
PRJ_TCASES_DIR	:= ${PRJ_TESTS_DIR}/test_cases
INCLUDE_DIR 		:= ${PRJ_SOURCE_CODE}/include

### Derived Variables ###
CPP_SRC_FILES 		:= $(shell find -L $(PRJ_SOURCE_CODE) -type f -name "*.cpp"  -print)                # All C++ files
CPP_OBJECTS   		:= $(patsubst $(PRJ_SOURCE_CODE)/%.cpp,$(PRJ_OBJECTS_DIR)/%.o, $(CPP_SRC_FILES))    # All C++ objects
T_SRC_FILES 			:= $(shell find -L $(INCLUDE_DIR) -type f -name "*.cpp"  -print) $(PRJ_TESTS_DIR)/tests_main.cpp 

### Flags ###
CPP_FLAGS 				:= -std=c++17 -O2 -g#$(shell tr '\n' ' ' < compile_flags.txt)
EXTERNAL_LIBS 		:= -lpugixml -pthread
INCLUDES        	+= -I${INCLUDE_DIR}

### Misc ###
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

### Targets ###
all: test $(CPP_OBJECTS)
	@echo "Executing target '$@' for project '${PRJ_NAME}'"
	@$(CC) -o ${PRJ_OUTPUT_DIR}/${PRJ_NAME} $(CPP_OBJECTS) $(EXTERNAL_LIBS)
	@chmod +x ${PRJ_ROOT}/run_analysis
	@echo "Finished executing the target '$@' for project '$(PRJ_NAME)'"

${PRJ_OBJECTS_DIR}/%.o : $(PRJ_SOURCE_CODE)/%.cpp
	@echo "Building '$<' for project '${PRJ_NAME}'"
	@mkdir -p $(@D)
	@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@
	@echo "Built '$<' for project '${PRJ_NAME}'"

clean: 
	@echo "Executing target '$@' for project '${PRJ_NAME}'"
	rm -rf ${PRJ_OBJECTS_DIR}
	@echo "Finished cleaning the target '$@' for project '${PRJ_NAME}'"

test: $(T_SRC_FILES)
	@$(CC) $^ $(CPP_FLAGS) $(INCLUDES) $(EXTERNAL_LIBS) -o $(PRJ_TESTS_DIR)/run
	@flag=0; \
	for num in 1 2 3 4; do \
		$(PRJ_TESTS_DIR)/run $(PRJ_TCASES_DIR)/test$$num/input.in > temp; \
		if diff -wbB temp $(PRJ_TCASES_DIR)/test$$num/output.out >/dev/null; then \
			echo "$(GREEN)Test $$num passed $(NC)✅"; \
		else \
			echo "$(RED)Test $$num failed $(NC)❌"; \
			flag=1; fi; \
		rm temp; \
	done; \
	rm $(PRJ_TESTS_DIR)/run; \
	if [ $$flag -eq 0 ]; then \
		echo "\n$(GREEN)All tests passed ! $(NC)✅ \n"; \
	else \
		echo "$(RED)Test $$num failed $(NC)❌"; \
		exit 1; \
	fi

