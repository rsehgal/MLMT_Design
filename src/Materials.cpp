/*
**	Filename : Materials.cpp
**	2024-01-02
**	username : rsehgal
*/
#include "Materials.h"
#include <G4Color.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4OpticalSurface.hh>
#include <G4SurfaceProperty.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>

Materials *Materials::s_instance = 0;

Materials *Materials::Instance() {
  if (!s_instance)
    s_instance = new Materials;
  return s_instance;
}

Materials::Materials() {
#ifdef ICNSE_FILL_COLOUR
  fColor["G4_Pb"] = new G4VisAttributes(G4Colour(0.5, 0.5, 0, 1));
  fColor["ICNSE_BP"] = new G4VisAttributes(G4Colour(0.5, 1, 0.6, 1));
  fColor["ICNSE_HDPE"] = new G4VisAttributes(G4Colour(1, 0.5, 1, 1));
  fColor["ICNSE_PS"] = new G4VisAttributes(G4Colour(0., 1, 0, 1));
  //fColor["G4_Cu"] = new G4VisAttributes(G4Colour(1., 1, 0, 01));
  fColor["G4_Cu"] = new G4VisAttributes(G4Colour(1.,1.,0.,0.8));
  fColor["G4_Fe"] = new G4VisAttributes(G4Colour(1., 0, 0, 1));
  //fColor["G4_Galactic"] = new G4VisAttributes(G4Colour::Yellow());
  fColor["G4_Al"] = new G4VisAttributes(G4Colour(1.,0.,1.,.6));
#endif

  CreateBoratedPolyethylene();
  CreateHighDensityPolyethylene();
  CreateScintillatorMaterial();
}

Materials::~Materials() {}

std::map<G4String, G4VisAttributes *> Materials::GetColorMap() const { return fColor; }

/*
** Add the new function corresponding to desired material
**
** Below are the examples to add BoratedPolyethylene and
** High density Polyethylene
*/

void Materials::CreateBoratedPolyethylene() {

  // G4double density = 0.95 * g / cm3;
  G4double density = 1.04 * g / cm3;
  fBP = new G4Material("BoratedPolyethylene", density, 2);
  /* Define elements and materials (if not already defined)
  ** We are trying to define Borated Polyethylene with required % of Boron
  */
  // G4Element *elB = new G4Element("Boron", "B", 5, 10.811 * g / mole);
  G4Material *elB = G4NistManager::Instance()->FindOrBuildMaterial("G4_B");
  // fBP->AddElement(elB, 0.05); // 15% Boron
  fBP->AddMaterial(elB, 0.05); // 15% Boron

  G4Material *polyethylene = G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE");
  fBP->AddMaterial(polyethylene, 0.95);

  /*
  ** Very important line to add the newly created material to the map
  ** to be searched while creating the materials in detector constrution
  */
  fMaterialMap["ICNSE_BP"] = fBP;
}

void Materials::CreateHighDensityPolyethylene() {
  // double density = 0.95 * g / cm3;
  double density = 0.97 * g / cm3;
  G4NistManager *nistManager = G4NistManager::Instance();
  nistManager->BuildMaterialWithNewDensity("HighDensityPolyethylene", "G4_POLYETHYLENE", density);
  fHDPE = G4NistManager::Instance()->FindOrBuildMaterial("HighDensityPolyethylene");
  fMaterialMap["ICNSE_HDPE"] = fHDPE;
}

void Materials::CreateScintillatorMaterial() {
  G4NistManager *nistManager = G4NistManager::Instance();
  G4Material *scintMaterial = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
  AttachScintillatorOpticalProperties(scintMaterial);
#endif
  fMaterialMap["ICNSE_PS"] = scintMaterial;
}

#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
void Materials::AttachScintillatorOpticalProperties(G4Material *material) {

#if(0)
  std::vector<G4double> reflectivity = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,
                                        1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  std::vector<G4double> photonEnergy = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
      2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
      2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

  std::vector<G4double> refractiveIndex1 = {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                            1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                            1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};

  std::vector<G4double> absorption = {3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m,
                                      3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m,
                                      3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m,
                                      3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m, 3.8 * m};
  /*{
        3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m,  12.346 * m, 13.889 * m, 15.152 * m, 17.241 * m,
        18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m, 45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m,
        55.556 * m, 52.632 * m, 52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
        30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m, 17.500 * m, 14.500 * m};*/

  std::vector<G4double> scintilFast = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                                       1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                                       1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

  std::vector<G4double> scintilSlow = {0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
                                       7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00, 4.00,
                                       5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 5.00, 4.00};

  G4MaterialPropertiesTable *myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex1)->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorption)->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast)->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT", photonEnergy, scintilSlow)->SetSpline(true);
  myMPT1->AddProperty("REFLECTIVITY", photonEnergy, reflectivity);

  myMPT1->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 0.9 * ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT", 2.1 * ns);
  myMPT1->AddConstProperty("YIELDRATIO", 0.8);
#endif

