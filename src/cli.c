#include <cli.h>

void cli_opt__init(cli_opt_t *opt) {
  opt->input_instance = stdin;
  opt->output_tour = NULL;
  opt->output_csv = stdout;
  opt->log = stderr;
  for (int i = 0; i < BAL_COUNT; i++) {
    opt->state[i] = false;
  }
}

void cli(int argc, char const *argv[], cli_opt_t *opt) {

  cli_opt__init(opt);
  int i = 1;
  int methods = 0;
  while (i < argc) {

    // Balise -f
    if (strcmp("-f", argv[i]) == 0) {
      opt->state[BAL_F] = true;
      if (i + 1 < argc) {
        i++;
        opt->input_instance = read_or_fail(argv[i], 0);
      } else {
        fprintf(stderr, COLOR_R
                "[cli - error] file expected after flag (-f)\n" COLOR_N);
        exit(1);
      }
    }

    // Balise -t
    else if (strcmp("-t", argv[i]) == 0) {
      opt->state[BAL_T] = true;
      if (i + 1 < argc) {
        i++;
        opt->output_tour = read_or_fail(argv[i], 1);
      } else {
        fprintf(stderr, COLOR_R
                "[cli - error] file expected after flag (-t)\n" COLOR_N);
        exit(1);
      }
    }

    // Balise -v
    else if (strcmp("-v", argv[i]) == 0) {
      opt->state[BAL_V] = true;
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        i++;
        opt->log = read_or_fail(argv[i], 1);
      }
    }

    // Balise -o
    else if (strcmp("-o", argv[i]) == 0) {
      opt->state[BAL_O] = true;
      if (i + 1 < argc) {
        i++;
        opt->output_csv = read_or_fail(argv[i], 1);
      } else {
        fprintf(stderr, COLOR_R
                "[cli - error] file expected after flag (-o)\n" COLOR_N);
        exit(1);
      }
    }

    // Balise -ppv
    else if (strcmp("-ppv", argv[i]) == 0) {
      opt->state[BAL_PPV] = true;
      methods++;
    }

    // Balise -rw
    else if (strcmp("-rw", argv[i]) == 0) {
      opt->state[BAL_RW] = true;
      methods++;
    }

    // Balise -2opt
    else if (strcmp("-2opt", argv[i]) == 0) {
      opt->state[BAL_2OPT] = true;
      methods++;
    }

    // Balise -bf
    else if (strcmp("-bf", argv[i]) == 0) {
      opt->state[BAL_BF] = true;
      methods++;
    }

    // Balise -bfm
    else if (strcmp("-bfm", argv[i]) == 0) {
      opt->state[BAL_BFM] = true;
      methods++;
    }

    // Balise -ga
    else if (strcmp("-ga", argv[i]) == 0) {
      opt->state[BAL_GA] = true;
      methods++;
    }

    // Balise -nz
    else if (strcmp("-nz", argv[i]) == 0) {
      opt->state[BAL_ZERO] = true;
    }

    // Balise -h
    else if (strcmp("-h", argv[i]) == 0) {
      opt->state[BAL_H] = true;
    }

    // Balise -gpy
    else if (strcmp("-gpy", argv[i]) == 0) {
      opt->state[BAL_GPY] = true;
    }

    // Balise inconnue
    else {
      fprintf(stderr, COLOR_R "[cli - error] invalid option %s\n" COLOR_N,
              argv[i]);
      exit(1);
    }
    i++;
  }

  if (!opt->state[BAL_F]) {
    fprintf(stderr, COLOR_R "[cli - error] no input file provided\n" COLOR_N);
    exit(1);
  }

  if (methods == 0) {
    fprintf(stderr, COLOR_R "[cli - error] no method provided\n" COLOR_N);
    exit(1);
  }
}