#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>

// find empty regions in tracking space of deltaR = 0.4 within eta = [-1.0,1.0] and phi = [-3.14,3.14]
// want to know the number of empty spaces in each centrality region 
// one thing we might need to check is that the distribution across the detector is the same for 
// the isolated tracks as for the empty locations 
// can then get the background energy in each of the detectors (emcal, ihcal, ohcal)
void IsotrackTreesAnalysis::initEmptyRegionModule() {
	// centrality regions 20-40,40-60,60-80,80-100
	int centrality_list[] = {30,50,70,90};
	histEmptyRegionNumber = new TH1F("empty_region_number","",4,20,100);
	histTruthEmptyRegionNumber = new TH1F("truth_empty_region_number","",4,20,100);
	histAcceptanceIndex = new TH2F("empty_alg_acc_index","",140,-0.5,139.5,630,-0.5,629.5);
	for (int i = 0; i < 4; i++) {
		histEmptyCenter[i] = new TH2F(TString::Format("empty_center_%d",centrality_list[i]),"",24,-1,1,64,-M_PI,M_PI);
		histEmptyEnergy[i] = new TH1F(TString::Format("empty_energy_%d",centrality_list[i]),"",5000,0,100);
		histEmptyNumber[i] = new TH1F(TString::Format("empty_number_%d",centrality_list[i]),"",500,0,500);
	}
	//histEmptyEvent = new TH2F("empty_event","",24,-1,1,64,-M_PI,M_PI);
}

void IsotrackTreesAnalysis::emptyRegionModule() {

    float circle_eta[140];
    float circle_phi[630];
    TVector3 v1, v2;
    bool empty;
    float centrality_array[] = {20,40,60,80,100};
    const std::set<int> neutral_pid = {-3322,-3212,-3122,-2112,-421,-14,-12,12,14,22,111,130,310,421,
                    2112,3122,3212,3322};

    for (int i = 0; i < 140; i++) {
    	circle_eta[i] = -0.695 + 0.01 * i;
    }
    for (int i = 0; i < 630; i++) {
    	circle_phi[i] = -3.1366 + 0.00997 * i;
    }
  
    std::random_device rd;
    std::mt19937 engine(rd());
    std::shuffle(std::begin(circle_eta), std::end(circle_eta), engine);
    std::shuffle(std::begin(circle_phi), std::end(circle_phi), engine);

    for (int i = 0; i < 140; i++) {
    	for (int j = 0; j < 630; j++) {
		    
		    v1.SetPtEtaPhi(1.0, circle_eta[i], circle_phi[j]);
		    empty = true;
		    
		    for(int k = 0; k < m_trkmult; k++){
		    	if (m_tr_outer_cemc_phi[k] > -998) {
		    		v2.SetPtEtaPhi(m_tr_pt[k], m_tr_cemc_eta[k], 0.5*(m_tr_cemc_phi[k]+m_tr_outer_cemc_phi[k]));
		    	} else {
		    		v2.SetPtEtaPhi(m_tr_pt[k], m_tr_cemc_eta[k], m_tr_cemc_phi[k]);
		    	}
		        if(v2.Pt() > MATCHED_PT_CUT && v1.DeltaR(v2) < MATCHED_DR_CUT){
		            empty = false;
		            break;
		        }
		    }
		    
		    if (empty) {
		    	histEmptyRegionNumber->Fill(centrality);
		    	histTruthEmptyRegionNumber->Fill(truth_centrality);
		    	histAcceptanceIndex->Fill(i,j);
		    	//std::cout << "indexes: " << i << " " << j << " circle_eta: " << circle_eta[i] << " " << " circle_phi: " << circle_phi[j] << std::endl;
		    	/*
		    	histEmptyEvent->Reset();
		    	for (int k = 0; k < m_trkmult; k++) {
		    		if (m_tr_pt[k] > MATCHED_PT_CUT) { 
			    		if (m_tr_outer_cemc_phi[k] > -998) {
			    			histEmptyEvent->Fill(m_tr_cemc_eta[k], 0.5*(m_tr_cemc_phi[k]+m_tr_outer_cemc_phi[k]));
			    			v2.SetPtEtaPhi(m_tr_pt[k], m_tr_cemc_eta[k], 0.5*(m_tr_cemc_phi[k]+m_tr_outer_cemc_phi[k]));
			    			std::cout << "track " << k << " dr = " << v1.DeltaR(v2) << " track_eta = " << m_tr_cemc_eta[k] << " track_phi = " << 0.5*(m_tr_cemc_phi[k]+m_tr_outer_cemc_phi[k]) << std::endl;
			    		} else {
			    			histEmptyEvent->Fill(m_tr_cemc_eta[k], m_tr_cemc_phi[k]);
			    			v2.SetPtEtaPhi(m_tr_pt[k], m_tr_cemc_eta[k], m_tr_cemc_phi[k]);
			    			std::cout << "track " << k << " dr = " << v1.DeltaR(v2) << " track_eta = " << m_tr_cemc_eta[k] << " track_phi = " << m_tr_cemc_phi[k] << std::endl;
			    		}
			    	}
		        }*/

		    	float e_nn = 0;
    			int n_nn = 0;
			    for (int k = 0; k < m_g4; k++) {
				    if (neutral_pid.find(m_g4_pid[k]) == neutral_pid.end() || m_g4_pt[k] < MATCHED_NEUTRAL_TRUTH_PT_CUT || fabs(m_g4_eta[k]) > MATCHED_NEUTRAL_TRUTH_ETA_CUT) { continue; }
				    
				    v2.SetPtEtaPhi(m_g4_pt[k], m_g4_eta[k], m_g4_phi[k]);
				    //std::cout << "pt = " << m_g4_pt[k] << " " << v2.Pt() << " dr = " << v1.DeltaR(v2) << std::endl;
				    if (v1.DeltaR(v2) < MATCHED_DR_CUT) {
				    	//std::cout << "pid = " << m_g4_pid[k] << " pt = " << v2.Pt() << " dr = " << v1.DeltaR(v2) << " E = " << m_g4_e[k] << std::endl;
				        if (m_g4_pid[k] == 111) { 
				        	continue;
				        } else {
				        	n_nn++;
				        	e_nn += m_g4_e[k];
				        }
			    	}
			    }
			    //std::cout << "centrality = " << centrality << " E_total = " << e_nn << " N = " << n_nn << std::endl;

    			for (int k = 1; k < 5; k++) {
      				if (centrality > centrality_array[k-1] && centrality < centrality_array[k]) {
        				histEmptyEnergy[k-1]->Fill(e_nn);
        				histEmptyNumber[k-1]->Fill(n_nn);
						histEmptyCenter[k-1]->Fill(circle_eta[i],circle_phi[j]);
      				}
    			}

		    	return;
		    }
		}
	}
}