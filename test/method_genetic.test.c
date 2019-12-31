#include <assert.h>
#include <methods/method_genetic.h>
#include <testing.h>

void method_genetic_run_test() {
  test_t test;
  init_test(&test, "testing genetic module");

  tour_t t1;
  tour_t t2;
  tour__init(&t1);
  tour__init(&t2);
  tour__set_dimension(&t1, 3);
  tour__set_dimension(&t2, 3);

  int a1[3] = {1, 2, 3};
  int a2[3] = {2, 1, 3};
  for (int i = 0; i < 3; i++) {
    t1.tour[i] = a1[i];
    t2.tour[i] = a2[i];
  }

  int edges1[2][2] = {{1, 2}, {2, 3}};
  int edges2[2][2] = {{1, 2}, {1, 3}};

  int **cedges1;
  int **cedges2;

  tour__get_edges(&t1, &cedges1);
  tour__get_edges(&t2, &cedges2);

  bool check1 = true;
  bool check2 = true;
  for (int i = 0; i < 2; i++) {
    check1 = check1 &&
             (edges1[i][0] == cedges1[i][0] && edges1[i][1] == cedges1[i][1]);
    check2 = check2 &&
             (edges2[i][0] == cedges2[i][0] && edges2[i][1] == cedges2[i][1]);
  }

  test_ensure(&test, "edges of tour [1, 2, 3] are {{1, 2}, {2, 3}}", check1);
  test_ensure(&test, "edges of tour [2, 1, 3] are {{2, 1}, {1, 3}}", check2);

  bool check3 = true;
  int **frags;
  int *sizes;

  int size = explode(&t1, &t2, &frags, &sizes);
  test_ensure(&test, "There are 2 shared fragments bt [2, 1, 3] and [1, 2, 3]",
              size == 2);

  test_ensure(&test, "Shared fragments 0 bt [2, 1, 3] and [1, 2, 3] has size 2",
              sizes[0] == 2);

  test_ensure(&test, "Shared fragments 1 bt [2, 1, 3] and [1, 2, 3] has size 1",
              sizes[1] == 1);

  test_ensure(&test,
              "shared fragments bt [2, 1, 3] and [1, 2, 3] are {1, 2}, {3}",
              check3);

  tour_t t3;
  tour_t t4;

  tour__init(&t3);
  tour__init(&t4);
  tour__set_dimension(&t3, 10);
  tour__set_dimension(&t4, 10);

  int a3[] = {5, 3, 9, 1, 2, 8, 10, 6, 7, 4};
  int a4[] = {1, 2, 5, 3, 9, 4, 8, 6, 10, 7};

  for (int i = 0; i < 10; i++) {
    t3.tour[i] = a3[i];
    t4.tour[i] = a4[i];
  }

  int **edgesA;
  int **edgesB;
  tour__get_edges(&t3, &edgesA);
  tour__get_edges(&t4, &edgesB);

  int cedgesA[9][2] = {{3, 5},  {3, 9},  {1, 9}, {1, 2}, {2, 8},
                       {8, 10}, {6, 10}, {6, 7}, {4, 7}};

  int cedgesB[9][2] = {{1, 2}, {2, 5}, {3, 5},  {3, 9}, {4, 9},
                       {4, 8}, {6, 8}, {6, 10}, {7, 10}};

  bool check = true;
  for (int i = 0; i < 9; i++) {
    check = check &&
            (cedgesA[i][0] == edgesA[i][0] && cedgesA[i][1] == edgesA[i][1]);
  }

  test_ensure(&test,
              "edges of [5, 3, 9, 1, 2, 8, 10, 6, 7, 4] are "
              "(3 5) (3 9) (1 9) (1 2) (2 8) (8 10) (6 10) (6 7) (4 7)",
              check);

  check = true;
  for (int i = 0; i < 9; i++) {
    check = check &&
            (cedgesB[i][0] == edgesB[i][0] && cedgesB[i][1] == edgesB[i][1]);
  }

  test_ensure(&test,
              "edges of [1, 2, 5, 3, 9, 4, 8, 6, 10, 7] are "
              "(1 2) (2 5) (3 5) (3 9) (4 9) (4 8) (6 8) (6 10) (7 10)",
              check);

  instance_t inst;
  tour_t t5;
  int *sizes2;
  int **frags2;
  int size2 = explode(&t3, &t4, &frags2, &sizes2);
  instance__init(&inst, false);
  instance__read_from_file(&inst, read_or_fail("./att10.tsp", 0));
  instance__compute_distances(&inst);
  int tour[10] = {5, 3, 9, 1, 2, 4, 10, 6, 7, 8};
  cross_dpx(&inst, &t3, &t4, &t5);

  check = true;
  for (int i = 1; i <= 10; i++) {
    check = check && (tour__has_node(&t5, i));
  }

  test_ensure(&test,
              "The result of cross_dpx on "
              "{5, 3, 9, 1, 2, 8, 10, 6, 7, 4} and "
              "{1, 2, 5, 3, 9,4, 8, 6, 10, 7} is consistent",
              check);

  check = true;
  for (int i = 0; i < 9; i++) {
    check = check && (t5.tour[i] == tour[i]);
  }

  test_ensure(&test,
              "The result of cross_dpx on "
              "{5, 3, 9, 1, 2, 8, 10, 6, 7, 4} and "
              "{1, 2, 5, 3, 9,4, 8, 6, 10, 7} is "
              "{5, 3, 9, 1, 2, 4, 10, 6, 7, 8}",
              check);

  end_test(&test);
}