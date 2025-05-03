#include <TFile.h>
#include <TTree.h>
#include <TMVA/Factory.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Tools.h>
#include <TMVA/Reader.h>

void TMVA_PoCA() {
    // Init TMVA
    TMVA::Tools::Instance();

    // Output file
    TFile* outputFile = TFile::Open("TMVA_PoCA.root", "RECREATE");

    // Create Factory and DataLoader
    TMVA::Factory* factory = new TMVA::Factory("TMVA_PoCA", outputFile,
        "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression");

    TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

    // Load your input ROOT file
    TFile* input = TFile::Open("out.root");  // Replace with your file name
    TTree* tree = (TTree*)input->Get("groundTruthPoCA");      // Replace with your tree name

    // Add variables (input features)
    dataloader->AddVariable("inX", 'F');
    dataloader->AddVariable("inY", 'F');
    dataloader->AddVariable("inZ", 'F');
    dataloader->AddVariable("dInX", 'F');
    dataloader->AddVariable("dInY", 'F');
    dataloader->AddVariable("dInZ", 'F');
    dataloader->AddVariable("outX", 'F');
    dataloader->AddVariable("outY", 'F');
    dataloader->AddVariable("outZ", 'F');
    dataloader->AddVariable("dOutX", 'F');
    dataloader->AddVariable("dOutY", 'F');
    dataloader->AddVariable("dOutZ", 'F');

    // Regression targets (PoCA coordinates)
    dataloader->AddTarget("pocaX");
    //dataloader->AddTarget("pocaY");
    //dataloader->AddTarget("pocaZ");

    // Add Tree to dataloader
    dataloader->AddRegressionTree(tree, 1.0);

    // Prepare training/testing
    dataloader->PrepareTrainingAndTestTree("", "",
        "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V");

    // Book a regression method — e.g., BDT or DNN
    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
        "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=Grad:UseBaggedBoost:"
        "BaggedSampleFraction=0.5:nCuts=20:PruneMethod=NoPruning");


    /*factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN",
    "H:!V:ErrorStrategy=SUMOFSQUARES:VarTransform=N:"
    "Layout=RELU|128,RELU|64,LINEAR:"
    "TrainingStrategy=LearningRate=1e-3,Momentum=0.9,"
    "Repetitions=1,ConvergenceSteps=20,BatchSize=256,"
    "TestRepetitions=1,MaxEpochs=100");
*/
    // You can also try deep neural networks:
    /*
    factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN",
        "H:!V:VarTransform=N:ErrorStrategy=CROSSENTROPY:Layout=TANH|128,TANH|64,LINEAR:"
        "TrainingStrategy=LearningRate=1e-3,Momentum=0.9,Repetitions=1,"
        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=1,MaxEpochs=100,DropConfig=0.0+0.0+0.0,"
        "WeightDecay=1e-5");
    */

    // Train, Test, Evaluate
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    // Clean up
    outputFile->Close();
    delete factory;
    delete dataloader;
}

