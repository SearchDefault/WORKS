EXE = Server
SRC_DIR = ./src

SOURCES =  $(SRC_DIR)/main.cpp
SOURCES += $(SRC_DIR)/ImGUI/imgui.cpp $(SRC_DIR)/ImGUI/imgui_demo.cpp $(SRC_DIR)/ImGUI/imgui_draw.cpp $(SRC_DIR)/ImGUI/imgui_tables.cpp $(SRC_DIR)/ImGUI/imgui_widgets.cpp
SOURCES += $(SRC_DIR)/Backends/imgui_impl_sdl.cpp $(SRC_DIR)/Backends/imgui_impl_opengl3.cpp
SOURCES += $(SRC_DIR)/ImPlot/implot.cpp $(SRC_DIR)/ImPlot/implot_items.cpp $(SRC_DIR)/ImPlot/implot_demo.cpp
SOURCES += $(SRC_DIR)/Network/TcpServer.cpp $(SRC_DIR)/Network/TcpServerClient.cpp ##$(SRC_DIR)/Network/TcpClient.cpp ##Delete TcpClient MB
SOURCES += $(SRC_DIR)/Renderer/Renderer.cpp $(SRC_DIR)/Renderer/FileManager.cpp
SOURCES += $(SRC_DIR)/ImGuiFileDialog/ImGuiFileDialog.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
LINUX_GL_LIBS = -lGL

CXXFLAGS = -I$(SRC_DIR)/ImGUI -I$(SRC_DIR)/backends -I$(SRC_DIR)/ImPlot -I$(SRC_DIR)/Network -I$(SRC_DIR)/Renderer
CXXFLAGS += -Wall -Wformat
LIBS =
mode = Debug

ifeq ($(mode), Debug)
	CXXFLAGS += -g
endif

ifeq ($(mode), Reliase)
	CXXFLAGS += -O3
endif

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(OS), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	CXX = g++
	LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Win)
	ECHO_MESSAGE = "Windows"
	CXX = x86_64-w64-mingw32-g++
	EXE = Server.exe
	LIBS += -lSDL2 -w -lws2_32 -lwsock32 -lgdi32 -lopengl32 -limm32 -lmingw32 -static-libgcc -static-libstdc++ -Wl,-subsystem,windows

	CXXFLAGS += -lSDL2 -w -lws2_32 -Wl,-subsystem,windows
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------


%.o:$(SRC_DIR)/Backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(SRC_DIR)/ImGUI/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.o:$(SRC_DIR)/ImPlot/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(SRC_DIR)/Network/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(SRC_DIR)/Renderer/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(SRC_DIR)/ImGuiFileDialog/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
