
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>

char Words[][16] =
     {
	"XYLOPHONE", "HOSPITAL", "SANDWICH", "ESCALATOR",
	"SCULPTURE", "ELEPHANT", "YELLOWSTONE", "LANDSCAPE",
	"QUARANTINE", "ASTEROID", "MOUNTAIN", "CHAMELEON",
	"JELLYFISH", "PINEAPPLE", "FURNITURE", "SUNFLOWER",
	"UMBRELLA", "BACKPACK", "LIGHTNING", "NOVEMBER",
	"MAGNOLIA", "CAMPFIRE", "COMPUTER", "BUTTERFLY",
	"GOLDFISH", "TELESCOPE", "TELEPHONE", "VOLCANO",
	"BIRTHDAY", "OCTOPUS", "ALPHABET", "CHOCOLATE",
	"LABORATORY", "BREAKFAST", "KANGAROO", "ICECREAM",
	"RAINFOREST", "NOTEBOOK", "DINOSAUR", "WATERFALL"
    };
int WelcomeScr()
{
   int x,y,z;
   setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	    outtextxy(300,160,"HANGMAN GAME ");
   setcolor(WHITE);
 setlinestyle(SOLID_LINE, 5,6);
  line(0, 305, 650, 305);
   line(100, 290, 100, 150); //Main Line
   line(100, 150, 200, 150);//SUPORT LINE
   line(105, 200, 150, 155);//TOP LINE
   line(199, 158, 200, 180);//ROPE
   circle(200, 190, 10);//head
   line(200, 200, 200, 235);//BODY
   line(200, 200, 220, 225);//HAND R
   line(200, 200, 180, 225);//HAND L
   line(200, 230, 210, 260);//LEG R
   line(200, 230, 190, 260);//LEG L
 settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);;
   outtextxy(15,350,"Press S for single player or M for multiplayer!");
   char input = getch();

    if (input == 'S' || input == 's') {
        return 1; // Single player mode
    } else if (input == 'M' || input == 'm') {
        return 2; // Multiplayer mode
    } else {
        outtextxy(15, 370, "Invalid input! Please press 'S' or 'M'.");
        return 0; // Invalid input
    }
  outtextxy(110,60,"HANGMAN GAME");
   setlinestyle(DASHED_LINE, 2,3);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);

}

void Gamegfx()
{
   int x,y,z;
   int i,j,xs,ys,State[100],xpos[100],ypos[100];
   setcolor(WHITE);
   setlinestyle(SOLID_LINE, 5,10);
   line(0, 300, 650, 300);
   setcolor(DARKGRAY);
   setlinestyle(SOLID_LINE, 2,8);
   line(0, 305, 650, 305);

     setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
      outtextxy(200,400,"Starting Lives: 10");
      line(100, 290, 101, 150);
}

void Drawf(int i)
{      setcolor(WHITE);

 switch (i)

 {
     case 9 :
      outtextxy(200,400,"Remaining Lives: 9");
      line(100, 150, 200, 150);//Step 2
     break;
     case 8 :
      outtextxy(200,400,"Remaining Lives: 8");
      line(105, 200, 150, 155);//Step 3
     break;
     case 7 :
     outtextxy(200,400,"Remaining Lives: 7");
     line(199, 158, 200, 180);//Step 4
     break;
     case 6 :
     outtextxy(200,400,"Remaining Lives: 6");
     circle(200, 190, 10);//head
     break;
     case 5 :
     outtextxy(200,400,"Remaining Lives: 5");
     line(200, 200, 200, 235);//Step 6
     break;
     case 4 :
     outtextxy(200,400,"Remaining Lives: 4");
     line(200, 200, 220, 225);//Step 7
     break;
     case 3 :
    outtextxy(200,400,"Remaining Lives: 3");
     line(200, 200, 180, 225);//Step 8
     break;
     case 2 :
     outtextxy(200,400,"Remaining Lives: 2");
     line(200, 230, 210, 260);//Step 9
     break;
     case 1 :
     outtextxy(200,400,"Remaining Lives: 1");
     line(200, 230, 190, 260);//Step 10
     break;
 }
}

void Checkf(char X,int AG,int r,int NL,int Length,char *Hidden, int *Lives,int *Count, char* word)
{
    int i;
    int Found = 0;
    Length = strlen(word);
    for (i=0;i<Length;i++)
    {
	if (X==word[i] && Hidden[i]=='*' && NL == 0)
	{
	    Hidden[i] = X;
	    *Count = *Count + 1;
	    Found = 1;
	}
    }
    if (!Found && !AG && NL == 0)
    *Lives = *Lives - 1;
}

