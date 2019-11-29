#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
struct Block{

    int board[3][3];
    int cost; //h
    int level;//g
    int valid;
    int pos_of_space[2];
    struct Block* next;
};

typedef struct Block block;

void print_board(int board[3][3]);
int generate_permutations(block *head);
void copy_boards(int dest[3][3], int src[3][3]);
block* hscores(int perm, block *top_node, block *head, int goal[3][3]);
int final_state(int b[3][3], int goal[3][3]);
block* new_node();
int get_hscore(int board[3][3],int goal[3][3]);

int main(){

    block *top_node = new_node();
    //int goal_state[3][3];

    printf("Welcome to 8-Puzzle Game\n");
    printf("Enter the initial state of the 8-puzzle game :-\n");
    printf("Put z to represent empty box\n");
    printf("Enter in single line :- Example : 2 4 3 1 7 5 -1 6 8\n");
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&top_node->board[i][j]);
            if(top_node->board[i][j]==-1)
            {
            	top_node->pos_of_space[0]=i;
            	top_node->pos_of_space[1]=j;
            }
        }
    }
	//print_board(top_node->board);
    int goal_state[3][3] = {1,2,3,4,5,6,7,8,-1};
    //print_board(goal_state);

    top_node->cost = get_hscore(top_node->board,goal_state);
    top_node->level = 0;
	block *head = top_node;
	block *b = top_node;
	
    while(!final_state(head->board, goal_state)){
        
        //check if node is goal state , if yes , then printout the sequence to reach there.
        //if not then expand the block and then store all possible states 
        //pick the least f score grid and again go to 1st comment
        //done
        int perms = generate_permutations(head);
        block* least_board=hscores(perms, top_node, head, goal_state);
        //b=least_cost(head);
        head = least_board;
        print_board(least_board->board);
        printf("\n");
        sleep(2);
        
    }
    print_board(head->board);
}

int get_hscore(int board[3][3],int goal[3][3]){

    //returns the h-score : Here the hueristic taken is number of misplaced tiles

    int misplaced_tiles = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] != goal[i][j])
                misplaced_tiles++;    
        }
    }
    return misplaced_tiles;
}
int final_state(int b[3][3], int goal[3][3])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(b[i][j]!=goal[i][j])
				return 0;
		}
	}
	return 1;
}
block* hscores(int perm, block *top_node, block *head, int goal[3][3])
{
	block *temp = head;
	block *least_cost = NULL;
	int min = 1000000000;
	int t=0;
	while(temp!=NULL)
	{
		t=get_hscore(temp->board, goal) + get_hscore(temp->board, top_node->board);
		if(t<min)
		{
			min=t;
			least_cost = temp;
		}
		temp = temp->next;
	}
	return least_cost;
}
void copy_boards(int dest[3][3], int src[3][3])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			dest[i][j] = src[i][j];
		}
	}
}

block* new_node(){
    block* p = (block*)malloc(sizeof(block));

    p->cost = 0;
    p->valid = 1;
    p->next = NULL;
    return p;
}

void print_board(int board[3][3])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
}

