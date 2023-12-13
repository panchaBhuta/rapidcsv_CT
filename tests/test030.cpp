// test030.cpp - delete rows, no row/column labels

#include <rapidcsv/rapidcsv.h>
#include "unittest.h"

int main()
{
  int rv = 0;

  std::string csvref =
    "3,9,81,6561\n"
    "4,16,256,65536\n"
  ;

  std::string csv =
    "2,4,16,256\n"
    "3,9,81,6561\n"
    "4,16,256,65536\n"
    "5,25,625,390625\n"
  ;

  std::string path = unittest::TempPath();
  unittest::WriteFile(path, csv);

  try
  {
    rapidcsv::Document doc(path, rapidcsv::LabelParams(rapidcsv::FlgColumnName::CN_MISSING, rapidcsv::FlgRowName::RN_MISSING));

    doc.RemoveRow(3);
    doc.RemoveRow(0);

    doc.Save();

    std::string csvread = unittest::ReadFile(path);

    unittest::ExpectEqual(std::string, csvref, csvread);
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    rv = 1;
  }

  unittest::DeleteFile(path);

  return rv;
}
