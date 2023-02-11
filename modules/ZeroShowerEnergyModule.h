#pragma once
#include "../IsotrackTreesAnalysis.h"

void IsotrackTreesAnalysis::initZeroShowerEnergyModule(){
    graphZeroShower = new TEfficiency("zero_shower_efficiency",";p [GeV];P(E=0) [%]",5,0.5,3.0);
}

void IsotrackTreesAnalysis::zeroShowerEnergyModule(int id, float cemcEnergy, float ihcalEnergy, float ohcalEnergy){
    graphZeroShower->Fill(m_tr_p[id], (cemcEnergy < 0.1) && (ihcalEnergy < 0.1) && (ohcalEnergy < 0.1) );

}