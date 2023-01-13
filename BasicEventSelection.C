// Code for basic event selection

bool IsotrackTreesAnalysis::basicEventSelection(){
  bool trackSelection = (m_trkmult > 100);
  bool caloSelection = (m_clsmult_cemc > 500);

  return trackSelection && caloSelection;
}
