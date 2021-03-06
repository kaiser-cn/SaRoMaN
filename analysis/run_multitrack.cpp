// #include "GoldCuts_Analysis.h"
#include "GoldCuts_TrajSel.h"
#include "Train_TMVA.h"
#include "Run_TMVA.h"
#include "Run_CCTMVA.h"
#include "Train_NDTMVA.h"
#include "Run_NDTMVA.h"



#include <bhep/gstore.h>
#include <bhep/sreader.h>

int main(int argc, char* argv[]) {

  std::string param_file;
  std::string outFileName;

  if ( argc == 4 ) { param_file = argv[1]; outFileName = argv[2]; }
  else if ( argc == 2) { param_file = argv[1]; }
  else {

    std::cout << "Execute as: ./run_analysis <parameter file> <outfile> <seed>" << std::endl;

    return -1;
  }

  bhep::gstore run_store;

  //Read run and cut parameters.
  bhep::sreader reader1(run_store);
  reader1.file(param_file);
  reader1.group("RUN");
  reader1.read();
  bhep::sreader reader2(run_store);
  reader2.file(param_file);
  reader2.group("CUT");
  reader2.read();
  //Add the seed to the store.
  //
  // GoldCuts_Analysis run1( run_store );
  if(run_store.find_istore("TrainTMVA")) {
    std::cout<<"Will use multivariate analysis"<<std::endl;
    int train_TMVA = run_store.fetch_istore("TrainTMVA");
  
    if(train_TMVA == 0){ 
      // std::cout<<"Add the seed to the store."<<std::endl;
      // run_store.store("outFile", outFileName );
      // run_store.store("seed", strtod( argv[3], NULL ) );
      // std::cout<<"Added the seed to the store."<<std::endl;
      Run_TMVA run1( run_store );
      run1.execute();
      run1.finalize();
    }
    else if(train_TMVA == -1){
      std::cout<<"Run track specific CC analysis"<<std::endl;
      Run_CCTMVA run1( run_store );
      run1.execute();
      run1.finalize();
    }
    else if(train_TMVA == 1){
      std::cout<<"Start training the analysis"<<std::endl;
      Train_TMVA run1( run_store );
      run1.execute(); 
      run1.finalize();
    }
    else if(train_TMVA == -2){
      std::cout<<"Run track specific CC analysis"<<std::endl;
      Run_NDTMVA run1( run_store );
      run1.execute();
      run1.finalize();
    }
    else if(train_TMVA == 2){
      std::cout<<"Start training the analysis"<<std::endl;
      Train_NDTMVA run1( run_store );
      run1.execute(); 
      run1.finalize();
    }
  }
  else if( argc == 4 ) { 
    
    run_store.store("outFile", outFileName );
    run_store.store("seed", strtod( argv[3], NULL ) );

    GoldCuts_TrajSel run1( run_store );
    run1.execute();
    run1.finalize();

  }
  
  return 0;
}
