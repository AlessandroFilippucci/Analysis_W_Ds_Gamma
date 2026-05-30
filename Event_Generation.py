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
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000)) #num. max eventi

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    comEnergy = cms.double(13000.0),
    maxEventsToPrint = cms.untracked.int32(0),
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
            '431:onIfMatch = 333 211', # Ds -> (Phi) + (pi+)

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

process.EtaWFilter = cms.EDFilter("MCParticlePairFilter",
    MaxEta = cms.untracked.vdouble(3.0, 3.0),
    MinEta = cms.untracked.vdouble(-3.0, -3.0),
    ParticleID1 = cms.untracked.vint32(24, -24),
    ParticleID2 = cms.untracked.vint32(24, -24),
)

process.ProductionFilterSequence = cms.Sequence(process.generator * process.EtaWFilter)
process.p = cms.Path(process.ProductionFilterSequence) #definizione percorso di esecuzione

# modulo di output per scrivere i dati in un file .root
process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('file:test_0_1.root'),
    outputCommands = cms.untracked.vstring('keep *')
)

# Aggiungi un filtro di output per applicare il filtro prima di scrivere gli eventi
process.output.SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('p')
)

process.outpath = cms.EndPath(process.output)

# Aggiungi il modulo di output al percorso di esecuzione
process.schedule = cms.Schedule(process.p, process.outpath)