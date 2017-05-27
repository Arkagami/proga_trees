#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h> 
#include <locale.h>


int main()
{
	int neNado = 0;
	int def = 0;
	-7878;nnm
	//lnnmnu 98y87-098
	09uy7h78j90u98y7g-089u98y89;
	"\\\"8978"
	char inFile[100];
	printf("Input file name:");
	scanf("%s", &inFile);

	int i = 0, slkol = 0; //slkol - count of sleshes, which going podryad
	char cArray[10000], c = 'n', lc = 'n', s[10000], cc = 'n', ccc = 'n';
	int len = strlen(cArray);
	int kav1 = 0, kav2 = 0; // Kavichki. 1 - '_', 2 - "_"; 

	FILE *fin = fopen(inFile, "r");

	for (i = 0; i<10000; i++) { s[i] = cArray[i] = '\0'; }

	while (!feof(fin)) {
	xyz:
		c = fgetc(fin);
		if (feof(fin)) { break; }
	eto:
		//Kavichki tipa "_" 
		if (c == '\"') {
			i = 0;
			slkol = 0;
			lc = 'n';
			c = '#';
			while ((c != '\"') || (slkol % 2 != 0)) {
			repa:lc = c;
				c = fgetc(fin);
				if (feof(fin)) { goto tuda; }
				if (((c == '\n') && (lc == '\\') && (slkol % 2 == 1))) { slkol = 0; goto repa; }
				else { if (c == '\n') { goto xyz; } }
				if (c == '\\') {
					if (lc == '\"') { slkol = 1; }
					else { slkol++; }
				}
				else {
					if (c == '\"') {
						if (lc == '\"') {
							if (slkol % 2 == 1) {
								goto xyz;
							}
							else { slkol = 0; }
						}
					}
					else { slkol = 0; }
				}
			}
			goto xyz;
		}
		else {
		uidi:;
			//Kavichki tipa '_' 
			if (c == '\'') {
				i = 0;
				slkol = 0;
				lc = 'n';
				c = '#';
				while ((c != '\'') || (slkol % 2 != 0)) {
				repet:lc = c;
					c = fgetc(fin);
					if (feof(fin)) { goto tuda; }
					if (c == '\n') { goto xyz; }
					if (c == '\\') {
						if (lc == '\'') { slkol = 1; }
						else { slkol++; }
					}
					else {
						if (c == '\'') {
							if (lc == '\'') {
								if (slkol % 2 == 1) {
									goto xyz;
								}
								else { slkol = 0; }
							}
						}
						else { slkol = 0; }
					}
				}
				goto xyz;
			}
			else {
				//. 

				//Comments
				if (c == '/') {
					c = fgetc(fin); if (feof(fin)) { goto tuda; }
					if (c == '/') {
						while (1) {
							lc = c;
							c = fgetc(fin);
							if (feof(fin)) { goto tuda; }
							if (c == '\n') {
								if (lc == '\\') {
									continue;
								}
								else { break; }
							}
						}
						goto xyz;
					}
					else {
						if (c == '*') {
							cc = 'i'; ccc = 'i'; while ((cc != '*') || (ccc != '/')) { cc = ccc; ccc = fgetc(fin); if (feof(fin)) { goto tuda; } } goto xyz;
						}
						else {
							goto eto;
						}
					}
					goto xyz;
				}
				else {
//-------------------------------------------------------------------------------------------------
//Main program code for podschet and poisk chisel
					int minus = 0;
					if(c=='-') {
						c = fgetc(fin);
						if (feof(fin)) goto tuda; 
						if ((c < 48) || (c > 57)) {
							goto eto;
						}
						else minus = 1;
					}
					long long number = 0;
					while ((c > 47) && (c < 58)) {
						number = number * 10 + c - 48;
						c = fgetc(fin);
						if (feof(fin)) goto tuda;
						}
					printf("%lld\n", number);
					goto eto;
//-------------------------------------------------------------------------------------------------
//End of main program code
				}
			}
		}
		//----------------------Comments 

	}
tuda:
	fclose(fin);

	return 0;
}