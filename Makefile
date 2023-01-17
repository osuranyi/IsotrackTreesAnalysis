CC = g++
ROOTCONFIG = `root-config --libs --cflags`
SOURCES = IsotrackTreesAnalysis.C BasicEventSelection.C BasicTrackSelection.C run.C
EXECUTABLE = ../build/run_analysis

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) $(ROOTCONFIG) -o $(EXECUTABLE)
