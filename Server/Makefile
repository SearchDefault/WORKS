EXE = Server
SRC_DIR = ./src

SOURCES =  $(SRC_DIR)/main.cpp
SOURCES += $(SRC_DIR)/ImGUI/imgui.cpp $(SRC_DIR)/ImGUI/imgui_demo.cpp $(SRC_DIR)/ImGUI/imgui_draw.cpp $(SRC_DIR)/ImGUI/imgui_tables.cpp $(SRC_DIR)/ImGUI/imgui_widgets.cpp
SOURCES += $(SRC_DIR)/Backends/imgui_impl_sdl.cpp $(SRC_DIR)/Backends/imgui_impl_opengl3.cpp
SOURCES += $(SRC_DIR)/ImPlot/implot.cpp $(SRC_DIR)/ImPlot/implot_items.cpp $(SRC_DIR)/ImPlot/implot_demo.cpp
SOURCES += $(SRC_DIR)/Network/TcpServer.cpp $(SRC_DIR)/Network/TcpServerClient.cpp ##$(SRC_DIR)/Network/TcpClient.cpp ##Delete TcpClient MB
SOURCES += $(SRC_DIR)/Renderer/Renderer.cpp $(SRC_DIR)/Renderer/FileManager.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -I$(SRC_DIR)/ImGUI -I$(SRC_DIR)/backends -I$(SRC_DIR)/ImPlot -I$(SRC_DIR)/Network -I$(SRC_DIR)/Renderer
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
    ECHO_MESSAGE = "MinGW"
    LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`

    CXXFLAGS += `pkg-config --cflags sdl2`
    CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------


%.o:$(SRC_DIR)/Backends/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

%.o:$(SRC_DIR)/ImGUI/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<
	
%.o:$(SRC_DIR)/ImPlot/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

%.o:$(SRC_DIR)/Network/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

%.o:$(SRC_DIR)/Renderer/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<
	
%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<
	
all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -g -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
