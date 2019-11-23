#include <testing.h>
#include <tsplib/tsplib.h>

void tsplib_run_test() {

  instance_t test_instance;

  test_t test1;
  init_test(&test1, "testing tsplib");

  read_tsp_file("./test.tsp", &test_instance);
  int tab[3][4] = {{0, 0, 0, 0}, {0, 1, 0, 0}, {2, 0, 0, 0}};
  bool check1 = strcmp(test_instance.name, "arthur") == 0;
  bool check2 = test_instance.dimension == 3;
  bool check3 = test_array_equals(test_instance.tabCoord[0], tab[0], 4);
  bool check4 = test_array_equals(test_instance.tabCoord[1], tab[1], 4);
  bool check5 = test_array_equals(test_instance.tabCoord[2], tab[2], 4);

  test_ensure(&test1, "TSP files are read correctly",
              check1 && check2 && check3 && check4 && check5);

  test_ensure(
      &test1, "euclidian distance btw node 0 and 1 is 1.0",
      test_double_equals(1.0, instance__dist_euclidian(&test_instance, 0, 1)));

  test_ensure(
      &test1, "euclidian distance btw node 0 and 2 is 2.0",
      test_double_equals(2.0, instance__dist_euclidian(&test_instance, 0, 2)));

  test_ensure(&test1, "euclidian distance btw node 1 and 2 is 2.236",
              test_double_equals(
                  2.236, instance__dist_euclidian(&test_instance, 1, 2)));

  end_test(&test1);
}