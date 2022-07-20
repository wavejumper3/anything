#include "item.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define maxrooms 100
#define maxitems 32

struct room {
	char name[15];
	char desc[121];
	int west;
	int east;
	int north;
	int south;
	struct item items[maxitems];
};
#define numactions 3

const char actions[numactions][8] = {"eat","drink","buy"};
char buffer[60];


void eat()
{
	printf("You eat it!");
}
void drink()
{
	printf("You drink it!");
}
void buy()
{
	printf("You buy it!");
}

void (*actionfunctions[numactions])() = {&eat, &drink, &buy};

void look(struct room *allrooms, int *curnum)
{
	printf("%s",allrooms[*curnum].desc);
	if (allrooms[*curnum].items[0].ats[0] != 0)
	{
		printf("\nThere is: %s", allrooms[*curnum].items[0].name);
	}
	if(allrooms[*curnum].north){printf("\nNorth: %s", allrooms[allrooms[*curnum].north -1].name);}
	if(allrooms[*curnum].south){printf("\nSouth: %s", allrooms[allrooms[*curnum].south -1].name);}
	if(allrooms[*curnum].east){printf("\nEast: %s", allrooms[allrooms[*curnum].east - 1].name);}
	if(allrooms[*curnum].west){printf("\nWest: %s", allrooms[allrooms[*curnum].west - 1].name);}
}

void dosim(struct room *allrooms, int *curnum)
{

}



void doaction(int actionnum, struct room *allrooms, int *curnum)
{
	struct room current = allrooms[*curnum];
	switch (actionnum)
	{
	case 0:
		printf("I have no idea what you mean!");
		break;
	case 1:
		look(allrooms, curnum);
		break;
	case 2:
		if (current.north != 0)
		{
			*curnum = current.north - 1;
			printf("You go north.\n");
			current = allrooms[*curnum];
		}
		look(allrooms, curnum);
		break;
	case 3:
		if (current.south != 0)
		{
			*curnum = current.south - 1;
			printf("You go south.\n");
			current = allrooms[*curnum];
		}
		look(allrooms, curnum);
		break;
	case 4:
		if (current.east != 0)
		{
			*curnum = current.east - 1;
			printf("You go east.\n");
			current = allrooms[*curnum];
		}
		look(allrooms, curnum);
		break;
	case 5:
		if (current.west != 0)
		{
			*curnum = current.west - 1;
			printf("You go west.\n");
			current = allrooms[*curnum];
		}
		look(allrooms, curnum);
		break;
	default:
		actionnum -= 7;
		printf("You wanna use the %s with what verb?\n>", allrooms[*curnum].items[actionnum].name);
		fgets(buffer, 60, stdin);
		buffer[strcspn(buffer, "\n")] = 0;;
		printf("You attempt to %s the %s.", buffer, allrooms[*curnum].items[actionnum].name);
		printf("\nHowever, this sim is so bad that you cant do that yet.\nWell, this is embarrasing...\nLets forget about that.\nTry something else!");
	}
}

int stringtonum(char *input, struct room *allrooms, int *curnum)
{
	if (!memcmp(input, "quit\n", 5)||!memcmp(input, "q", 2)) {return -1;}
	if (!memcmp(input, "look", 4)||!memcmp(input, "l", 2)) {return 1;}
	if (!memcmp(input, "north\n", 6)||!memcmp(input, "n", 2)){return 2;}
	if (!memcmp(input, "south\n", 6)||!memcmp(input, "s", 2)){return 3;}
	if (!memcmp(input, "east\n", 5) ||!memcmp(input, "e", 2)){return 4;}
	if (!memcmp(input, "west\n", 5) ||!memcmp(input, "w", 2)){return 5;}
	if (!memcmp(input, "get ", 4)){return 6;}
	if (!memcmp(input, "use ", 4))
	{
		for (int i = 0; allrooms[*curnum].items[i].ats[0] != 0; ++i)
		{
			if (!memcmp(((char *)input + 4), allrooms[*curnum].items[i].name, strlen(allrooms[*curnum].items[i].name)))
			{
				return i + 7;
			}
		}
		printf("There isn't one I can see.\n");
		return 1;
	}
	return 0;
}

int main(void)
{
	struct room start[maxrooms];

	struct room coffeeshop = {.desc = "You are in a coffee shop.", .name = "coffee shop", .north =2};
	struct room sidewalk = {.desc = "You are on the sidewalk.", .name = "sidewalk", .south = 1};

	start[0] = coffeeshop;
	start[1] = sidewalk;

	for(int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			start[i].items[j].ats[0] = 0;
		}
	}
	start[0].items[1] = start[0].items[0];
	start[0].items[0] = cup;
	int i;
	int action = 1;
	int curroom = 0;
	do {
		doaction(action, start, &curroom);
		dosim(start, &curroom);
		printf("\n>");
		fgets(buffer, 60, stdin);
		action = stringtonum(buffer, start, &curroom);
	} while(action != -1);

	return 0;
}

