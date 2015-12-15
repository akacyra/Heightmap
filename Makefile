CXX=g++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=
CXX_FLAGS := -Wall -MMD -std=c++11 -g
TARGET := heightmap 

all: dirs $(TARGET)

profile: CXX_FLAGS += -pg
profile: LD_FLAGS += -pg
profile: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: dirs clean

dirs: 
	mkdir -p obj

clean:
	rm -f $(TARGET) $(OBJ_FILES) $(OBJ_FILES:.o=.d)

# Automatic dependency graph generation with -MMD
-include $(OBJ_FILES:.o=.d)
