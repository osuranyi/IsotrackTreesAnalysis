// Code for basic event selection

#include "../IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::basicEventSelection(){
    // Centrality cut
    return (centrality > CENTRALITY_CUT);
}
