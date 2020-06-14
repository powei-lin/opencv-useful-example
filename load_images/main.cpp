#include <iostream>
#include <string>
#include <vector>

#include <opencv2/highgui.hpp>   // for imshow
#include <opencv2/imgcodecs.hpp> // for imread

using namespace std;
using namespace cv;

void load_data(string &path, vector<Mat> &images) {
  vector<string> file_names;
  cv::glob(path, file_names);
  size_t s = file_names.size();
  images.resize(s);
  cout << "Start loading" << endl;
  for (size_t i = 0; i < s; ++i) {
    images[i] = imread(file_names[i]);
  }
  cout << "End loading" << endl;
}

void load_data_parallel(string &path, vector<Mat> &images, int threads = -1) {
  vector<string> file_names;
  cv::glob(path, file_names);
  size_t s = file_names.size();
  images.resize(s);
  cout << "Start loading" << endl;
  parallel_for_(
      Range(0, s),
      [&](const Range &range) {
        for (int i = range.start; i < range.end; i++) {
          images[i] = imread(file_names[i]);
        }
      },
      threads);
  cout << "End loading" << endl;
}

int main() {
  string img_folder_path = "../images/*.jpg";
  vector<Mat> images;
  load_data(img_folder_path, images);
  for (const auto &img : images) {
    imshow("test", img);
    waitKey(0);
  }
}