auto myMPT1 = new G4MaterialPropertiesTable();
// Photon energy array (in eV)
const G4int nEntries = 2;
/*
//Working
G4double photonEnergy[nEntries] = {2.95 * eV, 3.26 * eV};  // 415 nm to 380 nm

// Refractive index for NaI(Tl)
G4double refractiveIndex[nEntries] = {1.85, 1.85};
myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);

// Absorption length (in mm)
G4double absorptionLength[nEntries] = {2600. * mm, 2600. * mm};
myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorptionLength, nEntries);

// Emission spectrum for fast and slow components
G4double scintilFast[nEntries] = {0.1, 0.1};
G4double scintilSlow[nEntries] = {0.9, 0.9};
myMPT1->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintilFast, nEntries);
myMPT1->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintilSlow, nEntries);

// Set scintillation yield and time constants
myMPT1->AddConstProperty("SCINTILLATIONYIELD", 1000. / MeV);
myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
myMPT1->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 0.9 * ns);
myMPT1->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 2.1 * us);
myMPT1->AddConstProperty("SCINTILLATIONYIELD1", 0.1);
myMPT1->AddConstProperty("SCINTILLATIONYIELD2", 0.9);
*/

{
 G4double PhotonEnergy[nEntries]= {2.0*eV, 3.5*eV};
 G4double FastComponent[nEntries] = {1.0, 1.0}; // 100% fast component
G4double RefractiveIndex[nEntries] = {1.58, 1.58}; // Typical for plastic scintillators
G4double AbsorptionLength[nEntries] = {380*cm, 380*cm}; // Attenuation length in plastic scintillator

// Create Material Properties Table
myMPT1->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy, FastComponent, nEntries);
myMPT1->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
myMPT1->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionLength, nEntries);
myMPT1->AddConstProperty("SCINTILLATIONYIELD", 10000./MeV);
myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
myMPT1->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1*ns); // Fast decay time
myMPT1->AddConstProperty("SCINTILLATIONYIELD1", 1.);
//myMPT1->AddConstProperty("YIELDRATIO", 1.0); // No slow component
}
  material->SetMaterialPropertiesTable(myMPT1);
  /*
  ** Below line is most important which finally adds the material
  ** to Material map, so that the optical Plastic scintillator can
  ** be directly utilized
  */
  //fMaterialMap["ICNSE_PS"] = material;
  /*
  ** Taking this line inside Create scintillator material, so that we
  ** we can simply stop optical photon generator without changing material
  ** of scintillator
  */
}
#endif

#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
G4SurfaceProperty *Materials::GetMirror(G4String mirrorName) {

  G4double energy[2] = {1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2};
  G4double reflectivity[2] = {1.0, 1.0};
  G4OpticalSurface *optSurface = new G4OpticalSurface(mirrorName);

  optSurface->SetType(dielectric_metal);
  optSurface->SetFinish(ground);
  optSurface->SetModel(unified);

  G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
  mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
  optSurface->SetMaterialPropertiesTable(mptMirror);
  return optSurface;
}

G4SurfaceProperty *Materials::GetOpticalSurface(G4String surfaceName) {
  G4OpticalSurface *opticalSurface = new G4OpticalSurface(surfaceName);
  opticalSurface->SetType(dielectric_dielectric);
  opticalSurface->SetFinish(polished);
  opticalSurface->SetModel(unified);

  // Set reflectivity and efficiency properties
  // G4double reflectivity = 0.98; // Adjust as needed
  // G4double efficiency = 1.0;    // Adjust as needed

  std::vector<G4double> reflectivity = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,
                                        1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  std::vector<G4double> photonEnergy = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
      2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
      2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

  G4MaterialPropertiesTable *surfaceProperties = new G4MaterialPropertiesTable();
  // surfaceProperties->AddProperty("REFLECTIVITY",reflectivity,1);
  surfaceProperties->AddProperty("REFLECTIVITY", photonEnergy, reflectivity);
  // surfaceProperties->AddProperty("EFFICIENCY", new G4double[]{efficiency}, 1);

  opticalSurface->SetMaterialPropertiesTable(surfaceProperties);
  return opticalSurface;
}
#endif

G4Material *Materials::GetBP() const { return fBP; }
G4Material *Materials::GetHDPE() const { return fHDPE; }

G4Material *Materials::FindOrBuildMaterial(G4String material) {
  G4Material *mat = G4NistManager::Instance()->FindOrBuildMaterial(material);
  if (mat) {
    // AttachAirOpticalProperties(mat);
    return mat;
  } else {
    if (fMaterialMap.find(material) != fMaterialMap.end()) {
      std::cout << "RAMANN : Material Found : " << fMaterialMap[material] << std::endl;
      // AttachAirOpticalProperties(fMaterialMap[material]);

      return fMaterialMap[material];
    } else {
      std::cout << "SEHGALL : Material Not Found ..." << std::endl;
      return nullptr;
    }
  }
}
#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
void Materials::AttachAirOpticalProperties(G4Material *material) {

  std::vector<G4double> photonEnergy = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
      2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
      2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

  std::vector<G4double> refAir = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,
                                  1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  G4MaterialPropertiesTable *Air_MPT = new G4MaterialPropertiesTable();
  Air_MPT->AddProperty("RINDEX", photonEnergy, refAir,photonEnergy.size());//->SetSpline(true);
  material->SetMaterialPropertiesTable(Air_MPT);
}
#endif
