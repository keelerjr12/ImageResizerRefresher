// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "processing.h"
#include "Matrix_test_helpers.h"
#include "Image_test_helpers.h"

using namespace std;
using namespace MatrixNS;

void test_all(string prefix, int sizes[], int num_sizes);
void test_rotate(const Image *img, string prefix);
void test_energy(const Matrix *energy_mat, string prefix);
void test_cost(const Matrix *cost_mat, string prefix);
void test_find_seam(const int seam[], int n, string prefix);
void test_remove_seam(const Image* img, const int seam[],
                             string prefix);
void test_seam_carve(const Image *img, string prefix,
                            int new_width, int new_height);

static Matrix load_matrix(string filename);
static void write_matrix(const Matrix* mat, string filename);
static Image load_image(string filename);
static void write_image(const Image* img, string filename);
static void load_seam(int seam[], string filename);
static void write_seam(const int seam[], int len, string filename);

const string DATA_FOLDER = "data";
const string OUT_PPM_EXT = ".out.ppm";
const string OUT_TXT_EXT = ".out.txt";

int main(int argc, char *argv[]){
  if (argc > 2 ||
      (argc == 2&&
       strcmp(argv[1], "dog") &&
       strcmp(argv[1], "crabster") &&
       strcmp(argv[1], "horses"))) {
    cout << "Usage: " << argv[0] << " [dog|crabster|horses]" << endl;
    return 1;
  }

  string which_test = argc == 2 ? argv[1] : "all";

  if (which_test == "all" || which_test == "dog") {
    int dog_sizes[] = {4, 5};
    test_all("dog", dog_sizes, 1);
  }
  if (which_test == "all" || which_test == "crabster") {
    int crabster_sizes[] = {50, 45, 70, 35};
    test_all("crabster", crabster_sizes, 2);
  }
  if (which_test == "all" || which_test == "horses") {
    int horses_sizes[] = {300, 382, 400, 250};
    test_all("horses", horses_sizes, 2);
  }
}

void test_all(string prefix, int sizes[], int num_sizes){
  auto img = load_image(DATA_FOLDER + "/" + prefix + ".ppm");

  // Test rotate
  test_rotate(&img, prefix);

  // Test energy
  auto energy = compute_energy_matrix(&img);
  test_energy(&energy, prefix);

  // Test cost
  auto cost = compute_vertical_cost_matrix(&energy);
  test_cost(&cost, prefix);

  // Test find seam
  int seam[MAX_MATRIX_HEIGHT];
  find_minimal_vertical_seam(&cost, seam);
  test_find_seam(seam, cost.get_height(), prefix);

  // Test remove seam
  test_remove_seam(&img, seam, prefix);

  // Test full seam carving algorithm on various sizes
  for(int i = 0; i < num_sizes; ++i){
    test_seam_carve(&img, prefix, sizes[2*i], sizes[2*i + 1]);
  }

  cout << prefix << " tests PASS" << endl << endl;
}

void test_rotate(const Image *img, string prefix){
  auto rotated_img = Image(*img);

  // Test left rotation
  cout << "Testing " << prefix << " rotate left..." << flush;
  rotate_left(&rotated_img);
  write_image(&rotated_img, DATA_FOLDER + "/" + prefix + "_left" + OUT_PPM_EXT);

  auto rotated_img_correct = load_image(DATA_FOLDER + "/" + prefix + "_left.correct.ppm");
  assert(Image_equal(&rotated_img, &rotated_img_correct));
  cout << "PASS" << endl;

  // Test right rotation
  cout << "Testing " << prefix << " rotate right...";
  rotated_img = *img;
  rotate_right(&rotated_img);
  write_image(&rotated_img, DATA_FOLDER + "/" + prefix + "_right" + OUT_PPM_EXT);

  rotated_img_correct = load_image(DATA_FOLDER + "/" + prefix + "_right.correct.ppm");
  assert(Image_equal(&rotated_img, &rotated_img_correct));
  cout << "PASS" << endl;
}

