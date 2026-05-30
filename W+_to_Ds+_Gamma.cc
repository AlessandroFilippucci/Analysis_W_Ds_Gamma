#include "Analysis_includes.h"

using pat::PATSingleVertexSelector;
using namespace std;
using namespace edm;
using namespace reco;

// class declaration
class analysis_W_plus_first_decay : public edm::EDAnalyzer {
  public:
  explicit analysis_W_plus_first_decay(const edm::ParameterSet&);
  ~analysis_W_plus_first_decay(); //costruttore

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
  virtual void beginJob() ; //come già visto nell'analisi preliminare
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  edm::InputTag assocTags_;

  //definizioni di mappe per contenere istogrammi
  std::map<std::string,TH1F*> histContainer_;
  std::map<std::string,TH2F*> histContainer2_;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  int i;

  //definizione dei token necessari per accedere alle collezioni di dati degli
  //eventi da analizzare, come tracce, vertici, particelle ecc.
  edm::EDGetToken tracks_;
  edm::EDGetToken hVtx_;
  edm::EDGetToken beamSpotHandle_;
  edm::EDGetToken genParticles_;
  edm::EDGetToken hPU_;
  edm::EDGetToken trigger;
  edm::EDGetToken photons_;

  TTree *Tree; //un tree per dati processati oltre il gen level
  TTree *genTree; //tree per le particelle gen level

  //definizione delle variabili Pt, eta e phi per le particelle di interesse.
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
  double K0bar_pt, K0bar_eta, K0bar_phi;
  double Phi_pt, Phi_eta, Phi_phi;
  double Piplus_pt, Piplus_eta, Piplus_phi;
  double Kplus_pt, Kplus_eta, Kplus_phi;
  double Kminus_pt, Kminus_eta, Kminus_phi;
  double DS_pt, DS_eta, DS_phi;
  double Gamma_pt, Gamma_eta, Gamma_phi;
  
  double inv_mass_W = 0;
  double CL_vertex; //Confidence Level del vertice
  double x_p, y_p, z_p; //credo siano le coordinate del vertice primario
  double x_s, y_s, z_s; //coordinate del vertice secondario
  double L_abs, L_sigma, L_err; //la definizione di L mi è stata spiegata da Valentina in un colloquio ma devo ricercarla
  double cos_phi;
  int vertex_size, num_tracks, truePU, pt_tracks, presc;
  double DeltaR_12, DeltaR_13, DeltaR_23;
  double DeltaR_12_gen, DeltaR_13_gen, DeltaR_23_gen;
  double DeltaR_12_gen2, DeltaR_13_gen2, DeltaR_23_gen2;
  double DeltaR_Kplus_matching, DeltaR_Kminus_matching, DeltaR_Piplus_matching; 
  //HLTPrescaleProvider *hltPS_ ;
  bool passTrigger;
  int totalCandidates = 0;
 // ----------member data ---------------------------
};

//implementazione del costruttore, che prende subito le collezioni di dati nei token
//e assegna le variabili di interesse ai branch dei due tree (gen e non gen)