int RandomIndex()
{
    int X;
    X = rand() % 40;
    return X;
}

int Letterf(char X)
{
    if ((X >= 'a' && X <= 'z') || (X >= 'A' && X <= 'Z'))
    {
	return 0;
    }
    else
    {
	printf("Only letters are allowed!\n\n");
	return 1;
    }
}

char Capitalizef(char X)
{
    if (X>='a' && X<='z')
	X = X - 32;
    return X;
}
void CapitalizeWord(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = Capitalizef(word[i]);
    }
}
void PlayGame(char* wordToGuess) {
     GAME:
    cleardevice();
    Gamegfx();
    int r ;
    int i;
    int NL = 0; //Not Letters for Letterf
    char Again; //For playing again (Y/N)
    char Guessed[40];
    int j=0;
    int Lives = 10;
    int Count = 0;
    char Hidden[20];
    char Guessing;
    int Length = strlen(wordToGuess);
      for (i=0;i<Length;i++)
    {
	Hidden[i] = '*';
	printf("%c ",Hidden[i]);
    }
    while (Count!=Length)
    {
	int AG = 0; //Already Guessed
	printf("\nEnter a letter: ");
	scanf(" %c",&Guessing);
	Guessing = Capitalizef(Guessing);

	Guessed[j]=Guessing;
	if (j>0)
	{
	    for (i=0;i<j;i++)
	    {
		if (Guessing==Guessed[i])
		{
		    AG++;
		}
	    }
	}
	j++;
	system ("cls");
	NL = Letterf(Guessing);
		Checkf(Guessing,AG,r,NL,Length,Hidden,&Lives,&Count,wordToGuess);


	Drawf(Lives);
	if (Lives<=0)
	{
	    system ("cls");
	    setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
        outtextxy(158,350,"You ran out of lives!");
        setlinestyle(SOLID_LINE,1,1);
        line(198,188,196,186);
        line(204,188,202,186);
        line(196,188,198,186);
        line(202,188,204,186);
        setcolor(RED);
        line(198,192,202,192);
	    setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	    outtextxy(300,160,"THE WORD WAS: ");
	    setcolor(LIGHTRED);
	    outtextxy(300,205,Words[r]);
	    break;
	}
	for (i=0;i<Length;i++)
	{
	   printf("%c",Hidden[i]);
	}
	    printf("\nLetters Guessed:");
	for (i=0;i<j;i++)
	{
	    printf(" %c",Guessed[i]);
	}
	if (AG)
	{
	    printf("\nWarning: Letter already guessed!");
	}
    }
    //guessng loop
    if (Lives>0)
    {

        setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
        outtextxy(250,350,"You win!");
        setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	    outtextxy(300,160,"THE WORD WAS: ");
	    setcolor(LIGHTRED);
	    outtextxy(300,205,wordToGuess);
    }
    getchar();
    setcolor(WHITE);
	    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    outtextxy(180,400,"Try again? Y(es)/N(o)");
    printf("\n");
    scanf("%c",&Again);
    while (Again != 'y' || Again != 'Y' || Again != 'n' || Again !='N')
    {
        if (Again=='y' || Again=='Y')
        {
        system("cls");
        goto GAME;
        }
        else if (Again=='n' || Again == 'N')
        exit(EXIT_SUCCESS);
        else scanf("%c",&Again);
    }
}
int main(void)
{
    char wordToGuess[16];
    int gd = DETECT, gm,maxx,maxy;
    initgraph(&gd, &gm, "C:\\Program Files\\CodeBlocks\\MinGW\\lib");
    srand(time(NULL));
    int mode = WelcomeScr();
    while (mode == 0) {
        mode = WelcomeScr();
    }
if (mode == 1) {
        // Single-player mode
        for (int round = 0; round < 5; ++round) {
            int r = RandomIndex();
            strcpy(wordToGuess, Words[r]);
            PlayGame(wordToGuess);
        }
    } else if (mode == 2) {
        // Multiplayer mode
        char inputW[16];
        printf("Enter the word to guess: ");
        scanf("%15s", &inputW);
        system("cls");
        CapitalizeWord(inputW);
        strcpy(wordToGuess, inputW);
        PlayGame(inputW);
    }


    cleardevice();
    Gamegfx();
      closegraph();
    return 0;
}
