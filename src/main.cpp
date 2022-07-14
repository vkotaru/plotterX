#include "TestDataTable.cpp"
#include "TestVariable.cpp"
#include "TestFuncEval.cpp"
#include "TestSurface.cpp"
#include "TestTimeCurve.cpp"
#include "TestGraphRenderer.cpp"
#include "TestAllModules.cpp"
#include "TestParser.cpp"

#include "PlotterX.h"

#include "TestModules.h"
#include "Errors.h"

int main() {

  PlotterX plotterX;
  int Terminate = 0;
  while (Terminate != YES) {
    Terminate = plotterX.Run();
  }

  return 0;
}