int generate_permutations(block *head)
{
	block *t_head = head;
	block *temp;
	int space_i = head->pos_of_space[0];
	int space_j = head->pos_of_space[1];
	int no_of_perms=0;
	int gen=0;
	if((space_i==0&&space_j==0) || (space_i==0&&space_j==2) || (space_i==2&&space_j==2) || (space_i==2&&space_j==0))
	{
		no_of_perms=2;
		temp = new_node();
		//copy_boards(temp->board, t_head->board);
		copy_boards(temp->board, head->board);
		t_head->next=temp;
		t_head = temp;
		if(space_i==0)
		{
			//down
			temp->board[space_i][space_j] = temp->board[space_i+1][space_j];
			temp->board[space_i+1][space_j] = -1;
			temp->pos_of_space[0] = space_i+1;
			temp->pos_of_space[1] = space_j;
			gen++;
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			if(space_j==0)
			{
				//right
				temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
				temp->board[space_i][space_j+1] = -1;
				temp->pos_of_space[0] = space_i;
				temp->pos_of_space[1] = space_j+1;
				gen++;
			}
			else
			{
				//left
				temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
				temp->board[space_i][space_j-1] = -1;
				temp->pos_of_space[0] = space_i;
				temp->pos_of_space[1] = space_j-1;
				gen++;
			}
		}
		else //if(space_i==2)
		{
			//up
			temp->board[space_i][space_j] = temp->board[space_i-1][space_j];
			temp->board[space_i-1][space_j] = -1;
			temp->pos_of_space[0] = space_i-1;
			temp->pos_of_space[1] = space_j;
			gen++;
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			if(space_j==0)
			{
				//right
				temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
				temp->board[space_i][space_j+1] = -1;
				temp->pos_of_space[0] = space_i;
				temp->pos_of_space[1] = space_j+1;
				gen++;
			}
			else
			{
				//left
				temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
				temp->board[space_i][space_j-1] = -1;
				temp->pos_of_space[0] = space_i;
				temp->pos_of_space[1] = space_j-1;
				gen++;
			}
		}
	}
	else if(space_i==0 || space_i==2 || space_j==0 || space_j==2)
	{
		no_of_perms=3;
		int gen = 0;
		temp = new_node();
		copy_boards(temp->board, head->board);
		if(space_i==0)
		{
			//down
			temp->board[space_i][space_j] = temp->board[space_i+1][space_j];
			temp->board[space_i+1][space_j] = -1;
			temp->pos_of_space[0] = space_i+1;
			temp->pos_of_space[1] = space_j;
			gen++;
			//right
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
			temp->board[space_i][space_j+1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j+1;
			gen++;
			//left
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
			temp->board[space_i][space_j-1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j-1;
			gen++;
		}
		else if(space_i==2)
		{
			//up
			temp->board[space_i][space_j] = temp->board[space_i-1][space_j];
			temp->board[space_i-1][space_j] = -1;
			temp->pos_of_space[0] = space_i-1;
			temp->pos_of_space[1] = space_j;
			gen++;
			//right
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
			temp->board[space_i][space_j+1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j+1;
			gen++;
			//left
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
			temp->board[space_i][space_j-1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j-1;
			gen++;
		}
		else if(space_j==0)
		{
			//right
			temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
			temp->board[space_i][space_j+1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j+1;
			gen++;
			//down
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i+1][space_j];
			temp->board[space_i+1][space_j] = -1;
			temp->pos_of_space[0] = space_i+1;
			temp->pos_of_space[1] = space_j;
			gen++;
			//up
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i-1][space_j];
			temp->board[space_i-1][space_j] = -1;
			temp->pos_of_space[0] = space_i-1;
			temp->pos_of_space[1] = space_j;
			gen++;
		}
		else if(space_j==2)
		{
			//left
			temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
			temp->board[space_i][space_j-1] = -1;
			temp->pos_of_space[0] = space_i;
			temp->pos_of_space[1] = space_j-1;
			gen++;
			//down
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i+1][space_j];
			temp->board[space_i+1][space_j] = -1;
			temp->pos_of_space[0] = space_i+1;
			temp->pos_of_space[1] = space_j;
			gen++;
			//up
			temp = new_node();
			copy_boards(temp->board, head->board);
			t_head->next=temp;
			t_head = temp;
			temp->board[space_i][space_j] = temp->board[space_i-1][space_j];
			temp->board[space_i-1][space_j] = -1;
			temp->pos_of_space[0] = space_i-1;
			temp->pos_of_space[1] = space_j;
			gen++;
		}
	}
	else
	{
		//right
		temp = new_node();
		copy_boards(temp->board, head->board);
		t_head->next = temp;
		t_head = temp;
		temp->board[space_i][space_j] = temp->board[space_i][space_j+1];
		temp->board[space_i][space_j+1] = -1;
		temp->pos_of_space[0] = space_i;
		temp->pos_of_space[1] = space_j+1;
		gen++;
		//left
		temp = new_node();
		copy_boards(temp->board, head->board);
		t_head->next=temp;
		t_head = temp;
		temp->board[space_i][space_j] = temp->board[space_i][space_j-1];
		temp->board[space_i][space_j-1] = -1;
		temp->pos_of_space[0] = space_i;
		temp->pos_of_space[1] = space_j-1;
		gen++;
		//down
		temp = new_node();
		copy_boards(temp->board, head->board);
		t_head->next=temp;
		t_head = temp;
		temp->board[space_i][space_j] = temp->board[space_i+1][space_j];
		temp->board[space_i+1][space_j] = -1;
		temp->pos_of_space[0] = space_i+1;
		temp->pos_of_space[1] = space_j;
		gen++;
		//up
		temp = new_node();
		copy_boards(temp->board, head->board);
		t_head->next=temp;
		t_head = temp;
		temp->board[space_i][space_j] = temp->board[space_i-1][space_j];
		temp->board[space_i-1][space_j] = -1;
		temp->pos_of_space[0] = space_i-1;
		temp->pos_of_space[1] = space_j;
		gen++;
	}
	return gen;
}



/*permutations
	if space is on any of the four corners, only 2 perms possible
	else if space is on the first column, last column, first row or last row, 3 perms possible
	else 4 perms possible
*/
