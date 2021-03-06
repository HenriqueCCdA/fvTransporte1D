
#include"../include/Mesh.h"
#include"../include/TriaSolver.h"
#include"../include/EpdSolver.h"
#include"../include/Files.h"
#include"../include/CellDiffLoop.h"
#include"../include/RunTimes.h"
#include"../include/GMemoria.h"
#include"../include/GlobalVar.h"
#include"../include/Writer.h"
#include"../include/Reader.h"


int main(int argc, char *argv[]) {

  Files files;
  IntTemp intTemp;
  Mesh<FieldDif> mesh(&intTemp);
  Reader<FieldDif> simple;

  // ... 
  files.set_nameIn("temperatura.dat");
  simple.read(mesh, intTemp, files);
  mesh.display();
  // ............................................................................

  // ...
  Writers<FieldDif> writers;
  Writer *writer = writers.select(&mesh, &intTemp, files.get_prefixNameOut()
                                , typeWriters::typeVTK);
  // ............................................................................
  // ... 
  DataStruct *data = new TriaDiagonal(mesh.get_nCells());
  Solver *solver = new TriSolver(data);
  // ............................................................................

  // ... 
  mesh.grid();
  // ............................................................................

  // ...
  CellLoop *heatCell1D = new CellDiffLoop(solver, &mesh, &intTemp);
  // ............................................................................

  // 
  EpdSolver<FieldDif> epd(&mesh, &intTemp, heatCell1D, solver, writer);
  // ............................................................................

  //
  epd.init();
  // ............................................................................

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

  // ... desinstanciando objetos
  delete heatCell1D;
  delete solver;
  delete data;
  delete writer;
  // ............................................................................

  return 0;

}