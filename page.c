#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"



/* a function to generate HTML file that contains query results */
void print_page_sample(int *size)
{
	FILE* f;
	int i, j, k, m, n;
	extern char result[];

	if ((f = fopen(RESULT_PAGE, "w")) == NULL) {
		printf("cannot open file %s.", RESULT_PAGE);
		return;
	}

	/* printing HTML header */
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>result page</title>\n");
	fprintf(f, "<style type=\"text/css\">\n");
	fprintf(f, "table { background-image: url(\"nagoya.gif\"); }\n");
	fprintf(f, "td { padding: 0px; border: 1px; width: 16px; height: 14px; font-size: 10px; text-aligh: center; color: #ff00ff; } \n");
	fprintf(f, "</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");

	/* printing HTML table */
	fprintf(f, "<table>\n");
	for (i = 0; i < MAX_X_COORDINATE; i++) {

		/* printing table row */
		fprintf(f, "<tr>\n");
		for (j = 0; j < MAX_Y_COORDINATE; j++) {

			/* printing table column */
			fprintf(f, "<td>");

			/* printing item label corresponding to X=j, Y=i */

				/* PLEASE REPLACE HERE */
			for (n = 0; n < *size; n++) {
				if (j == item[result[n]].x && i == item[result[n]].y)
					fprintf(f, "%d", n);/* item label1 on X=1,Y=1 */
			}
			/* PLEASE REPLACE HERE */

			fprintf(f, "</td>\n");
		}
		fprintf(f, "</tr>\n");
	}
	fprintf(f, "</table>\n");

	/* printing HTML list */
	fprintf(f, "<ul>\n");

	/* printing list items */

		/* PLEASE REPLACE HERE */
	for (m = 0; m < *size; m++) {
		fprintf(f, "<li>%d : %s</li>\n", m, item[result[m]].name);
	}
	/* PLEASE REPLACE HERE */

	fprintf(f, "</ul>\n");


	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");

	fclose(f);
	return;
}


/* sample main function */
