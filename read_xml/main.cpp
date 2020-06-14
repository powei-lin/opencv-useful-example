#include <iostream>
#include <string>

#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

int main() {
  string distort_param_file_path = "../distortion.xml";
  string intrinsic_param_file_path = "../intrinsics.xml";

  FileStorage fs0(distort_param_file_path, FileStorage::READ);
  FileStorage fs1(intrinsic_param_file_path, FileStorage::READ);

  Mat distort_param, intrinsic_param;
  fs0["Distortion"] >> distort_param;
  fs1["Intrinsics"] >> intrinsic_param;
  cout << "Distortion:\n" << distort_param << endl;
  cout << "Camera intrinsic:\n" << intrinsic_param << endl;

  fs0.release();
  fs1.release();
}