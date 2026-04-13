#PDG IDs: 24 = W, 22 = Gamma, 431 = Ds, 321 = K+, 211 = pi+, 333 = mesone Phi

import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *
from Configuration.Generator.PSweightsPythia.PythiaPSweightsSettings_cfi import *

process = cms.Process("GEN") #inizializzazione del processo (necessaria)

# servizio di generazione di numeri casuali
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    generator = cms.PSet(
        initialSeed = cms.untracked.uint32(12345),
        engineName = cms.untracked.string('HepJamesRandom')
    )
)

process.source = cms.Source("EmptySource") #sorgente vuota per generare nuovi dati
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100)) #num. max eventi

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    comEnergy = cms.double(13000.0),
    maxEventsToPrint = cms.untracked.int32(1),
    PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,
        pythia8CP5SettingsBlock,
        pythia8PSweightsSettingsBlock,
        processParameters = cms.vstring(
            'WeakSingleBoson:ffbar2W = on',
            '24:onMode = off',
            '24:AddChannel = on 1.0 100 431 22', # W -> Ds + gamma
            '431:onMode = off',
            #'431:AddChannel = on 0.0537 0 321 -321 211',
            #'431:AddChannel = on 0.0221 0 333 211',
            #'333:onMode = off',
            #'333:onIfAll = 321 -321',
            '431:onIfMatch = 321 -313', # Ds -> (K+) + (K0bar) 
            '431:onIfMatch = 333 211' # Ds -> (Phi) + (pi+)

            #MODIFICHE PER PROVE:
            '-24:onMode = off',
            '-24:AddChannel = on 1.0 100 -431 22',
            '-431:onIfMatch = -321 -313', # Ds -> (K+) + (K0bar) 
            '-431:onIfMatch = 333 -211' # Ds -> (Phi) + (pi+)
        ),
        parameterSets = cms.vstring(
            'pythia8CommonSettings',
            'pythia8CP5Settings',
            'pythia8PSweightsSettings',
            'processParameters'
        )
    )
)

process.ProductionFilterSequence = cms.Sequence(process.generator)
process.p = cms.Path(process.ProductionFilterSequence) #definizione percorso di esecuzione

# modulo di output per scriver i dati in un file .root
process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('file:/afs/cern.ch/user/a/afilippu/CMSSW_10_6_18/src/work/Tesi/prova_pre_crab/prova_100_evnt.root'),
    outputCommands = cms.untracked.vstring('keep *')
)
process.outpath = cms.EndPath(process.output)
