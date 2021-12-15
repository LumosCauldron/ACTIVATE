#include <stdio.h>

int main() {
    int kilos;
    scanf("%d", &kilos);
    printf("%.2lf pounds\n", 2.2 * kilos);

    return 0;
}
/*/ Net
	if (argc == 1)
		gatekeeper();
	else
		enterportal();
/*/

/*/ Filter
	if (argc < 4)
		THROW("NEEDS 3 ARGS");
	else
		filter_file(argv[1], argv[2], argv[3]);
/*/

/*/ Read Column
	if (argc > 2)
		PRINT(readcolumn(atoi(argv[2]), argv[1]));
	else
		THROW("NOT ENOUGH ARGS");
/*/
