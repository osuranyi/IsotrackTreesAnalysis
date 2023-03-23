#pragma once
#include "../IsotrackTreesAnalysis.h"

void IsotrackTreesAnalysis::initZeroShowerEnergyModule(){
    graphZeroShower = new TEfficiency("zero_shower_efficiency",";p [GeV];P(E=0)",5,0.5,3.0);
}

void IsotrackTreesAnalysis::zeroShowerEnergyModule(int id, float cemcEnergy, float ihcalEnergy, float ohcalEnergy){
    //std::cout << m_tr_p[id] << "\t" << (int)((cemcEnergy < 0.1) && (ihcalEnergy < 0.1) && (ohcalEnergy < 0.1)) << std::endl;
    graphZeroShower->Fill((cemcEnergy < 0.00001) && (ihcalEnergy < 0.00001) && (ohcalEnergy < 0.00001), m_tr_p[id]);
}