analysis_W_plus_first_decay::analysis_W_plus_first_decay(const edm::ParameterSet& iConfig){
  edm::Service<TFileService> fs;

  tracks_= consumes<reco::TrackCollection>(edm::InputTag("generalTracks"));
  hVtx_= consumes<std::vector<reco::Vertex>>(edm::InputTag("offlinePrimaryVertices"));
  beamSpotHandle_= consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
  genParticles_= consumes<edm::View<reco::GenParticle>>(edm::InputTag("genParticles"));
  hPU_ = consumes<std::vector<PileupSummaryInfo>>(edm::InputTag("addPileupInfo"));
  trigger = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","","HLT"));
  photons_ = consumes<reco::PhotonCollection>(edm::InputTag("photons"));

  genTree = fs->make<TTree>("Gen", "Gen");

  genTree->Branch("W_pt_gen",&W_pt_gen,"W_pt_gen/D");
  genTree->Branch("W_eta_gen",&W_eta_gen,"W_eta_gen/D");
  genTree->Branch("W_phi_gen",&W_phi_gen,"W_phi_gen/D");

  genTree->Branch("DS_pt_gen",&DS_pt_gen,"DS_pt_gen/D");
  genTree->Branch("DS_eta_gen",&DS_eta_gen,"DS_eta_gen/D");
  genTree->Branch("DS_phi_gen",&DS_phi_gen,"DS_phi_gen/D");

  genTree->Branch("Gamma_pt_gen",&Gamma_pt_gen,"Gamma_pt_gen/D");
  genTree->Branch("Gamma_eta_gen",&Gamma_eta_gen,"Gamma_eta_gen/D");
  genTree->Branch("Gamma_phi_gen",&Gamma_phi_gen,"Gamma_phi_gen/D");

  genTree->Branch("K0bar_pt_gen",&K0bar_pt_gen,"K0bar_pt_gen/D");
  genTree->Branch("K0bar_eta_gen",&K0bar_eta_gen,"K0bar_eta_gen/D");
  genTree->Branch("K0bar_phi_gen",&K0bar_phi_gen,"K0bar_phi_gen/D");

  genTree->Branch("Kplus_pt_gen",&Kplus_pt_gen,"Kplus_pt_gen/D");
  genTree->Branch("Kplus_eta_gen",&Kplus_eta_gen,"Kplus_eta_gen/D");
  genTree->Branch("Kplus_phi_gen",&Kplus_phi_gen,"Kplus_phi_gen/D");

  genTree->Branch("Piplus_pt_gen",&Piplus_pt_gen,"Piplus_pt_gen/D");
  genTree->Branch("Piplus_eta_gen",&Piplus_eta_gen,"Piplus_eta_gen/D");
  genTree->Branch("Piplus_phi_gen",&Piplus_phi_gen,"Piplus_phi_gen/D");

  genTree->Branch("Kminus_pt_gen",&Kminus_pt_gen,"Kminus_pt_gen/D");
  genTree->Branch("Kminus_eta_gen",&Kminus_eta_gen,"Kminus_eta_gen/D");
  genTree->Branch("Kminus_phi_gen",&Kminus_phi_gen,"Kminus_phi_gen/D");

  histContainer_["W_pt_gen"] = fs->make<TH1F>("W_pt_gen", "W_pt_gen", 100, 0, 200);
  histContainer_["W_eta_gen"] = fs->make<TH1F>("W_eta_gen", "W_eta_gen", 100, -5, 5);
  histContainer_["W_phi_gen"] = fs->make<TH1F>("W_phi_gen", "W_phi_gen", 100, -3.14, 3.14);

  histContainer_["DS_pt_gen"] = fs->make<TH1F>("DS_pt_gen", "DS_pt_gen", 100, 0, 200);
  histContainer_["DS_eta_gen"] = fs->make<TH1F>("DS_eta_gen", "DS_eta_gen", 100, -5, 5);
  histContainer_["DS_phi_gen"] = fs->make<TH1F>("DS_phi_gen", "DS_phi_gen", 100, -3.14, 3.14);

  histContainer_["Gamma_pt_gen"] = fs->make<TH1F>("Gamma_pt_gen", "Gamma_pt_gen", 100, 0, 200);
  histContainer_["Gamma_eta_gen"] = fs->make<TH1F>("Gamma_eta_gen", "Gamma_eta_gen", 100, -5, 5);
  histContainer_["Gamma_phi_gen"] = fs->make<TH1F>("Gamma_phi_gen", "Gamma_phi_gen", 100, -3.14, 3.14);

  histContainer_["K0bar_pt_gen"] = fs->make<TH1F>("K0bar_pt_gen", "K0bar_pt_gen", 100, 0, 200);
  histContainer_["K0bar_eta_gen"] = fs->make<TH1F>("K0bar_eta_gen", "K0bar_eta_gen", 100, -5, 5);
  histContainer_["K0bar_phi_gen"] = fs->make<TH1F>("K0bar_phi_gen", "K0bar_phi_gen", 100, -3.14, 3.14);

  histContainer_["Kplus_pt_gen"] = fs->make<TH1F>("Kplus_pt_gen", "Kplus_pt_gen", 100, 0, 200);
  histContainer_["Kplus_eta_gen"] = fs->make<TH1F>("Kplus_eta_gen", "Kplus_eta_gen", 100, -5, 5);
  histContainer_["Kplus_phi_gen"] = fs->make<TH1F>("Kplus_phi_gen", "Kplus_phi_gen", 100, -3.14, 3.14);

  histContainer_["Piplus_pt_gen"] = fs->make<TH1F>("Piplus_pt_gen", "Piplus_pt_gen", 100, 0, 200);
  histContainer_["Piplus_eta_gen"] = fs->make<TH1F>("Piplus_eta_gen", "Piplus_eta_gen", 100, -5, 5);
  histContainer_["Piplus_phi_gen"] = fs->make<TH1F>("Piplus_phi_gen", "Piplus_phi_gen", 100, -3.14, 3.14);

  histContainer_["Kminus_pt_gen"] = fs->make<TH1F>("Kminus_pt_gen", "Kminus_pt_gen", 100, 0, 200);
  histContainer_["Kminus_eta_gen"] = fs->make<TH1F>("Kminus_eta_gen", "Kminus_eta_gen", 100, -5, 5);
  histContainer_["Kminus_phi_gen"] = fs->make<TH1F>("Kminus_phi_gen", "Kminus_phi_gen", 100, -3.14, 3.14);
  
  histContainer_["Phi_pt_gen"] = fs->make<TH1F>("Phi_pt_gen", "Phi_pt_gen", 100, 0, 200);
  histContainer_["Phi_eta_gen"] = fs->make<TH1F>("Phi_eta_gen", "Phi_eta_gen", 100, -5, 5);
  histContainer_["Phi_phi_gen"] = fs->make<TH1F>("Phi_phi_gen", "Phi_phi_gen", 100, -3.14, 3.14);

  histContainer_["Kplus_pt_gen2"] = fs->make<TH1F>("Kplus_pt_gen2", "Kplus_pt_gen2", 100, 0, 200);
  histContainer_["Kplus_eta_gen2"] = fs->make<TH1F>("Kplus_eta_gen2", "Kplus_eta_gen2", 100, -5, 5);
  histContainer_["Kplus_phi_gen2"] = fs->make<TH1F>("Kplus_phi_gen2", "Kplus_phi_gen2", 100, -3.14, 3.14);

  histContainer_["Piplus_pt_gen2"] = fs->make<TH1F>("Piplus_pt_gen2", "Piplus_pt_gen2", 100, 0, 200);
  histContainer_["Piplus_eta_gen2"] = fs->make<TH1F>("Piplus_eta_gen2", "Piplus_eta_gen2", 100, -5, 5);
  histContainer_["Piplus_phi_gen2"] = fs->make<TH1F>("Piplus_phi_gen2", "Piplus_phi_gen2", 100, -3.14, 3.14);

  histContainer_["Kminus_pt_gen2"] = fs->make<TH1F>("Kminus_pt_gen2", "Kminus_pt_gen2", 100, 0, 200);
  histContainer_["Kminus_eta_gen2"] = fs->make<TH1F>("Kminus_eta_gen2", "Kminus_eta_gen2", 100, -5, 5);
  histContainer_["Kminus_phi_gen2"] = fs->make<TH1F>("Kminus_phi_gen2", "Kminus_phi_gen2", 100, -3.14, 3.14);
  
  histContainer_["Delta R GEN tra K+ e Pi+"] = fs->make<TH1F>("Delta R GEN tra K+ e Pi+", "Delta R GEN tra K+ e Pi+", 100, 0.0, 0.5);
  histContainer_["Delta R GEN tra K+ e K-"] = fs->make<TH1F>("Delta R GEN tra K+ e K-", "Delta R GEN tra K+ e K-", 100, 0.0, 0.5);
  histContainer_["Delta R GEN tra Pi+ e K-"] = fs->make<TH1F>("Delta R GEN tra Pi+ e K-", "Delta R GEN tra Pi+ e K-", 100, 0.0, 0.5);
  histContainer_["Delta R GEN2 tra K+ e Pi+"] = fs->make<TH1F>("Delta R GEN2 tra K+ e Pi+", "Delta R GEN2 tra K+ e Pi+", 100, 0.0, 0.5);
  histContainer_["Delta R GEN2 tra K+ e K-"] = fs->make<TH1F>("Delta R GEN2 tra K+ e K-", "Delta R GEN2 tra K+ e K-", 100, 0.0, 0.5);
  histContainer_["Delta R GEN2 tra Pi+ e K-"] = fs->make<TH1F>("Delta R GEN2 tra Pi+ e K-", "Delta R GEN2 tra Pi+ e K-", 100, 0.0, 0.5);

  Tree= fs->make<TTree>("Analysis","Analysis");

  Tree->Branch("W_pt", &W_pt, "W_pt/D");
  Tree->Branch("W_eta", &W_eta, "W_eta/D");
  Tree->Branch("W_phi", &W_phi, "W_phi/D");

  Tree->Branch("DS_pt", &DS_pt, "DS_pt/D");
  Tree->Branch("DS_eta", &DS_eta, "DS_eta/D");
  Tree->Branch("DS_phi", &DS_phi, "DS_phi/D");

  Tree->Branch("Gamma_pt", &Gamma_pt, "Gamma_pt/D");
  Tree->Branch("Gamma_eta", &Gamma_eta, "Gamma_eta/D");
  Tree->Branch("Gamma_phi", &Gamma_phi, "Gamma_phi/D");

  Tree->Branch("K0bar_pt", &K0bar_pt, "K0bar_pt/D");
  Tree->Branch("K0bar_eta", &K0bar_eta, "K0bar_eta/D");
  Tree->Branch("K0bar_phi", &K0bar_phi, "K0bar_phi/D");

  Tree->Branch("Kplus_pt", &Kplus_pt, "Kplus_pt/D");
  Tree->Branch("Kplus_eta", &Kplus_eta, "Kplus_eta/D");
  Tree->Branch("Kplus_phi", &Kplus_phi, "Kplus_phi/D");

  Tree->Branch("Piplus_pt", &Piplus_pt, "Piplus_pt/D");
  Tree->Branch("Piplus_eta", &Piplus_eta, "Piplus_eta/D");
  Tree->Branch("Piplus_phi", &Piplus_phi, "Piplus_phi/D");

  Tree->Branch("Kminus_pt", &Kminus_pt, "Kminus_pt/D");
  Tree->Branch("Kminus_eta", &Kminus_eta, "Kminus_eta/D");
  Tree->Branch("Kminus_phi", &Kminus_phi, "Kminus_phi/D");

  Tree->Branch("CL_vertex",&CL_vertex,"CL_vertex/D");

  Tree->Branch("x_p",&x_p,"x_p/D");
  Tree->Branch("y_p",&y_p,"y_p/D");
  Tree->Branch("z_p",&z_p,"z_p/D");

  Tree->Branch("x_s",&x_s,"x_s/D");
  Tree->Branch("y_s",&y_s,"y_s/D");
  Tree->Branch("z_s",&z_s,"z_s/D");

  Tree->Branch("L_abs",&L_abs,"L_abs/D");
  Tree->Branch("L_sigma",&L_sigma,"L_sigma/D");
  Tree->Branch("cos_phi",&cos_phi,"cos_phi/D");
  Tree->Branch("vertex_size",&vertex_size,"vertex_size/I");
  Tree->Branch("pt_tracks",&pt_tracks,"pt_tracks/D");
  Tree->Branch("truePU",&truePU,"truePU/I");
  Tree->Branch("num_tracks",&num_tracks,"num_tracks/I");

  histContainer_["W_pt"] = fs->make<TH1F>("W_pt", "W_pt", 200, 0, 100);
  histContainer_["W_eta"] = fs->make<TH1F>("W_eta", "W_eta", 200, -5, 5);
  histContainer_["W_phi"] = fs->make<TH1F>("W_phi", "W_phi", 200, -3.14, 3.14);

  histContainer_["DS_pt"] = fs->make<TH1F>("DS_pt", "DS_pt", 200, 0, 50);
  histContainer_["DS_eta"] = fs->make<TH1F>("DS_eta", "DS_eta", 200, -5, 5);
  histContainer_["DS_phi"] = fs->make<TH1F>("DS_phi", "DS_phi", 200, -3.14, 3.14);

  histContainer_["Gamma_pt"] = fs->make<TH1F>("Gamma_pt", "Gamma_pt", 200, 0, 100);
  histContainer_["Gamma_eta"] = fs->make<TH1F>("Gamma_eta", "Gamma_eta", 200, -5, 5);
  histContainer_["Gamma_phi"] = fs->make<TH1F>("Gamma_phi", "Gamma_phi", 200, -3.14, 3.14);

  histContainer_["Kplus_pt"] = fs->make<TH1F>("Kplus_pt", "Kplus_pt", 200, 0, 35);
  histContainer_["Kplus_eta"] = fs->make<TH1F>("Kplus_eta", "Kplus_eta", 200, -5, 5);
  histContainer_["Kplus_phi"] = fs->make<TH1F>("Kplus_phi", "Kplus_phi", 200, -3.14, 3.14);

  histContainer_["Piplus_pt"] = fs->make<TH1F>("Piplus_pt", "Piplus_pt", 200, 0, 35);
  histContainer_["Piplus_eta"] = fs->make<TH1F>("Piplus_eta", "Piplus_eta", 200, -5, 5);
  histContainer_["Piplus_phi"] = fs->make<TH1F>("Piplus_phi", "Piplus_phi", 200, -3.14, 3.14);

  histContainer_["Kminus_pt"] = fs->make<TH1F>("Kminus_pt", "Kminus_pt", 200, 0, 35);
  histContainer_["Kminus_eta"] = fs->make<TH1F>("Kminus_eta", "Kminus_eta", 200, -5, 5);
  histContainer_["Kminus_phi"] = fs->make<TH1F>("Kminus_phi", "Kminus_phi", 200, -3.14, 3.14);

  histContainer_["DS_mass"] = fs->make<TH1F>("DS_mass", "DS_mass", 200, 1.0, 3.0);
  histContainer_["W_mass"] = fs->make<TH1F>("W_mass", "W_mass", 200, 70.0, 90.0);

  histContainer_["Cos Phi"] = fs->make<TH1F>("Cos Phi", "Cos Phi", 200, -1.0, 1.0);
  histContainer_["L/sigma"] = fs->make<TH1F>("L/sigma", "L/sigma", 200, 0.0, 10.0);
  histContainer_["CL_vertex"] = fs->make<TH1F>("CL_vertex", "CL_vertex", 1000, 0.0, 1.0);

  histContainer_["Delta R tra K+ e Pi+"] = fs->make<TH1F>("Delta R tra K+ e Pi+", "Delta R tra K+ e Pi+", 300, 0.0, 0.5);
  histContainer_["Delta R tra K+ e K-"] = fs->make<TH1F>("Delta R tra K+ e K-", "Delta R tra K+ e K-", 300, 0.0, 0.5);
  histContainer_["Delta R tra Pi+ e K-"] = fs->make<TH1F>("Delta R tra Pi+ e K-", "Delta R tra Pi+ e K-", 300, 0.0, 0.5);
  histContainer_["Delta R matching K+"] = fs->make<TH1F>("Delta R matching K+", "Delta R matching K+", 300, 0.0, 0.5);
  histContainer_["Delta R matching Pi+"] = fs->make<TH1F>("Delta R matching Pi+", "Delta R matching Pi+", 300, 0.0, 0.5);
  histContainer_["Delta R matching K-"] = fs->make<TH1F>("Delta R matching K-", "Delta R matching K-", 300, 0.0, 0.5);
}

