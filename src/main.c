#include "ping.h"

int main(int argc, char **argv) {
	int	count;
	int	opt;
	int i;

	getip(argv[1]);

	if (argc < 2) {
		fprintf(stderr, "ping: Usage: ping [OPTION] [DEST...]\n");
		return 1;
	}

	display_messge(2, "invalid argument\n", ERR_MSG);
	display_messge(1, "normal msg :)\n", NORMAL_MSG);
	display_messge(1, "warn msg :)\n", WARN_MSG);
	
	static struct option long_options[] = {
        {"count", no_argument, 0, 'c'},
        {"help",    no_argument, 0, 'h'},
        {0,         0,           0, 0}
    };

	i = 0;
	while (++i < argc)
	{
		if ((opt = getopt_long(argc, argv, "ch:", long_options, NULL)) != -1) {
			switch (opt) {
				case 'c':
					if (i + 1 < argc)
						count = atoi(argv[i + 1]);
					else {
						display_messge(2, "Missing Value for [-c] flag", ERR_MSG);
						return 1;
					}
					break;
				case 'h':
					printf("Usage: %s [-c] [-h]\n", argv[0]);
					return 0;
				default:
					continue;
			}
		}
		printf("%s\n", argv[i]);
	}
	printf("%d\n", count);
	return 0;
}
