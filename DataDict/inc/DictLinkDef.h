// See: https://root.cern.ch/selecting-dictionary-entries-linkdefh
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link C++ all functions;
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedef;

#pragma link C++ namespace lite_interface;
#pragma link C++ defined_in namespace lite_interface;


#pragma link C++ class lite_interface::A+;
#pragma link C++ class std::vector<lite_inteface::A*>+;
#pragma link C++ class lite_interface::B+;
#pragma link C++ class Data+;
#pragma link C++ class std::vector<Data*>+;
#pragma link C++ struct Vector3D+;

#endif