//implementazione di un costruttore alternativo, senza alcuna variabile passata
analysis_W_plus_first_decay::~analysis_W_plus_first_decay(){}

//implementazione della funzione di analisi vera e propria, a cui viene passato l'evento come
//variabile su cui lavorare.
void analysis_W_plus_first_decay::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace edm;

  edm::Handle<edm::View<reco::GenParticle> > genParticles;
  iEvent.getByToken(genParticles_, genParticles);

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByToken(tracks_ , tracks );

  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByToken(beamSpotHandle_ , beamSpotHandle);

  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);

  edm::ESHandle<TransientTrackBuilder> theB1;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB1);

  edm::Handle< std::vector<PileupSummaryInfo> > hPU;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), hPU);

  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trigger, trigResults);

  edm::Handle<reco::PhotonCollection> photons;
  iEvent.getByToken(photons_, photons);

  edm::Handle<std::vector<reco::Vertex>> hVtx;
  iEvent.getByToken(hVtx_ , hVtx);
  reco::Vertex primVertex;

  //informazioni bunch-crossing
  for (unsigned int i = 0; i< hPU->size();++i){
    if (hPU->at(i).getBunchCrossing() == 0) {
      truePU = hPU->at(i).getTrueNumInteractions(); 
    } 
  }

  //contatori di particelle per le particelle di interesse.
  int Ds = 0, K0bar = 0, Piplus = 0, Kplus = 0, Kminus = 0, W = 0, Gamma = 0, Phi = 0;
  int Kplus2 = 0, Kminus2 = 0, Piplus2 = 0;
  double pi_mass = 0.13957018;
  double K_mass = 0.493677;
  double DS_mass = 1.96835;
  double W_mass = 80.3932;    
  int id = 0, n = 0, m = 0, l = 0, t = 0;
  double Gamma_pt_tmp = 0;
  double Gamma_eta_tmp = 0;
  double Gamma_phi_tmp = 0;

  TLorentzVector WvectorGen;
  TLorentzVector DSvectorGen;
  TLorentzVector GammavectorGen;
  TLorentzVector K0barvectorGen;
  TLorentzVector PhivectorGen;
  TLorentzVector Kplus_vectorGen;
  TLorentzVector Kminus_vectorGen;
  TLorentzVector PiplusvectorGen;

  TLorentzVector Kplus_vectorGen2;
  TLorentzVector Kminus_vectorGen2;
  TLorentzVector PiplusvectorGen2;

  for (size_t i = 0; i < genParticles->size(); ++ i){
    const GenParticle & p = (*genParticles)[i];
    id = p.pdgId();
    if (id == 24){
      W++;
      m = p.numberOfDaughters();
      if (m == 2){
        W_pt_gen = p.pt();
        W_eta_gen = p.eta();
        W_phi_gen = p.phi(); 
        WvectorGen.SetPtEtaPhiM(W_pt_gen, W_eta_gen, W_phi_gen, W_mass);
        histContainer_["W_pt_gen"]->Fill(W_pt_gen);
        histContainer_["W_eta_gen"]->Fill(W_eta_gen);
        histContainer_["W_phi_gen"]->Fill(W_phi_gen);

        Ds = 0;
        Gamma = 0;
        for (int j = 0; j < m; j++){
          const Candidate * d = p.daughter( j );
          id = d->pdgId();
          if (id == 22){
            Gamma++;                        
            Gamma_pt_gen = d->pt();
            Gamma_eta_gen = d->eta();
            Gamma_phi_gen = d->phi();
            GammavectorGen.SetPtEtaPhiM(Gamma_pt_gen, Gamma_eta_gen, Gamma_phi_gen, 0.0);
            histContainer_["Gamma_pt_gen"]->Fill(Gamma_pt_gen);
            histContainer_["Gamma_eta_gen"]->Fill(Gamma_eta_gen);
            histContainer_["Gamma_phi_gen"]->Fill(Gamma_phi_gen);
          }
          else if (id == 431){
            Ds++;
            DS_pt_gen = d->pt();
            DS_eta_gen = d->eta();
            DS_phi_gen = d->phi(); 
            DSvectorGen.SetPtEtaPhiM(DS_pt_gen, DS_eta_gen, DS_phi_gen, DS_mass); 
            histContainer_["DS_pt_gen"]->Fill(DS_pt_gen);
            histContainer_["DS_eta_gen"]->Fill(DS_eta_gen);
            histContainer_["DS_phi_gen"]->Fill(DS_phi_gen);

            n = d->numberOfDaughters();
            if (n == 2){
              Kplus = 0; K0bar = 0; Phi = 0; Piplus2 = 0;
              for (int k = 0; k < n; k++){
                const Candidate * e = d->daughter( k );
                int id2 = e->pdgId();
                if (id2 == 321){
                  Kplus++;
                  Kplus_pt_gen = e->pt();
                  Kplus_eta_gen = e->eta();
                  Kplus_phi_gen = e->phi();
                  Kplus_vectorGen.SetPtEtaPhiM(Kplus_pt_gen, Kplus_eta_gen, Kplus_phi_gen, K_mass);
                  histContainer_["Kplus_pt_gen"]->Fill(Kplus_pt_gen);
                  histContainer_["Kplus_eta_gen"]->Fill(Kplus_eta_gen);
                  histContainer_["Kplus_phi_gen"]->Fill(Kplus_phi_gen);
                }
                if (id2 == 211){
                  Piplus2++;
                  Piplus_pt_gen2 = e->pt();
                  Piplus_eta_gen2 = e->eta();
                  Piplus_phi_gen2 = e->phi();
                  PiplusvectorGen2.SetPtEtaPhiM(Piplus_pt_gen2, Piplus_eta_gen2, Piplus_phi_gen2, pi_mass);
                  histContainer_["Piplus_pt_gen2"]->Fill(Piplus_pt_gen2);
                  histContainer_["Piplus_eta_gen2"]->Fill(Piplus_eta_gen2);
                  histContainer_["Piplus_phi_gen2"]->Fill(Piplus_phi_gen2);
                }
                else if(id2 == -313){
                  K0bar ++;
                  l = e->numberOfDaughters();
                  if(l == 2){
                    Kminus = 0;
                    Piplus = 0;
                    for (int s = 0; s < l; s++){
                      const Candidate * r = e->daughter( s );
                      int id3 = r->pdgId();
                      if (id3 == 211) { // Pi+
                        Piplus++;
                        Piplus_pt_gen = r->pt();
                        Piplus_eta_gen = r->eta();
                        Piplus_phi_gen = r->phi();
                        PiplusvectorGen.SetPtEtaPhiM(Piplus_pt_gen, Piplus_eta_gen, Piplus_phi_gen, pi_mass);
                        histContainer_["Piplus_pt_gen"]->Fill(Piplus_pt_gen);
                        histContainer_["Piplus_eta_gen"]->Fill(Piplus_eta_gen);
                        histContainer_["Piplus_phi_gen"]->Fill(Piplus_phi_gen);                             
                      }
                      else if (id3 == -321) { // K-
                        Kminus++;
                        Kminus_pt_gen = r->pt();
                        Kminus_eta_gen = r->eta();
                        Kminus_phi_gen = r->phi();
                        Kminus_vectorGen.SetPtEtaPhiM(Kminus_pt_gen, Kminus_eta_gen, Kminus_phi_gen, K_mass);
                        histContainer_["Kminus_pt_gen"]->Fill(Kminus_pt_gen);
                        histContainer_["Kminus_eta_gen"]->Fill(Kminus_eta_gen);
                        histContainer_["Kminus_phi_gen"]->Fill(Kminus_phi_gen);
                      }
                    }
                  }
                }
                else if(id2 == 333){
                  Phi++;
                  t = e->numberOfDaughters();
                  if(t == 2){
                    Kplus2 = 0;
                    Kminus2 = 0;
                    for (int x = 0; x < t; x++){
                      const Candidate * q = e->daughter( x );
                      int id4 = q->pdgId();
                      if (id4 == 321) { // K+
                        Kplus2++;
                        Kplus_pt_gen2 = q->pt();
                        Kplus_eta_gen2 = q->eta();
                        Kplus_phi_gen2 = q->phi();
                        Kplus_vectorGen2.SetPtEtaPhiM(Kplus_pt_gen2, Kplus_eta_gen2, Kplus_phi_gen2, K_mass);
                        histContainer_["Kplus_pt_gen2"]->Fill(Kplus_pt_gen2);
                        histContainer_["Kplus_eta_gen2"]->Fill(Kplus_eta_gen2);
                        histContainer_["Kplus_phi_gen2"]->Fill(Kplus_phi_gen2);
                      }
                      else if (id4 == -321) { // K-
                        Kminus2++;
                        Kminus_pt_gen2 = q->pt();
                        Kminus_eta_gen2 = q->eta();
                        Kminus_phi_gen2 = q->phi();
                        Kminus_vectorGen2.SetPtEtaPhiM(Kminus_pt_gen2, Kminus_eta_gen2, Kminus_phi_gen2, K_mass);
                        histContainer_["Kminus_pt_gen2"]->Fill(Kminus_pt_gen2);
                        histContainer_["Kminus_eta_gen2"]->Fill(Kminus_eta_gen2);
                        histContainer_["Kminus_phi_gen2"]->Fill(Kminus_phi_gen2);
                      }
                    }
                  }                 
                }
              }
            }
          }
        }
      }
    }
  }

  if(K0bar == 1 && Phi == 0){
    if(Kminus == 1 && Piplus == 1){
      K0barvectorGen = PiplusvectorGen + Kminus_vectorGen;
      K0bar_pt_gen = K0barvectorGen.Pt();
      K0bar_eta_gen = K0barvectorGen.Eta();
      K0bar_phi_gen = K0barvectorGen.Phi();
      //genTree->Fill();
      histContainer_["K0bar_pt_gen"]->Fill(K0bar_pt_gen);
      histContainer_["K0bar_eta_gen"]->Fill(K0bar_eta_gen);
      histContainer_["K0bar_phi_gen"]->Fill(K0bar_phi_gen);

      DeltaR_12_gen = Kplus_vectorGen.DeltaR(PiplusvectorGen);
      DeltaR_13_gen = Kplus_vectorGen.DeltaR(Kminus_vectorGen);
      DeltaR_23_gen = PiplusvectorGen.DeltaR(Kminus_vectorGen);
      histContainer_["Delta R GEN tra K+ e Pi+"]->Fill(DeltaR_12_gen);
      histContainer_["Delta R GEN tra K+ e K-"]->Fill(DeltaR_13_gen);
      histContainer_["Delta R GEN tra Pi+ e K-"]->Fill(DeltaR_23_gen);
    }
  }
  if(Phi == 1 && K0bar == 0){
    if(Kplus2 == 1 && Kminus2 == 1){
      PhivectorGen = Kplus_vectorGen2 + Kminus_vectorGen2;
      Phi_pt_gen = PhivectorGen.Pt();
      Phi_eta_gen = PhivectorGen.Eta();
      Phi_phi_gen = PhivectorGen.Phi();
      histContainer_["Phi_pt_gen"]->Fill(Phi_pt_gen);
      histContainer_["Phi_eta_gen"]->Fill(Phi_eta_gen);
      histContainer_["Phi_phi_gen"]->Fill(Phi_phi_gen);

      DeltaR_12_gen2 = Kplus_vectorGen2.DeltaR(PiplusvectorGen2);
      DeltaR_13_gen2 = Kplus_vectorGen2.DeltaR(Kminus_vectorGen2);
      DeltaR_23_gen2 = PiplusvectorGen2.DeltaR(Kminus_vectorGen2);
      histContainer_["Delta R GEN2 tra K+ e K-"]->Fill(DeltaR_13_gen2);
      histContainer_["Delta R GEN2 tra K+ e Pi+"]->Fill(DeltaR_12_gen2);
      histContainer_["Delta R GEN2 tra Pi+ e K-"]->Fill(DeltaR_23_gen2);
    }
  }

  /*************** RECO ************** */

  bool result = false;
  bool passTrig = true;
  if(hVtx->size() > 0){

    reco::TransientTrack  K1trans;
    reco::TransientTrack  pitrans;
    reco::TransientTrack  K2trans;
    std::vector<reco::TransientTrack> tks;

    TLorentzVector Dcandidates;
    vector<reco::Track> tracksVector;
    reco::Track temp;
    reco::Track tr1;
    reco::Track tr2;
    reco::Track tr3;

    reco::Track goodTrack1;
    reco::Track goodTrack2;
    reco::Track goodTrack3;

    TLorentzVector K1vector;
    TLorentzVector Pivector;
    TLorentzVector K2vector;
    TLorentzVector DSvector;
    TLorentzVector photonVector;
    TLorentzVector photonVector_tmp;
    TLorentzVector Wvector;
    TLorentzVector K0barvector;
    TLorentzVector Phivector;
    TLorentzVector Ds_candidate;

    reco::Track combinatorio_tracce[3]; 
    TransientVertex v;
    reco::Vertex primaryVertex;
    reco::Vertex primVertex_tmp;
    bool goodvertex = false;

    double bsx = 0, bsy = 0, bsz = 0;
    if ( beamSpotHandle.isValid() ){
      beamSpot = *beamSpotHandle;
      bsx = beamSpot.x0();
      bsy = beamSpot.y0();
      bsz = beamSpot.z0();
    }
    GlobalPoint BeamSpotGP(bsx, bsy, bsz);

    for(unsigned int t = 0; t < hVtx->size(); t++){
      primVertex_tmp = hVtx->at(t);
      if(!primVertex_tmp.isFake()  && primVertex_tmp.isValid() && primVertex_tmp.ndof() > 4 && fabs(primVertex_tmp.z()-bsz) < 10 ){
        goodvertex = true;
        primaryVertex = primVertex_tmp;
        break;
      }
    }

    if(goodvertex){

      double inv_mass_W_tmp = 0, diff_mass_W = 20, inv_mass_DS_tmp = 0; //queste sono variabili temporanee per aggiustare il riempimento
      double diff_cosphi = 1;
      int sameVertex = 0, mini = 0;
      double inv_mass1 = 0, sigma_L = 0, v_chi2 = 0, CL = 0;
      bool CAIR_ST = false;
      bool goodtracks = false, good = false;
      double deriv[3];
      double cov_sv[3][3];
      double cov_pv[3][3];
      double Lsusigma = 0, xprim = 0, yprim = 0, zprim = 0, xsec = 0, ysec = 0, zsec = 0, dx = 0, dy = 0, dz = 0, px = 0, py = 0, pz = 0, pi = 0, cosphi = 0, L = 0;
      int ntracks = 0;
      double diff_mass = 100;

      for (reco::TrackCollection::const_iterator track = tracks->begin();  track != tracks->end();  ++track){
        ntracks ++;
        if((track->pt() > 0.5) && 
          ((track->chi2())/(track->ndof()) <= 2.5) && 
          (track->numberOfValidHits() >= 5) && 
          (track->hitPattern().numberOfValidPixelHits() >= 2)  && 
          (track->quality(Track::highPurity))&& 
          fabs(track->dxy(primaryVertex.position())) < 0.1 && 
          fabs(track->dz(primaryVertex.position())) < 1) {
          tracksVector.push_back(*track);
        }
      }

      if (tracksVector.size() > 2){
        for (reco::TrackCollection::const_iterator track = tracksVector.begin();  track != tracksVector.end();  ++track) {
          for (reco::TrackCollection::const_iterator track1 = track+1; track1 != tracksVector.end(); ++track1){
            if  (fabs(track->vz() - track1->vz()) < 1){
              for (reco::TrackCollection::const_iterator track2 = track1+1; track2 != tracksVector.end(); ++track2){
                if  (fabs(track->vz() - track2->vz()) < 1 && fabs(track1->vz() - track2->vz()) < 1 ){
                  if (track->charge() + track1->charge() + track2->charge() == 1){
                    
                    combinatorio_tracce[0]=*track;
                    combinatorio_tracce[1]=*track1;
                    combinatorio_tracce[2]=*track2;

                    mini = 0;
                    for(int i = 0; i < 2; i++){
                      mini = i;
                      for(int j = i + 1; j < 3; j++) {
                      if(combinatorio_tracce[j].charge() > combinatorio_tracce[mini].charge()){
                        mini = j;
                        temp=combinatorio_tracce[mini];
                        combinatorio_tracce[mini]=combinatorio_tracce[i];
                        combinatorio_tracce[i]=temp;
                        }
                      }
                    }
                    // ++-
                    tr1 = combinatorio_tracce[0];
                    tr2 = combinatorio_tracce[1];
                    tr3 = combinatorio_tracce[2]; //qui ci va la particella negativa, che in questo decadimento è sicuramente una delle K

                    good = true;
                    K2vector.SetPtEtaPhiM(tr3.pt(), tr3.eta(), tr3.phi(), K_mass);
                    Pivector.SetPtEtaPhiM(tr1.pt(), tr1.eta(), tr1.phi(), pi_mass);
                    K1vector.SetPtEtaPhiM(tr2.pt(), tr2.eta(), tr2.phi(), K_mass);
                  
                    Ds_candidate = K1vector + Pivector + K2vector;
                    
                    K1trans  = (*theB).build(tr2);
                    pitrans = (*theB).build(tr1);
                    K2trans = (*theB).build(tr3);
                      
                    if (/*fabs(Ds_candidate.M() - DS_mass) < 0.3*/ Ds_candidate.M() >= 1.6 && Ds_candidate.M() <= 2.1){
                      v_chi2 = 0;
                      CL = 0;
                      sameVertex = 0;
                      
                      // ######### vertex fit ##########
                      tks.clear();
                      tks.push_back(K1trans);
                      tks.push_back(pitrans);
                      tks.push_back(K2trans);
                      KalmanVertexFitter kalman(true);
                      
                      if (tks.size() > 2){
                        if(good){ 
                          v = kalman.vertex(tks);
                          if(v.isValid()){
                            sameVertex++;
                            v_chi2 = v.normalisedChiSquared();
                            CL = TMath::Prob(v.totalChiSquared(),(int)v.degreesOfFreedom());
                            
                          }
                        }
                      }

                      if(sameVertex > 0 && CL > 0.005 && good == true){                        
                        xprim = primaryVertex.position().x();
                        yprim = primaryVertex.position().y();
                        zprim = primaryVertex.position().z();
                           
                        xsec = v.position().x();
                        ysec = v.position().y();
                        zsec = v.position().z();
                        
                        dx = xsec - xprim;
                        dy = ysec - yprim;
                        dz = zsec - zprim;
                        
                        L_abs = sqrt(pow(dx,2) + pow(dy,2) + pow(dz,2));
                        
                        px = Ds_candidate.Px();
                        py = Ds_candidate.Py();
                        pz = Ds_candidate.Pz();
                        pi = Ds_candidate.P();
                        
                        L = 0;
                        cosphi = (px*dx + py*dy + pz*dz)/(L_abs*pi);
                        cos_phi = 0;
    
                        cov_sv[0][0] = v.positionError().cxx();
                        cov_sv[1][0] = v.positionError().cyx();
                        cov_sv[2][0] = v.positionError().czx();
                        cov_sv[0][1] = cov_sv[1][0];
                        cov_sv[1][1] = v.positionError().cyy();
                        cov_sv[2][1] = v.positionError().czy();
                        cov_sv[0][2] = cov_sv[2][0];
                        cov_sv[1][2] = cov_sv[2][1];
                        cov_sv[2][2] = v.positionError().czz();

                        cov_pv[0][0] = primaryVertex.covariance(0,0);
                        cov_pv[1][0] = primaryVertex.covariance(1,0);
                        cov_pv[2][0] = primaryVertex.covariance(2,0);
                        cov_pv[0][1] = cov_pv[1][0];
                        cov_pv[1][1] = primaryVertex.covariance(1,1);
                        cov_pv[2][1] = primaryVertex.covariance(2,1);
                        cov_pv[0][2] = cov_pv[2][0];
                        cov_pv[1][2] = cov_pv[2][1];
                        cov_pv[2][2] = primaryVertex.covariance(2,2);
                        deriv[0] = dx/L_abs;
                        deriv[1] = dy/L_abs;
                        deriv[2] = dz/L_abs;
                        
                        if(cosphi > 0.90){
                          L = (px*dx + py*dy + pz*dz)/pi;
                          sigma_L = 0;
                          for (int m = 0; m < 3; ++m){
                            for (int n = 0; n < 3; ++n ){
                              sigma_L += deriv[m]*deriv[n]*(cov_pv[m][n] + cov_sv[m][n]);
                            }
                          }
                          sigma_L = sqrt(sigma_L);
                          L_err = sigma_L;
                          Lsusigma = L/sigma_L;
                          if(Lsusigma > 2.0){ 
                            if(passTrig == true && Ds_candidate.Pt() > 1. && fabs(Ds_candidate.Eta()) < 2.4 ){
                              if(fabs(cosphi - cos_phi) < diff_cosphi /*cosphi > 0.98*/){
                                diff_cosphi = fabs(cosphi - cos_phi);
                                if(cosphi > 0.98){
                                  Piplus_pt = Pivector.Pt();
                                  Piplus_eta = Pivector.Eta();
                                  Piplus_phi = Pivector.Phi();

                                  Kminus_pt = K2vector.Pt();
                                  Kminus_eta = K2vector.Eta();
                                  Kminus_phi = K2vector.Phi();

                                  Kplus_pt = K1vector.Pt();
                                  Kplus_eta = K1vector.Eta();
                                  Kplus_phi = K1vector.Phi();

                                  DeltaR_12 = K1vector.DeltaR(Pivector);
                                  DeltaR_13 = K1vector.DeltaR(K2vector);
                                  DeltaR_23 = Pivector.DeltaR(K2vector);

                                  DeltaR_Kplus_matching = K1vector.DeltaR(Kplus_vectorGen);
                                  DeltaR_Kminus_matching = K2vector.DeltaR(Kminus_vectorGen);
                                  DeltaR_Piplus_matching = Pivector.DeltaR(PiplusvectorGen);
                                  
                                  Gamma_pt_tmp = 0;
                                  Gamma_eta_tmp = 0;
                                  Gamma_phi_tmp = 0;
                                  for (reco::PhotonCollection::const_iterator photon = photons->begin();  photon != photons->end();  ++photon) {
                                    if(photon->pt() > 30){
                                      Gamma++;
                                      Gamma_pt_tmp = photon->pt();
                                      Gamma_eta_tmp = photon->eta();
                                      Gamma_phi_tmp = photon->phi();
                                      photonVector.SetPtEtaPhiM(Gamma_pt_tmp, Gamma_eta_tmp, Gamma_phi_tmp, 0.0);
                                      break;
                                    }
                                    
                                  } 
                                  
                                  DSvector = Ds_candidate;
                                  DS_pt = DSvector.Pt();
                                  DS_eta = DSvector.Eta();
                                  DS_phi = DSvector.Phi();

                                  Wvector = DSvector + photonVector;
                                  W_pt = Wvector.Pt();
                                  W_eta = Wvector.Eta();
                                  W_phi = Wvector.Phi();
                                  
                                  Gamma_pt = photonVector.Pt();
                                  Gamma_eta = photonVector.Eta();
                                  Gamma_phi = photonVector.Phi();

                                  CL_vertex = CL;
                                  vertex_size = hVtx->size();
                                  L_sigma = Lsusigma;
                                  passTrigger = passTrig;
                                  cos_phi = cosphi;
                                  //totalCandidates++;
                                }
                              }
                            }//pt D
                          }//Lsusigma > 3.0
                        }//cos phi > 0.9
                      }//CL SV
                    }//mass
                  }//if carica1
                }
              } //track2
            }
          }//track1
        }//track
        if(Wvector.M() >= 70 && Wvector.M() <= 90){ //QUESTA CONDIZIONE CAMBIA MOLTO IL RIEMPIMENTO
          
          histContainer_["Kplus_pt"]->Fill(Kplus_pt);
          histContainer_["Kplus_eta"]->Fill(Kplus_eta);
          histContainer_["Kplus_phi"]->Fill(Kplus_phi);
          
          histContainer_["Kminus_pt"]->Fill(Kminus_pt);
          histContainer_["Kminus_eta"]->Fill(Kminus_eta);
          histContainer_["Kminus_phi"]->Fill(Kminus_phi);
          
          histContainer_["Piplus_pt"]->Fill(Piplus_pt);
          histContainer_["Piplus_eta"]->Fill(Piplus_eta);
          histContainer_["Piplus_phi"]->Fill(Piplus_phi);
  
          histContainer_["Delta R tra K+ e Pi+"]->Fill(DeltaR_12);
          histContainer_["Delta R tra K+ e K-"]->Fill(DeltaR_13);
          histContainer_["Delta R tra Pi+ e K-"]->Fill(DeltaR_23);

          histContainer_["Delta R matching K+"]->Fill(DeltaR_Kplus_matching);
          histContainer_["Delta R matching K-"]->Fill(DeltaR_Kminus_matching);
          histContainer_["Delta R matching Pi+"]->Fill(DeltaR_Piplus_matching);
  
          histContainer_["W_pt"]->Fill(W_pt);
          histContainer_["W_eta"]->Fill(W_eta);
          histContainer_["W_phi"]->Fill(W_phi);
          histContainer_["W_mass"]->Fill(Wvector.M());
  
          histContainer_["Gamma_pt"]->Fill(photonVector.Pt());
          histContainer_["Gamma_eta"]->Fill(photonVector.Eta());
          histContainer_["Gamma_phi"]->Fill(photonVector.Phi());
  
          histContainer_["DS_pt"]->Fill(DS_pt);
          histContainer_["DS_eta"]->Fill(DS_eta);
          histContainer_["DS_phi"]->Fill(DS_phi);
          histContainer_["DS_mass"]->Fill(DSvector.M());
  
          histContainer_["Cos Phi"]->Fill(cos_phi);
          histContainer_["L/sigma"]->Fill(L_sigma);
          histContainer_["CL_vertex"]->Fill(CL_vertex);
          
          Tree->Fill();
        }
      }
    }//vertex good
  }//hVtx>0 
}

// ------------ method called once each job just before starting event loop  ------------
void analysis_W_plus_first_decay::beginJob(){ edm::Service<TFileService> fs;}

// ------------ method called once each job just after ending the event loop  ------------
void analysis_W_plus_first_decay::endJob(){}

// ------------ method called when starting to processes a run  ------------
void analysis_W_plus_first_decay::beginRun(edm::Run const&, edm::EventSetup const&){}

// ------------ method called when ending the processing of a run  ------------
void analysis_W_plus_first_decay::endRun(edm::Run const&, edm::EventSetup const&){}

// ------------ method called when starting to processes a luminosity block  ------------
void analysis_W_plus_first_decay::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// ------------ method called when ending the processing of a luminosity block  ------------
void analysis_W_plus_first_decay::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void analysis_W_plus_first_decay::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(analysis_W_plus_first_decay);
