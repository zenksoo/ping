#include "ping.h"

int main(int argc, char **argv) {
	int	count;
	int	opt;
	int i;

	display_error();
	
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
					count = atoi(argv[i + 1]);
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
