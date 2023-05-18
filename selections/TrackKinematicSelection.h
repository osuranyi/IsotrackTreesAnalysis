bool IsotrackTreesAnalysis::trackKinematicSelection(int id){
    // Track momentum and cut
    if(m_tr_pt[id] < PT_CUT || fabs(m_tr_cemc_eta[id]) > 1.0){
        return false;
    }
    else{
        return true;
    }
}

