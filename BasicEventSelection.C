// Code for basic event selection

#include "IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::basicEventSelection(float centralityCut){
    // Centrality cut
    return (centrality > centralityCut);
}
