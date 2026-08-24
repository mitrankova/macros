#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

void MakeTpcField3DCoefficients(
    const std::string& outputFile = "/sphenix/user/mitrankova/macros/TpcProduction/tpc_field3d_coefficients.root",
    const std::string& inputTextFile = "")
{
  std::vector<std::tuple<int, double, double>> coefficients = {
      {76905, 0.0, 0.0},
      {79513, 1.0, 1.6},
  };

  if (!inputTextFile.empty())
  {
    coefficients.clear();

    std::ifstream input(inputTextFile);
    if (!input.is_open())
    {
      std::cerr << "MakeTpcField3DCoefficients - could not open " << inputTextFile << std::endl;
      return;
    }

    std::string line;
    while (std::getline(input, line))
    {
      if (line.empty() || line[0] == '#')
      {
        continue;
      }

      int runnumber = 0;
      double field3DSide0 = 0.0;
      double field3DSide1 = 0.0;
      std::istringstream lineStream(line);
      if (lineStream >> runnumber >> field3DSide0 >> field3DSide1)
      {
        coefficients.emplace_back(runnumber, field3DSide0, field3DSide1);
      }
    }
  }

  TFile output(outputFile.c_str(), "RECREATE");
  if (output.IsZombie())
  {
    std::cerr << "MakeTpcField3DCoefficients - could not create " << outputFile << std::endl;
    return;
  }

  int runnumber = 0;
  double field3DSide0 = 0.0;
  double field3DSide1 = 0.0;

  TTree tree("field3DCoefficients", "TPC 3D field coefficients by run");
  tree.Branch("runnumber", &runnumber, "runnumber/I");
  tree.Branch("field3DSide0", &field3DSide0, "field3DSide0/D");
  tree.Branch("field3DSide1", &field3DSide1, "field3DSide1/D");

  for (const auto& coefficient : coefficients)
  {
    runnumber = std::get<0>(coefficient);
    field3DSide0 = std::get<1>(coefficient);
    field3DSide1 = std::get<2>(coefficient);
    tree.Fill();
  }

  tree.Write();
  output.Close();

  std::cout << "MakeTpcField3DCoefficients - wrote " << coefficients.size()
            << " runs to " << outputFile << std::endl;
}
