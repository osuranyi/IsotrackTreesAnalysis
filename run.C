#include "IsotrackTreesAnalysis.h"

int main(){
    //gROOT->LoadMacro("../src/IsotrackTreesAnalysis.C");
    //gROOT->LoadMacro("../src/BasicEventSelection.C");
    //gROOT->LoadMacro("../src/BasicTrackSelection.C");

    IsotrackTreesAnalysis a;

    a.Loop();
}
