#include <stdio.h>
#include <string.h>

#define ingestable 1
#define warm 2
#define cold 3
#define holdsstuff 4
#define holdsliquid 5

struct item
{
	char name[15];
	int material;
	int volume;
	int ats[20];
	struct item *contents[8];
};
void printitem(struct item thing)
{
	puts("----");
	puts(thing.name);
	int i = 0;
	while(thing.contents[i] != 0)
	{
		printf("contains: %s\n", thing.contents[i]->name);
		++i;
		if(i <= 4){break;}
	}
	puts("----");
}
struct item coffee = {.name = "coffee", .ats[0] = ingestable, .ats[1] = warm};
struct item cup = {.name = "cup", .ats[0] = holdsliquid, .ats[2] = holdsstuff, .contents[0] = &coffee};

