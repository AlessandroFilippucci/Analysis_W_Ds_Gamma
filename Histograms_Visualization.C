// /eos/user/a/afilippu/15k_events/15k_RECO.root
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>

using namespace std;

void Analisi_MC_W_plus(TChain* a_, TChain* b_, const char* outputFile) {

  /*std::ofstream cosPhiFile("cos_phi_values.txt");
  if (!cosPhiFile.is_open()) {
      std::cerr << "Errore: impossibile aprire il file di testo per scrivere i valori di cos_phi." << std::endl;
      return;
  }*/

  double W_pt_gen, W_eta_gen, W_phi_gen;
  double K0bar_pt_gen, K0bar_eta_gen, K0bar_phi_gen;
  double Phi_pt_gen, Phi_eta_gen, Phi_phi_gen;
  double Piplus_pt_gen, Piplus_eta_gen, Piplus_phi_gen;
  double Kplus_pt_gen, Kplus_eta_gen, Kplus_phi_gen;
  double Kminus_pt_gen, Kminus_eta_gen, Kminus_phi_gen;
  double Piplus_pt_gen2, Piplus_eta_gen2, Piplus_phi_gen2;
  double Kplus_pt_gen2, Kplus_eta_gen2, Kplus_phi_gen2;
  double Kminus_pt_gen2, Kminus_eta_gen2, Kminus_phi_gen2;
  double DS_pt_gen, DS_eta_gen, DS_phi_gen;
  double Gamma_pt_gen, Gamma_eta_gen, Gamma_phi_gen;

  double W_pt, W_eta, W_phi;
  double Piplus_pt, Piplus_eta, Piplus_phi;
  double Kplus_pt, Kplus_eta, Kplus_phi;
  double Kminus_pt, Kminus_eta, Kminus_phi;
  double DS_pt, DS_eta, DS_phi, DSmass;
  double Gamma_pt, Gamma_eta, Gamma_phi;
  
  double inv_mass_W;
  double CL_vertex, cos_phi;
  double x_p, y_p, z_p; 
  double x_s, y_s, z_s; 
  double L_abs, L_sigma;
  int vertex_size, num_tracks, truePU /*pt_tracks*/;
  double DeltaR_12, DeltaR_13, DeltaR_23;
  double DeltaR_12_gen, DeltaR_13_gen, DeltaR_23_gen;
  double DeltaR_12_gen2, DeltaR_13_gen2, DeltaR_23_gen2;
  double DeltaR_Kplus_matching, DeltaR_Kminus_matching, DeltaR_Piplus_matching; 
  double pi_mass = 0.13957018;
  double K_mass = 0.493677;
  double DS_mass = 1.96835;
  //bool passTrigger;

  a_->SetBranchAddress("W_pt", &W_pt);
  a_->SetBranchAddress("W_eta", &W_eta);
  a_->SetBranchAddress("W_phi", &W_phi);
  a_->SetBranchAddress("W_mass", &inv_mass_W);
  a_->SetBranchAddress("Piplus_pt", &Piplus_pt);
  a_->SetBranchAddress("Piplus_eta", &Piplus_eta);
  a_->SetBranchAddress("Piplus_phi", &Piplus_phi);
  a_->SetBranchAddress("Kplus_pt", &Kplus_pt);
  a_->SetBranchAddress("Kplus_eta", &Kplus_eta);
  a_->SetBranchAddress("Kplus_phi", &Kplus_phi);
  a_->SetBranchAddress("Kminus_pt", &Kminus_pt);
  a_->SetBranchAddress("Kminus_eta", &Kminus_eta);
  a_->SetBranchAddress("Kminus_phi", &Kminus_phi);
  a_->SetBranchAddress("DS_pt", &DS_pt);
  a_->SetBranchAddress("DS_eta", &DS_eta);
  a_->SetBranchAddress("DS_phi", &DS_phi);
  a_->SetBranchAddress("DS_mass", &DSmass);
  a_->SetBranchAddress("Gamma_pt", &Gamma_pt);
  a_->SetBranchAddress("Gamma_eta", &Gamma_eta);
  a_->SetBranchAddress("Gamma_phi", &Gamma_phi);
  a_->SetBranchAddress("L_abs", &L_abs);
  a_->SetBranchAddress("L_sigma", &L_sigma);
  a_->SetBranchAddress("cos_phi", &cos_phi);
  a_->SetBranchAddress("vertex_size", &vertex_size);
  a_->SetBranchAddress("num_tracks", &num_tracks);
  a_->SetBranchAddress("truePU", &truePU);
  //a_->SetBranchAddress("passTrigger", &passTrigger);
  //a_->SetBranchAddress("pt_tracks", &pt_tracks);
  a_->SetBranchAddress("CL_vertex", &CL_vertex);
  a_->SetBranchAddress("x_p", &x_p);
  a_->SetBranchAddress("y_p", &y_p);
  a_->SetBranchAddress("z_p", &z_p);
  a_->SetBranchAddress("x_s", &x_s);
  a_->SetBranchAddress("y_s", &y_s);
  a_->SetBranchAddress("z_s", &z_s);
  a_->SetBranchAddress("DeltaR_12", &DeltaR_12);
  a_->SetBranchAddress("DeltaR_13", &DeltaR_13);
  a_->SetBranchAddress("DeltaR_23", &DeltaR_23);
  a_->SetBranchAddress("DeltaR_Kplus_matching", &DeltaR_Kplus_matching);
  a_->SetBranchAddress("DeltaR_Kminus_matching", &DeltaR_Kminus_matching);
  a_->SetBranchAddress("DeltaR_Piplus_matching", &DeltaR_Piplus_matching);

  b_->SetBranchAddress("W_pt_gen", &W_pt_gen);
  b_->SetBranchAddress("W_eta_gen", &W_eta_gen);
  b_->SetBranchAddress("W_phi_gen", &W_phi_gen);
  b_->SetBranchAddress("Piplus_pt_gen", &Piplus_pt_gen);
  b_->SetBranchAddress("Piplus_eta_gen", &Piplus_eta_gen);
  b_->SetBranchAddress("Piplus_phi_gen", &Piplus_phi_gen);
  b_->SetBranchAddress("Kplus_pt_gen", &Kplus_pt_gen);
  b_->SetBranchAddress("Kplus_eta_gen", &Kplus_eta_gen);
  b_->SetBranchAddress("Kplus_phi_gen", &Kplus_phi_gen);
  b_->SetBranchAddress("Kminus_pt_gen", &Kminus_pt_gen);
  b_->SetBranchAddress("Kminus_eta_gen", &Kminus_eta_gen);
  b_->SetBranchAddress("Kminus_phi_gen", &Kminus_phi_gen);
  b_->SetBranchAddress("DS_pt_gen", &DS_pt_gen);
  b_->SetBranchAddress("DS_eta_gen", &DS_eta_gen);
  b_->SetBranchAddress("DS_phi_gen", &DS_phi_gen);
  b_->SetBranchAddress("Gamma_pt_gen", &Gamma_pt_gen);
  b_->SetBranchAddress("Gamma_eta_gen", &Gamma_eta_gen);
  b_->SetBranchAddress("Gamma_phi_gen", &Gamma_phi_gen);
  b_->SetBranchAddress("Kplus_pt_gen2", &Kplus_pt_gen2);
  b_->SetBranchAddress("Kplus_eta_gen2", &Kplus_eta_gen2);
  b_->SetBranchAddress("Kplus_phi_gen2", &Kplus_phi_gen2);
  b_->SetBranchAddress("Kminus_pt_gen2", &Kminus_pt_gen2);
  b_->SetBranchAddress("Kminus_eta_gen2", &Kminus_eta_gen2);
  b_->SetBranchAddress("Kminus_phi_gen2", &Kminus_phi_gen2);
  b_->SetBranchAddress("Piplus_pt_gen2", &Piplus_pt_gen2);
  b_->SetBranchAddress("Piplus_eta_gen2", &Piplus_eta_gen2);
  b_->SetBranchAddress("Piplus_phi_gen2", &Piplus_phi_gen2);
  b_->SetBranchAddress("Phi_pt_gen", &Phi_pt_gen);
  b_->SetBranchAddress("Phi_eta_gen", &Phi_eta_gen);
  b_->SetBranchAddress("Phi_phi_gen", &Phi_phi_gen);
  b_->SetBranchAddress("K0bar_pt_gen", &K0bar_pt_gen);
  b_->SetBranchAddress("K0bar_eta_gen", &K0bar_eta_gen);
  b_->SetBranchAddress("K0bar_phi_gen", &K0bar_phi_gen);
  b_->SetBranchAddress("Delta R GEN tra K+ e Pi+", &DeltaR_12_gen);
  b_->SetBranchAddress("Delta R GEN tra K+ e K-", &DeltaR_13_gen);
  b_->SetBranchAddress("Delta R GEN tra Pi+ e K-", &DeltaR_23_gen);
  b_->SetBranchAddress("Delta R GEN2 tra K+ e Pi+", &DeltaR_12_gen2);
  b_->SetBranchAddress("Delta R GEN2 tra K+ e K-", &DeltaR_13_gen2);
  b_->SetBranchAddress("Delta R GEN2 tra Pi+ e K-", &DeltaR_23_gen2);


  TBranch *b_W_pt_gen=b_->GetBranch("W_pt_gen");
  TBranch *b_W_eta_gen=b_->GetBranch("W_eta_gen");
  TBranch *b_W_phi_gen=b_->GetBranch("W_phi_gen");

  TBranch *b_Piplus_pt_gen=b_->GetBranch("Piplus_pt_gen");
  TBranch *b_Piplus_eta_gen =b_->GetBranch("Piplus_eta_gen");
  TBranch *b_Piplus_phi_gen=b_->GetBranch("Piplus_phi_gen");
  
  TBranch *b_Kplus_pt_gen=b_->GetBranch("Kplus_pt_gen");
  TBranch *b_Kplus_eta_gen=b_->GetBranch("Kplus_eta_gen");
  TBranch *b_Kplus_phi_gen=b_->GetBranch("Kplus_phi_gen");

  TBranch *b_Kminus_pt_gen=b_->GetBranch("Kminus_pt_gen");
  TBranch *b_Kminus_eta_gen=b_->GetBranch("Kminus_eta_gen");
  TBranch *b_Kminus_phi_gen=b_->GetBranch("Kminus_phi_gen");

  TBranch *b_DS_pt_gen=b_->GetBranch("DS_pt_gen");
  TBranch *b_DS_eta_gen=b_->GetBranch("DS_eta_gen");
  TBranch *b_DS_phi_gen=b_->GetBranch("DS_phi_gen");

  TBranch *b_Gamma_pt_gen=b_->GetBranch("Gamma_pt_gen");
  TBranch *b_Gamma_eta_gen=b_->GetBranch("Gamma_eta_gen");
  TBranch *b_Gamma_phi_gen=b_->GetBranch("Gamma_phi_gen");

  TBranch *b_Kplus_pt_gen2=b_->GetBranch("Kplus_pt_gen2");
  TBranch *b_Kplus_eta_gen2=b_->GetBranch("Kplus_eta_gen2");
  TBranch *b_Kplus_phi_gen2=b_->GetBranch("Kplus_phi_gen2");

  TBranch *b_Kminus_pt_gen2=b_->GetBranch("Kminus_pt_gen2");
  TBranch *b_Kminus_eta_gen2=b_->GetBranch("Kminus_eta_gen2");
  TBranch *b_Kminus_phi_gen2=b_->GetBranch("Kminus_phi_gen2");

  TBranch *b_Piplus_pt_gen2=b_->GetBranch("Piplus_pt_gen2");
  TBranch *b_Piplus_eta_gen2=b_->GetBranch("Piplus_eta_gen2");
  TBranch *b_Piplus_phi_gen2=b_->GetBranch("Piplus_phi_gen2");

  TBranch *b_Phi_pt_gen=b_->GetBranch("Phi_pt_gen");
  TBranch *b_Phi_eta_gen=b_->GetBranch("Phi_eta_gen");
  TBranch *b_Phi_phi_gen=b_->GetBranch("Phi_phi_gen");

  TBranch *b_K0bar_pt_gen=b_->GetBranch("K0bar_pt_gen");
  TBranch *b_K0bar_eta_gen=b_->GetBranch("K0bar_eta_gen");
  TBranch *b_K0bar_phi_gen=b_->GetBranch("K0bar_phi_gen");


  TBranch *a_W_pt=a_->GetBranch("W_pt");
  TBranch *a_W_eta=a_->GetBranch("W_eta");
  TBranch *a_W_phi=a_->GetBranch("W_phi");
  TBranch *a_W_mass=a_->GetBranch("W_mass");

  TBranch *a_Piplus_pt=a_->GetBranch("Piplus_pt");
  TBranch *a_Piplus_eta=a_->GetBranch("Piplus_eta");
  TBranch *a_Piplus_phi=a_->GetBranch("Piplus_phi");

  TBranch *a_Kplus_pt=a_->GetBranch("Kplus_pt");
  TBranch *a_Kplus_eta=a_->GetBranch("Kplus_eta");
  TBranch *a_Kplus_phi=a_->GetBranch("Kplus_phi");

  TBranch *a_Kminus_pt=a_->GetBranch("Kminus_pt");
  TBranch *a_Kminus_eta=a_->GetBranch("Kminus_eta");
  TBranch *a_Kminus_phi=a_->GetBranch("Kminus_phi");

  TBranch *a_DS_pt=a_->GetBranch("DS_pt");
  TBranch *a_DS_eta=a_->GetBranch("DS_eta");
  TBranch *a_DS_phi=a_->GetBranch("DS_phi");
  TBranch *a_DS_mass=a_->GetBranch("DS_mass");

  TBranch *a_Gamma_pt=a_->GetBranch("Gamma_pt");
  TBranch *a_Gamma_eta=a_->GetBranch("Gamma_eta");
  TBranch *a_Gamma_phi=a_->GetBranch("Gamma_phi");

  TBranch *a_L_abs=a_->GetBranch("L_abs");
  TBranch *a_L_sigma=a_->GetBranch("L_sigma");
  TBranch *a_cosphi=a_->GetBranch("cos_phi");
  TBranch *a_vertex_size=a_->GetBranch("vertex_size");
  TBranch *a_num_tracks=a_->GetBranch("num_tracks");
  TBranch *a_truePU= a_->GetBranch("truePU");
  //TBranch *a_trigger=a_->GetBranch("passTrigger");
  //TBranch *a_pt_tracks=a_->GetBranch("pt_tracks");
  TBranch *a_CL_vertex=a_->GetBranch("CL_vertex");
  TBranch *a_x_p=a_->GetBranch("x_p");
  TBranch *a_y_p=a_->GetBranch("y_p");
  TBranch *a_z_p=a_->GetBranch("z_p");
  TBranch *a_x_s=a_->GetBranch("x_s");
  TBranch *a_y_s=a_->GetBranch("y_s");
  TBranch *a_z_s=a_->GetBranch("z_s");
  TBranch *a_DeltaR_12=a_->GetBranch("DeltaR_12");
  TBranch *a_DeltaR_13=a_->GetBranch("DeltaR_13");
  TBranch *a_DeltaR_23=a_->GetBranch("DeltaR_23");
  TBranch *b_DeltaR_12_gen=b_->GetBranch("Delta R GEN tra K+ e Pi+");
  TBranch *b_DeltaR_13_gen=b_->GetBranch("Delta R GEN tra K+ e K-");
  TBranch *b_DeltaR_23_gen=b_->GetBranch("Delta R GEN tra Pi+ e K-");
  TBranch *b_DeltaR_12_gen2=b_->GetBranch("Delta R GEN2 tra K+ e Pi+");
  TBranch *b_DeltaR_13_gen2=b_->GetBranch("Delta R GEN2 tra K+ e K-");
  TBranch *b_DeltaR_23_gen2=b_->GetBranch("Delta R GEN2 tra Pi+ e K-");
  TBranch *a_DeltaR_Kplus_matching=a_->GetBranch("DeltaR_Kplus_matching");
  TBranch *a_DeltaR_Kminus_matching=a_->GetBranch("DeltaR_Kminus_matching");
  TBranch *a_DeltaR_Piplus_matching=a_->GetBranch("DeltaR_Piplus_matching");

  b_W_pt_gen->SetAddress(&W_pt_gen);
  b_W_eta_gen->SetAddress(&W_eta_gen);
  b_W_phi_gen->SetAddress(&W_phi_gen);

  b_Piplus_pt_gen->SetAddress(&Piplus_pt_gen);
  b_Piplus_eta_gen->SetAddress(&Piplus_eta_gen);
  b_Piplus_phi_gen->SetAddress(&Piplus_phi_gen);

  b_Kplus_pt_gen->SetAddress(&Kplus_pt_gen);
  b_Kplus_eta_gen->SetAddress(&Kplus_eta_gen);
  b_Kplus_phi_gen->SetAddress(&Kplus_phi_gen);

  b_Kminus_pt_gen->SetAddress(&Kminus_pt_gen);
  b_Kminus_eta_gen->SetAddress(&Kminus_eta_gen);
  b_Kminus_phi_gen->SetAddress(&Kminus_phi_gen);

  b_DS_pt_gen->SetAddress(&DS_pt_gen);
  b_DS_eta_gen->SetAddress(&DS_eta_gen);
  b_DS_phi_gen->SetAddress(&DS_phi_gen);

  b_Gamma_pt_gen->SetAddress(&Gamma_pt_gen);
  b_Gamma_eta_gen->SetAddress(&Gamma_eta_gen);
  b_Gamma_phi_gen->SetAddress(&Gamma_phi_gen);

  a_W_pt->SetAddress(&W_pt);
  a_W_eta->SetAddress(&W_eta);
  a_W_phi->SetAddress(&W_phi);
  a_W_mass->SetAddress(&inv_mass_W);

  a_Piplus_pt->SetAddress(&Piplus_pt);
  a_Piplus_eta->SetAddress(&Piplus_eta);
  a_Piplus_phi->SetAddress(&Piplus_phi);

  a_Kplus_pt->SetAddress(&Kplus_pt);
  a_Kplus_eta->SetAddress(&Kplus_eta);
  a_Kplus_phi->SetAddress(&Kplus_phi);

  a_Kminus_pt->SetAddress(&Kminus_pt);
  a_Kminus_eta->SetAddress(&Kminus_eta);
  a_Kminus_phi->SetAddress(&Kminus_phi);

  a_DS_pt->SetAddress(&DS_pt);
  a_DS_eta->SetAddress(&DS_eta);
  a_DS_phi->SetAddress(&DS_phi);
  a_DS_mass->SetAddress(&DSmass);

  a_Gamma_pt->SetAddress(&Gamma_pt);
  a_Gamma_eta->SetAddress(&Gamma_eta);
  a_Gamma_phi->SetAddress(&Gamma_phi);

  a_L_abs->SetAddress(&L_abs);
  a_L_sigma->SetAddress(&L_sigma);
  a_cosphi->SetAddress(&cos_phi);
  a_vertex_size->SetAddress(&vertex_size);
  a_num_tracks->SetAddress(&num_tracks);
  a_truePU->SetAddress(&truePU);
  //a_trigger->SetAddress(&passTrigger);
  //a_pt_tracks->SetAddress(&pt_tracks);
  a_CL_vertex->SetAddress(&CL_vertex);
  a_x_p->SetAddress(&x_p);
  a_y_p->SetAddress(&y_p);
  a_z_p->SetAddress(&z_p);
  a_x_s->SetAddress(&x_s);
  a_y_s->SetAddress(&y_s);
  a_z_s->SetAddress(&z_s);
  a_DeltaR_12->SetAddress(&DeltaR_12);
  a_DeltaR_13->SetAddress(&DeltaR_13);
  a_DeltaR_23->SetAddress(&DeltaR_23);
  b_DeltaR_12_gen->SetAddress(&DeltaR_12_gen);
  b_DeltaR_13_gen->SetAddress(&DeltaR_13_gen);
  b_DeltaR_23_gen->SetAddress(&DeltaR_23_gen);
  b_DeltaR_12_gen2->SetAddress(&DeltaR_12_gen2);
  b_DeltaR_13_gen2->SetAddress(&DeltaR_13_gen2);
  b_DeltaR_23_gen2->SetAddress(&DeltaR_23_gen2);
  a_DeltaR_Kplus_matching->SetAddress(&DeltaR_Kplus_matching);
  a_DeltaR_Kminus_matching->SetAddress(&DeltaR_Kminus_matching);
  a_DeltaR_Piplus_matching->SetAddress(&DeltaR_Piplus_matching);

  TH1D * h_W_pt = new TH1D("W_pt", "W_pt", 70, 0., 60);
  h_W_pt->SetTitle("W+ p_{T}");
  h_W_pt->SetXTitle("p_{T} [GeV]");
  h_W_pt->SetYTitle("Entries");
  h_W_pt->SetLineColor(kRed);
  TH1D * h_W_eta = new TH1D("W_eta", "W_eta", 70, -2.4, 2.4);
  h_W_eta->SetTitle("W+ #eta");
  h_W_eta->SetXTitle("#eta");
  h_W_eta->SetYTitle("Entries");
  h_W_eta->SetLineColor(kBlue);
  TH1D * h_W_phi = new TH1D("W_phi", "W_phi", 30, -3.14, 3.14);
  h_W_phi->SetTitle("W+ #phi");
  h_W_phi->SetXTitle("#phi");
  h_W_phi->SetYTitle("Entries");
  h_W_phi->SetLineColor(kBlack);
  TH1D * h_W_mass = new TH1D("W_mass", "W_mass", 100, 70, 90);
  h_W_mass->SetTitle("W+ invariant mass");
  h_W_mass->SetXTitle("m_{W} [GeV]");
  h_W_mass->SetYTitle("Entries");
  h_W_mass->SetLineColor(kRed);

  //I PT DELLE PARTICELLE RECO NON SONO BELLI. NON SO SE DIPENDA DALLA SCALA OPPURE SIANO PROPRIO
  //VENUTI MALE. CHIEDERE A VALENTINA
  TH1D * h_Piplus_pt = new TH1D("Piplus_pt", "Piplus_pt", 70, 0., 30); //FORSE LOG SCALE?
  h_Piplus_pt->SetTitle("p_{T} of #pi^{+}");
  h_Piplus_pt->SetXTitle("p_{T} [GeV]");
  h_Piplus_pt->SetYTitle("Entries");
  h_Piplus_pt->SetLineColor(kRed);
  TH1D * h_Piplus_eta = new TH1D("Piplus_eta", "Piplus_eta", 70, -2.4, 2.4);
  h_Piplus_eta->SetTitle("#eta of #pi^{+}");
  h_Piplus_eta->SetXTitle("#eta");
  h_Piplus_eta->SetYTitle("Entries");
  h_Piplus_eta->SetLineColor(kBlue);
  TH1D * h_Piplus_phi = new TH1D("Piplus_phi", "Piplus_phi", 70, -3.14, 3.14);
  h_Piplus_phi->SetTitle("#phi of #pi^{+}");
  h_Piplus_phi->SetXTitle("#phi");
  h_Piplus_phi->SetYTitle("Entries");
  h_Piplus_phi->SetLineColor(kBlack);

  TH1D * h_Kplus_pt = new TH1D("Kplus_pt", "Kplus_pt", 70, 0., 30);
  h_Kplus_pt->SetTitle("p_{T} of K^{+}");
  h_Kplus_pt->SetXTitle("p_{T} [GeV]");
  h_Kplus_pt->SetYTitle("Entries");
  h_Kplus_pt->SetLineColor(kRed);
  TH1D * h_Kplus_eta = new TH1D("Kplus_eta", "Kplus_eta", 70, -2.4, 2.4);
  h_Kplus_eta->SetTitle("#eta of K^{+}");
  h_Kplus_eta->SetXTitle("#eta");
  h_Kplus_eta->SetYTitle("Entries");
  h_Kplus_eta->SetLineColor(kBlue);
  TH1D * h_Kplus_phi = new TH1D("Kplus_phi", "Kplus_phi", 70, -3.14, 3.14);
  h_Kplus_phi->SetTitle("#phi of K^{+}");
  h_Kplus_phi->SetXTitle("#phi");
  h_Kplus_phi->SetYTitle("Entries");
  h_Kplus_phi->SetLineColor(kBlack);

  TH1D * h_Kminus_pt = new TH1D("Kminus_pt", "Kminus_pt", 70, 0., 30);
  h_Kminus_pt->SetTitle("p_{T} of K^{-}");
  h_Kminus_pt->SetXTitle("p_{T} [GeV]");
  h_Kminus_pt->SetYTitle("Entries");
  h_Kminus_pt->SetLineColor(kRed);
  TH1D * h_Kminus_eta = new TH1D("Kminus_eta", "Kminus_eta", 70, -2.4, 2.4);
  h_Kminus_eta->SetTitle("#eta of K^{-}");
  h_Kminus_eta->SetXTitle("#eta");
  h_Kminus_eta->SetYTitle("Entries");
  h_Kminus_eta->SetLineColor(kBlue);
  TH1D * h_Kminus_phi = new TH1D("Kminus_phi", "Kminus_phi", 70, -3.14, 3.14);
  h_Kminus_phi->SetTitle("#phi of K^{-}");
  h_Kminus_phi->SetXTitle("#phi");
  h_Kminus_phi->SetYTitle("Entries");
  h_Kminus_phi->SetLineColor(kBlack);

  TH1D * h_DS_pt = new TH1D("DS_pt", "DS_pt", 70, 0., 60);
  h_DS_pt->SetTitle("p_{T} of D_{S}+");
  h_DS_pt->SetXTitle("p_{T} [GeV]");
  h_DS_pt->SetYTitle("Entries");
  h_DS_pt->SetLineColor(kRed);
  TH1D * h_DS_eta = new TH1D("DS_eta", "DS_eta", 70, -2.4, 2.4);
  h_DS_eta->SetTitle("#eta of D_{S}+");
  h_DS_eta->SetXTitle("#eta");
  h_DS_eta->SetYTitle("Entries");
  h_DS_eta->SetLineColor(kBlue);
  TH1D * h_DS_phi = new TH1D("DS_phi", "DS_phi", 70, -3.14, 3.14);
  h_DS_phi->SetTitle("#phi of D_{S}+");
  h_DS_phi->SetXTitle("#phi");
  h_DS_phi->SetYTitle("Entries");
  h_DS_phi->SetLineColor(kBlack);
  TH1D * h_DS_mass = new TH1D("DS_mass", "DS_mass", 70, 1.6, 2.1);
  h_DS_mass->SetTitle("DS+ invariant mass");
  h_DS_mass->SetXTitle("m_{DS} [GeV]");
  h_DS_mass->SetYTitle("Entries");
  h_DS_mass->SetLineColor(kRed);

  TH1D * h_Gamma_pt = new TH1D("Gamma_pt", "Gamma_pt", 70, 37, 90);
  h_Gamma_pt->SetTitle("p_{T} of #gamma");
  h_Gamma_pt->SetXTitle("p_{T} [GeV]");
  h_Gamma_pt->SetYTitle("Entries");
  h_Gamma_pt->SetLineColor(kRed);
  TH1D * h_Gamma_eta = new TH1D("Gamma_eta", "Gamma_eta", 70, -2.4, 2.4);
  h_Gamma_eta->SetTitle("#eta of #gamma");
  h_Gamma_eta->SetXTitle("#eta");
  h_Gamma_eta->SetYTitle("Entries");
  h_Gamma_eta->SetLineColor(kBlue);
  TH1D * h_Gamma_phi = new TH1D("Gamma_phi", "Gamma_phi", 70, -3.14, 3.14);
  h_Gamma_phi->SetTitle("#phi of #gamma");
  h_Gamma_phi->SetXTitle("#phi");
  h_Gamma_phi->SetYTitle("Entries");
  h_Gamma_phi->SetLineColor(kBlack);

  TH1D * h_L_abs = new TH1D("L_abs", "L_abs", 100, 0., 3); 
  h_L_abs->SetTitle("L_{abs}");
  h_L_abs->SetXTitle("L_{abs} [cm]");
  h_L_abs->SetYTitle("Entries");
  h_L_abs->SetLineColor(kRed);
  TH1D * h_L_sigma = new TH1D("L_sigma", "L_sigma", 100, 1.9, 10); 
  h_L_sigma->SetTitle("L_{sigma}");
  h_L_sigma->SetXTitle("L_{sigma} [cm]");
  h_L_sigma->SetYTitle("Entries");
  h_L_sigma->SetLineColor(kBlue);
  TH1D * h_cosphi = new TH1D("cos_phi", "cos_phi", 100, 0.998, 1.); //LOG SCALE O RIDURRE LIMITE
  h_cosphi->SetTitle("cos(#phi)");
  h_cosphi->SetXTitle("cos(#phi)");
  h_cosphi->SetYTitle("Entries");
  h_cosphi->SetLineColor(kBlack);
  TH1D * h_vertex_size = new TH1D("vertex_size", "vertex_size", 100, 0., 60);
  h_vertex_size->SetTitle("vertex_size");
  h_vertex_size->SetXTitle("vertex_size");
  h_vertex_size->SetYTitle("Entries");
  h_vertex_size->SetLineColor(kRed);
  TH1D * h_num_tracks = new TH1D("num_tracks", "num_tracks", 100, 0., 70);
  h_num_tracks->SetTitle("num_tracks");
  h_num_tracks->SetXTitle("num_tracks");
  h_num_tracks->SetYTitle("Entries");
  h_num_tracks->SetLineColor(kBlue);
  TH1D * h_truePU = new TH1D("truePU", "truePU", 100, 0., 70);
  h_truePU->SetTitle("Pile Up");
  h_truePU->SetXTitle("truePU");
  h_truePU->SetYTitle("Entries");
  h_truePU->SetLineColor(kBlack);
  TH1D * h_CL_vertex = new TH1D("CL_vertex", "CL_vertex", 100, 0., 1);
  h_CL_vertex->SetTitle("CL_vertex");
  h_CL_vertex->SetXTitle("CL_vertex");
  h_CL_vertex->SetYTitle("Entries");
  h_CL_vertex->SetLineColor(kBlack);
  TH1D * h_x_p = new TH1D("x_p", "x_p", 100, 0., 70);
  TH1D * h_y_p = new TH1D("y_p", "y_p", 100, 0., 70);
  TH1D * h_z_p = new TH1D("z_p", "z_p", 100, 0., 70);
  TH1D * h_x_s = new TH1D("x_s", "x_s", 100, 0., 70);
  TH1D * h_y_s = new TH1D("y_s", "y_s", 100, 0., 70);
  TH1D * h_z_s = new TH1D("z_s", "z_s", 100, 0., 70);
  TH1D * h_DeltaR_12 = new TH1D("DeltaR_12", "DeltaR_12", 70, 0., 0.5);
  h_DeltaR_12->SetTitle("Delta R tra K+ e Pi+");
  h_DeltaR_12->SetXTitle("#Delta R");
  h_DeltaR_12->SetYTitle("Entries");
  h_DeltaR_12->SetLineColor(kRed);
  TH1D * h_DeltaR_13 = new TH1D("DeltaR_13", "DeltaR_13", 70, 0., 0.5);
  h_DeltaR_13->SetTitle("Delta R tra K+ e K-");
  h_DeltaR_13->SetXTitle("#Delta R");
  h_DeltaR_13->SetYTitle("Entries");
  h_DeltaR_13->SetLineColor(kBlue);
  TH1D * h_DeltaR_23 = new TH1D("DeltaR_23", "DeltaR_23", 70, 0., 0.5);
  h_DeltaR_23->SetTitle("Delta R tra Pi+ e K-");
  h_DeltaR_23->SetXTitle("#Delta R");
  h_DeltaR_23->SetYTitle("Entries");
  h_DeltaR_23->SetLineColor(kBlack);
  TH1D * h_DeltaR_Kplus_matching = new TH1D("DeltaR_Kplus_matching", "DeltaR_Kplus_matching", 70, 0, 0.1);
  h_DeltaR_Kplus_matching->SetTitle("Delta R K+ matching");
  h_DeltaR_Kplus_matching->SetXTitle("#Delta R");
  h_DeltaR_Kplus_matching->SetYTitle("Entries");
  h_DeltaR_Kplus_matching->SetLineColor(kRed);
  TH1D * h_DeltaR_Kminus_matching = new TH1D("DeltaR_Kminus_matching", "DeltaR_Kminus_matching", 70, 0, 0.1);
  h_DeltaR_Kminus_matching->SetTitle("Delta R K- matching");
  h_DeltaR_Kminus_matching->SetXTitle("#Delta R");
  h_DeltaR_Kminus_matching->SetYTitle("Entries");
  h_DeltaR_Kminus_matching->SetLineColor(kBlue);
  TH1D * h_DeltaR_Piplus_matching = new TH1D("DeltaR_Piplus_matching", "DeltaR_Piplus_matching", 70, 0, 0.1);
  h_DeltaR_Piplus_matching->SetTitle("Delta R Pi+ matching");
  h_DeltaR_Piplus_matching->SetXTitle("#Delta R");
  h_DeltaR_Piplus_matching->SetYTitle("Entries");
  h_DeltaR_Piplus_matching->SetLineColor(kBlack);

  TH2D *h2_Gamma_DS_pt = new TH2D("h2_Gamma_DS_pt", "Correlation between Gamma p_{T} and DS p_{T}", 100, 0., 70., 100, 0., 70.);
  h2_Gamma_DS_pt->SetTitle("Correlation between Gamma p_{T} and DS p_{T}");
  h2_Gamma_DS_pt->SetXTitle("Gamma p_{T} [GeV]");
  h2_Gamma_DS_pt->SetYTitle("DS p_{T} [GeV]");
  h2_Gamma_DS_pt->SetLineColor(kBlack);

  TH1D * h_DS_mass_signal = new TH1D("DS_mass_signal", "DS_mass_signal", 170, 1.94, 2.);
  h_DS_mass_signal->SetTitle("DS+ invariant mass signal");
  h_DS_mass_signal->SetXTitle("m_{DS} [GeV]");
  h_DS_mass_signal->SetYTitle("Entries");
  h_DS_mass_signal->SetLineColor(kRed);

  TH1D * h_W_mass_signal = new TH1D("W_mass_signal", "W_mass_signal", 100, 70, 90);
  h_W_mass_signal->SetTitle("W+ invariant mass signal");
  h_W_mass_signal->SetXTitle("m_{W} [GeV]");
  h_W_mass_signal->SetYTitle("Entries");
  h_W_mass_signal->SetLineColor(kRed); 

  // filling MC histos
  for (Int_t i=0;i<a_->GetEntries();i++) {
    a_->GetEntry(i);
    //cosPhiFile << cos_phi << std::endl;
    if(Gamma_pt > 37 && cos_phi > 0.95 && Gamma_eta >= -2.4 && Gamma_eta <= 2.4) {
      h_W_pt->Fill(W_pt);
      h_W_eta->Fill(W_eta);
      h_W_phi->Fill(W_phi);
      h_W_mass->Fill(inv_mass_W);
      h_Piplus_pt->Fill(Piplus_pt);
      h_Piplus_eta->Fill(Piplus_eta);
      h_Piplus_phi->Fill(Piplus_phi);
      h_Kplus_pt->Fill(Kplus_pt);
      h_Kplus_eta->Fill(Kplus_eta);
      h_Kplus_phi->Fill(Kplus_phi);
      h_Kminus_pt->Fill(Kminus_pt);
      h_Kminus_eta->Fill(Kminus_eta);
      h_Kminus_phi->Fill(Kminus_phi);
      h_DS_pt->Fill(DS_pt);
      h_DS_eta->Fill(DS_eta);
      h_DS_phi->Fill(DS_phi);
      h_DS_mass->Fill(DSmass);
      h_Gamma_eta->Fill(Gamma_eta);
      h_Gamma_pt->Fill(Gamma_pt);
      h_Gamma_phi->Fill(Gamma_phi);
      h_L_abs->Fill(L_abs);
      h_L_sigma->Fill(L_sigma);
      h_cosphi->Fill(cos_phi);
      h_vertex_size->Fill(vertex_size);
      h_num_tracks->Fill(num_tracks);
      h_truePU->Fill(truePU);
      //h_trigger->Fill(passTrigger);
      //h_pt_tracks->Fill(pt_tracks);
      h_CL_vertex->Fill(CL_vertex);
      h_x_p->Fill(x_p);
      h_y_p->Fill(y_p);
      h_z_p->Fill(z_p);
      h_x_s->Fill(x_s);
      h_y_s->Fill(y_s);
      h_z_s->Fill(z_s);
      h_DeltaR_12->Fill(DeltaR_12);
      h_DeltaR_13->Fill(DeltaR_13);
      h_DeltaR_23->Fill(DeltaR_23);
      h_DeltaR_Kplus_matching->Fill(DeltaR_Kplus_matching);
      h_DeltaR_Kminus_matching->Fill(DeltaR_Kminus_matching);
      h_DeltaR_Piplus_matching->Fill(DeltaR_Piplus_matching);
      h2_Gamma_DS_pt->Fill(Gamma_pt, DS_pt);
      if(DSmass > 1.94 && DSmass < 2.){
        h_DS_mass_signal->Fill(DSmass);
        h_W_mass_signal->Fill(inv_mass_W);
      }
    }
  }
  //cosPhiFile.close();
  TFile *f = new TFile(outputFile, "RECREATE");
  if (!f->IsOpen()) {
    std::cerr << "Errore: impossibile aprire il file di output." << std::endl;
    return;
  }
  h_W_pt->Write();
  h_W_eta->Write();
  h_W_phi->Write();
  h_W_mass->Write();
  h_Piplus_pt->Write();
  h_Piplus_eta->Write();
  h_Piplus_phi->Write();
  h_Kplus_pt->Write();
  h_Kplus_eta->Write();
  h_Kplus_phi->Write();
  h_Kminus_pt->Write();
  h_Kminus_eta->Write();
  h_Kminus_phi->Write();
  h_DS_pt->Write();
  h_DS_eta->Write();
  h_DS_phi->Write();
  h_DS_mass->Write();
  h_Gamma_pt->Write();
  h_Gamma_eta->Write();
  h_Gamma_phi->Write();
  h_L_abs->Write();
  h_L_sigma->Write();
  h_cosphi->Write();
  h_vertex_size->Write();
  h_num_tracks->Write();
  h_truePU->Write();
  //h_trigger->Write();
  //h_pt_tracks->Write();
  h_CL_vertex->Write();
  h_x_p->Write();
  h_y_p->Write();
  h_z_p->Write();
  h_x_s->Write();
  h_y_s->Write();
  h_z_s->Write();
  h_DeltaR_12->Write();
  h_DeltaR_13->Write();
  h_DeltaR_23->Write();
  h_DeltaR_Kplus_matching->Write();
  h_DeltaR_Kminus_matching->Write();
  h_DeltaR_Piplus_matching->Write();
  h2_Gamma_DS_pt->Write();
  h_DS_mass_signal->Write();
  h_W_mass_signal->Write();

  f->Write();
  f->Close();
}
