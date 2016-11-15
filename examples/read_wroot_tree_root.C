//
//  This script shows how to read with CERN-ROOT the wroot_tree.root
// file containing TTrees produced by the wroot_tree.cpp program.
//

bool plot(TH1D& a_h) {
  TCanvas* plotter = new TCanvas("canvas","",10,10,800,600);
  plotter->Divide(1,1);  

  plotter->cd(1);
  a_h.Draw();

  plotter->Update();

  return true;
}

void read_wroot_tree_root() {

  ////////////////////////////////////////////////////////
  /// create histo : /////////////////////////////////////
  ////////////////////////////////////////////////////////
  TH1D* hrg = new TH1D("hrg","Rand gauss",100,-5,5);

  ////////////////////////////////////////////////////////
  /// read data an fill histo : //////////////////////////
  ////////////////////////////////////////////////////////
  TFile* f = new TFile("wroot_tree.root");

  ////////////////////////////////////////////////////////
  /// TTree produced with wroot::tree ////////////////////
  ////////////////////////////////////////////////////////
 {TTree* tree = (TTree*)f->Get("tree");
  if(!tree) {
    std::cout << " TTree tree not found." << std::endl;    
    return;
  }

 {TObjArray* brs = tree->GetListOfBranches();
  for(int i=0;i<brs->GetEntries();i++) {
    TBranch* b = (TBranch*)brs->At(i);
    std::cout << " Event branch : " << b->GetName()
    	      << std::endl;    
  }}
  TBranch* b = (TBranch*)tree->GetBranch("branch");
  if(!b) {
    std::cout << " TBranch branch not found." << std::endl;    
    return;
  }
  TLeaf* leaf_index = b->GetLeaf("index");
  if(!leaf_index) {
    std::cout << " TLeaf index not found." << std::endl;    
    return;
  }
  TLeaf* leaf_rgauss = b->GetLeaf("rgauss");
  if(!leaf_index) {
    std::cout << " TLeaf rgauss not found." << std::endl;    
    return;
  }

  int index;
  leaf_index->SetAddress(&index);
  double rgauss;
  leaf_rgauss->SetAddress(&rgauss);

  int num = tree->GetEntries();  
  std::cout << " number of events = " << num << std::endl;

  for(int i=0;i<num;i++) {
    tree->GetEntry(i);
    if(index!=i) {
      std::cout << "problem to read index branch at entry " << i
                << ". Found index was " << index << "."
                << std::endl;
      break;
    }
    //std::cout << "debug : " << rgauss << std::endl;
    hrg->Fill(rgauss,1);
  }}

  ////////////////////////////////////////////////////////
  /// plot histogram : ///////////////////////////////////
  ////////////////////////////////////////////////////////
  plot(*hrg);

}
