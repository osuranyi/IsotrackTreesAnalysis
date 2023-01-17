// Code for basic event selection

const float CENTRALITY_CUT = 20.0;

bool IsotrackTreesAnalysis::basicEventSelection(){
    // Centrality cut
    return (centrality > CENTRALITY_CUT);
}