void test_energy(const Matrix *energy_mat, string prefix){
  cout << "Testing " << prefix << " energy..." << flush;

  write_matrix(energy_mat, DATA_FOLDER + "/" +  prefix + "_energy" + OUT_TXT_EXT);

  auto energy_mat_correct = load_matrix(DATA_FOLDER + "/" + prefix + "_energy_correct.txt");

  assert(Matrix_equal(*energy_mat, energy_mat_correct));
  cout << "PASS" << endl;
}


void test_cost(const Matrix *cost_mat, string prefix){
  cout << "Testing " << prefix << " cost..." << flush;

  write_matrix(cost_mat, DATA_FOLDER + "/" +  prefix + "_cost" + OUT_TXT_EXT);

  auto cost_mat_correct = load_matrix(DATA_FOLDER + "/" + prefix + "_cost_correct.txt");

  assert(Matrix_equal(*cost_mat, cost_mat_correct));
  cout << "PASS" << endl;
}

void test_find_seam(const int seam[], int n, string prefix){
  cout << "Testing " << prefix << " find seam..." << flush;
  write_seam(seam, n, DATA_FOLDER + "/" + prefix + "_seam" + OUT_TXT_EXT);

  int seam_correct[MAX_MATRIX_HEIGHT];
  load_seam(seam_correct, DATA_FOLDER + "/" + prefix + "_seam_correct.txt");

  assert(array_equal(seam, seam_correct, n));
  cout << "PASS" << endl;
}

void test_remove_seam(const Image* img, const int seam[],
                             string prefix){
  cout << "Testing " << prefix << " remove seam..." << flush;

  Image* removed_img = new Image(*img);
  remove_vertical_seam(removed_img, seam);
  write_image(removed_img, DATA_FOLDER + "/" + prefix + "_removed" + OUT_PPM_EXT);

  auto removed_img_correct = load_image(DATA_FOLDER + "/" + prefix + "_removed.correct.ppm");

  assert(Image_equal(removed_img, &removed_img_correct));
  cout << "PASS" << endl;

  delete removed_img;
}

void test_seam_carve(const Image *img, string prefix,
                            int new_width, int new_height){
  cout << "Testing " << prefix << " seam carve ";
  cout << new_width << "x" << new_height << "..." << flush;
  Image* carved_img = new Image(*img);
  seam_carve(carved_img, new_width, new_height);
  write_image(carved_img,
    DATA_FOLDER + "/" + prefix + "_" + to_string(new_width) +
    "x" + to_string(new_height) + OUT_PPM_EXT);

  auto carved_img_correct = load_image(DATA_FOLDER + "/" + prefix + "_" + 
    to_string(new_width) + "x" + to_string(new_height) + ".correct.ppm");

  assert(Image_equal(carved_img, &carved_img_correct));
  cout << "PASS" << endl;

  delete carved_img;
}

static Matrix load_matrix(string filename){
  ifstream fin;
  fin.open(filename.c_str());

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  int width, height;
  fin >> width >> height;

  auto mat = Matrix(width, height);

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      fin >> mat.at(r, c);
    }
  }

  return mat;
}

static void write_matrix(const Matrix* mat, string filename){
  ofstream fout(filename.c_str());
  Matrix_print(*mat, fout);
}

static Image load_image(string filename){
  ifstream fin;
  fin.open(filename.c_str());

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  auto img = image_from_stream(fin);

  return img;
}


static void write_image(const Image* img, string filename){
  ofstream fout(filename.c_str());
  Image_print(*img, fout);
}

static void load_seam(int seam[], string filename){
  ifstream fin;
  fin.open(filename.c_str());

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  for(int i = 0, column; fin >> column; ++i){
    seam[i] = column;
  }
}

static void write_seam(const int seam[], int len, string filename){
  ofstream fout(filename.c_str());
  for(int i = 0; i < len; ++i){
    fout << seam[i] << endl;
  }
}
