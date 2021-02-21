// Nadav Avraham <313531964>
//2`nd project- <SNAKE>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_ROWS 25
#define MAX_COLS 75
#define W 119
#define D 100
#define S 115
#define A 97


typedef struct link { //this struct represent the snake itself. contains the location on the screen; (loc_x loc_y)
	int loc_x;
	int loc_y;
	struct link *next;   //Address of the next node
}Link;


// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen, 
// but rather a command to the terminal (or most likely terminal emulator).
// Turn escape codes ON.
void init(void);
// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the position.
//     y: the column of the position.
void gotoxy(int x, int y);
// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs);
void printBorder();

Link* newLink(); // function to create new list---> a new node for the snake to make gim grow in insert function
void printLinkedList(Link * head); //print the list to the screen
void deletesfirst(Link** head); //deleting the first node- which basiclly is the tail of the snake
void clrLast(Link* head); //delete from the scren the sign @ represent the tail (last node) from sreen
void insert(Link * p, char dir); //inserting new node the list
bool stillAlive(Link* p); //checks if the game ended - if there is a collision in the border or with the snake itself


int main()
{
	int counter = 0; //counting steps of the snake
	float speed = 1; //represent the time of sleeping-> control pace of the snake changes every 5 steps
	bool game_on = true; //updating from stillAlive function
	char dir = D; // pointing the direcction of the snake- works with insert for changing the location of the next node of list
	init();
	printBorder();
	Link* head;
	head = newLink();
	while (game_on) {
		if (_kbhit()) {  // if keboard hitted (assumin right hit (A,D,S,W)) changing dir content and from now on the new nodes will be inserted as needed
			dir = _getch();
		}
		printLinkedList(head);
		insert(head, dir);
		counter++;
		sleep(speed);

		if (counter < 5) { 
			clrLast(head);
			deletesfirst(&head);
		}
		else { //5 steps has been made, no need for deleting the last node or clear the last @ from screen
			counter = 0;
			if (speed > 0.01) //speed is changing every five steps
				speed = speed - 0.03;
		}
		game_on = stillAlive(head); //checks if game is stil on works with stillALive function
	}

	//if game on was false, means game over, while is ended and we go to the block of code, clear screen and print border, and print GAME OVER in middle of screen
	init(); 
	printBorder();
	gotoxy(MAX_ROWS / 2, MAX_COLS / 2);
	printf("GAME OVER");
	gotoxy(MAX_ROWS+1, MAX_COLS / 2);


}



Link* newLink() // function to create new list---> a new node for the snake to make gim grow in insert function
{
	Link *p = (Link *)malloc(sizeof(Link));
	p->loc_x = MAX_ROWS / 2;
	p->loc_y = MAX_COLS / 2;
	p->next = NULL;
	return p;

}

void printLinkedList(Link * head) { //print the list to the screen
	while (head != NULL) {
		gotoxy(head->loc_x, head->loc_y);
		printf("@");
		head = head->next;
	}
}

void insert(Link * p, char dir) { // assume p is not NULL because defult situation is at least one node of the snake. and inserting new node the list
	while (p->next != NULL) {
		p= p->next;
	}
	Link *q = newLink();
	switch (dir) // the location of the new node will be desermind by the direction comming from the dir vairable from main (changing with kbhit)
	{
		case D:
			q->loc_x = p->loc_x;
			q->loc_y = p->loc_y + 1;
			break;
		case W:
			q->loc_x = p->loc_x-1;
			q->loc_y = p->loc_y;
			break;
		case A:
			q->loc_x = p->loc_x;
			q->loc_y = p->loc_y -1;
			break;
		case S:
			q->loc_x = p->loc_x+1;
			q->loc_y = p->loc_y;
		break;
	}
	
	p->next = q;
}

void clrLast(Link* head) {  //delete from the scren the sign @ represent the tail (last node) from sreen
	gotoxy(head->loc_x, head->loc_y);
	printf(" ");
}

void deletesfirst(Link** head) //deleting the first node- which basiclly is the tail of the snake
{

	Link* temp;
	temp =(* head)->next;
	
	free(*head);
	*head = temp;
}

bool stillAlive(Link* p) {  //checks if the game ended - if there is a collision in the border or with the snake itself
	Link* q = p;
	while (q->next != NULL) {
		q = q->next;
	}
	while (p->next != NULL) { //checking cillision with the snake itself
		if (q->loc_x == p->loc_x && q->loc_y == p->loc_y)
			return false;
		else
			p = p->next;
	}

	if ((q->loc_y == 75) || (q->loc_y == 1) || (q->loc_x == 1) || (q->loc_x == 25)) // checks collision with one of the borders.
		return false;
	else return true;

}

void printBorder() //print the boarder of the game requested 25X75
{
	int i;
	for (i = 1; i < 25; i++)
	{
		gotoxy(i, 1);
		printf("#");
		gotoxy(i, 75);
		printf("#");
	}
	for (i = 1; i < 76; i++)
	{
		gotoxy(1, i);
		printf("#");
		gotoxy(25, i);
		printf("#");
	}
}


// Turn escape codes ON.
void init(void) {
	system("cls");
}
// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the position.
//     y: the column of the posiiton.
void gotoxy(int x, int y) {
	printf("\x1b[%d;%df", x, y);
}
// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs) {
	clock_t clocks_start = clock();

	while (clock() - clocks_start < secs*CLOCKS_PER_SEC)
		;
}
