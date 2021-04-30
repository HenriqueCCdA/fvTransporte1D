
#include"../include/Mesh.h"
#include"../include/TriaSolver.h"
#include"../include/EpdSolver.h"
#include"../include/Files.h"
#include"../include/CellLoop.h"
#include"../include/RunTimes.h"
#include"../include/GerenciadoDeMemoria.h"
#include"../include/GlobalVar.h"
#include"../include/Writer.h"

int main(int argc, char *argv[]) {

  Files files;
  IntTemp intTemp;
  Mesh mesh(&intTemp);

  // ... 
  files.set_nameIn("temperatura.dat");
  files.read(mesh, intTemp);
  mesh.display();
  // ............................................................................

  // ...
//Writer *writer = new WriterTxt(&mesh, &intTemp, files.get_nameOut());
  Writer *writer = new WriterVTK(&mesh, &intTemp, files.get_nameOut());
  // ............................................................................
  // ... 
  DataStruct *data = new TriaDiagonal(mesh.get_nCells());
  Solver *solver = new TriSolver(data);
  // ............................................................................

  // ... 
  mesh.grid();
  // ............................................................................

  // ...
  CellLoop *heatCell1D = new CellHeatLoop(solver, &mesh, &intTemp);
  // ............................................................................

  // 
  EpdSolver epd(&mesh, &intTemp, heatCell1D, solver, writer);
  // ............................................................................
  
  //
  epd.init();
  // ............................................................................
  
  writer->write();
  return 0;

  // ...
  epd.solver();
  // ............................................................................ 

  // ...
  writer->closeOutputFile();
  // ............................................................................

  // ...  
  cout << "Time Sist(s)   : " 
       << fixed << setprecision(4) << times.get_sist() << endl
       << "Time Solver(s) : " 
       << fixed << setprecision(4) << times.get_solver() << endl
       << "Time Wres(s)   : " 
       << fixed << setprecision(4) << times.get_res() << endl;
  // ............................................................................

  return 0;

}