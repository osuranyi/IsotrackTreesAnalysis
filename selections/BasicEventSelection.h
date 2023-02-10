// Code for basic event selection

#include "../IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::basicEventSelection(){
    // Centrality cut
    if (!USE_CENTRALITY) { return true; } 
    return (centrality > CENTRALITY_CUT);
}
