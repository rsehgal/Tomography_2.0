// See: https://root.cern.ch/selecting-dictionary-entries-linkdefh
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link C++ all functions;
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedef;

#pragma link C++ class Data+;
#pragma link C++ class std::vector<Data*>+;
#pragma link C++ class Vector3D+;
#pragma link C++ class std::vector<Vector3D>+;

#endif
