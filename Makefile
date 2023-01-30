CC = g++
ROOTCONFIG = `root-config --libs --cflags`
BOOST = -L/opt/sphenix/core/boost/lib -lboost_program_options
SOURCES = IsotrackTreesAnalysis.C run.C
EXECUTABLE = ../build/run_analysis

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) $(ROOTCONFIG) -o $(EXECUTABLE) $(BOOST)
