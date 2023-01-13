# IsotrackTreesAnalysis

Usage:

1. Start the ROOT command prompt
2. Issue ".L IsotrackTreesAnalysis.C"
3. Issue ".L BasicEventSelection.C"
4. Issue the same for additional modules
5. Create an instance of "IsotrackTreesAnalysis" C: "IsotrackTreesAnalysis a"
6. Then the "a.Loop()" runs over all events

Add any new modules in the "processEvent()" functions.
A module with a single function should be added as a member function to the IsotrackTreesAnalysis class. The definition of the function should go in a separate \*.C file - it is not needed to include .h file.
