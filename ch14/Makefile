################ template makefile ##############
#mks - Feb 06, 2018

# Find C++ compiler
CXX = $(shell fltk-config --cxx)
CXX-DEBUG = $(shell fltk-config --cxx) -g

# Set the flags for compiler: 
CXXFLAGS = $(shell fltk-config --cxxflags) --no-warnings -Wall

# Find the libraries to link against 
#LINKFLTK = $(shell fltk-config --ldflags) // what's the difference between ldflags and ldstaticflags
LINKFLTK = $(shell fltk-config --ldstaticflags)
# LINKFLTK_GL is needed to close the graphics window - I think, it gives the mouse control on the graphics. 
LINKFLTK_GL = $(shell fltk-config --use-gl --ldstaticflags)
#LINKFLTK_IMG is used in a couple of functions. 
LINKFLTK_IMG = $(shell fltk-config --use-images --ldstaticflags)

# no need for any of these
# Possible steps to run after linking...
#STRIP      = strip
#POSTBUILD  = fltk-config --post # Required on OSX, does nothing on other platforms, so safe to call


# Define the target application 
all: project

# Define how to build the various object files...

graph.o: Graph.cpp Graph.h
	$(CXX) -c $< $(CXXFLAGS) -o graph.o

graph-g.o: Graph.cpp Graph.h
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o graph-g.o

gui.o: GUI.cpp GUI.h
	$(CXX) -c $< $(CXXFLAGS) -o gui.o
  
gui-g.o: GUI.cpp GUI.h
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o gui-g.o

simple_window.o: Simple_window.cpp Simple_window.h
	$(CXX) -c $< $(CXXFLAGS) -o simple_window.o

simple_window-g.o: Simple_window.cpp Simple_window.h
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o simple_window-g.o

window.o: Window.cpp Window.h
	$(CXX) -c $< $(CXXFLAGS) -o window.o

window-g.o: Window.cpp Window.h
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o window-g.o

point.o: Point.cpp Point.h 
	$(CXX) -c $< $(CXXFLAGS) -o point.o

point-g.o: Point.cpp Point.h 
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o point-g.o

main.o: main.cpp fltk.h
	$(CXX) -c $< $(CXXFLAGS) -o main.o

main-g.o: main.cpp fltk.h 
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o main-g.o

main-german.o: main-german.cpp
	$(CXX-DEBUG) -c $< $(CXXFLAGS) -o main-german.o

# Now link all the object files- it needs image support and open gl. Note that LINKFLTK is embedded inside LINKFLTK_IMG/_GL

project: main.o window.o simple_window.o graph.o gui.o point.o 
	$(CXX) -o $@  main.o window.o simple_window.o graph.o gui.o point.o  $(LINKFLTK_IMG) $(LINKFLTK_GL)

#german prof solution

german: main-german.o window.o simple_window.o graph.o gui.o point.o 
	$(CXX) -o $@  main-german.o window.o simple_window.o graph.o gui.o point.o  $(LINKFLTK_IMG) $(LINKFLTK_GL)

#debug build

debug: main-g.o window-g.o simple_window-g.o graph-g.o gui-g.o point-g.o 
	$(CXX-DEBUG) -o project-g main-g.o window-g.o simple_window-g.o graph-g.o gui-g.o point-g.o $(LINKFLTK_IMG) $(LINKFLTK_GL)

#clean 
clean:
	rm -f *.o project project-g
