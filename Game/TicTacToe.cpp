#include "stdafx.h"

#define EMPTY 0
#define L 3
#define N 9
#define SUB_SIZE 3
#define SUB_NUM 3
#define ROW_SIZE 3
#define COL_SIZE 3
#define TIE 1
#define PLAYER1 2
#define PLAYER2 3
#define INVALID -1
#define MIN_INDEX 1
#define NOBODY 0
#define ERROR -2
#define EXSIT -3
#define FREE 0
#define TAKEN 1
#define check 4
#define SEARCH 5


void print_welcome_message();
int player_turn(int prog_cnt);
int start_play(int board[N][N], int prog_cnt, int player, int idx, int pos);
void print_message_idx(char X_O);
void print_message_pos(char X_O, int idx);
void print_message_taken();
int sub_board(int board[N][N], int win[L][L], int idx, int pos, int player, int c);
int find_position(int board[N][N], int pos, int player, int i, int j);
int check_win(int board[N][N], int win[L][L], int player, int i, int j);
int insert_num(int num);
int check_range(int num);
void print_message_range();
void temp_sub_board(int board[N][N], int t_arry[L][L], int i, int j);
void temp_win_arry(int win[L][L], int t_arry[L][L]);
void sub_winner(int win[L][L], int max, int player, int i, int j);
int board_full(int board[N][N]);
int print_end_message(int game_status);
char player_to_char(int player);
void print_board(int board[N][N]);
void print_numbers();
void print_hor_border();
bool is_sub_board_full(int board[N][N], int sub_index);
int get_sub_row(int sub_index);
int get_sub_col(int sub_index);
void print_sub_board_win(int sub_index, int curr_player);


//12 rows of commands
void main()
{
	int board[N][N] = { 0 }, player = 1, idx = ERROR, pos = ERROR, cntrl;
	int win_X[L][L] = { { 1,1,1 },{ 1,1,1 },{ 1,1,1 } }, prog_cnt = 0;
	int win_O[L][L] = { { 1,1,1 },{ 1,1,1 },{ 1,1,1 } }, prev_idx;
	print_welcome_message();
	print_board(board);
	do
	{
		player = player_turn(++prog_cnt);
		prev_idx = idx;
		idx = start_play(board, prog_cnt, player, idx, pos);
		if (idx == EXSIT) break;
		print_board(board);
		if (player == PLAYER1)
			cntrl = sub_board(board, win_X, prev_idx, pos, player, SEARCH);
		else
			cntrl = sub_board(board, win_O, prev_idx, pos, player, SEARCH);

	} while ((!cntrl) && (!board_full(board)));
}

void print_welcome_message()
{
	printf("Welcome to Ultimate Tic-Tac-Toe!\n");
}

//2 rows of commands
/*Determine player turn X or O*/
int player_turn(int prog_cnt)
{
	if (prog_cnt % 2 != 0)
		return PLAYER1;
	else
		return PLAYER2;
}

//12 rows of commands
/*Manages messages and inputs*/
int start_play(int board[N][N], int prog_cnt, int player, int idx, int pos)
{
	char X_O = player_to_char(player);
	if ((prog_cnt == 1) || (is_sub_board_full(board, idx)))
	{
		do
		{
			print_message_idx(X_O);
			idx = insert_num(ERROR);
			if (idx == ERROR)
				return EXSIT;
		} while (is_sub_board_full(board, idx));
	}

	if (idx != ERROR)
	{
		print_message_pos(X_O, idx);
		pos = insert_num(ERROR);
	}

	if (pos != ERROR)
	{
		while (sub_board(board, FREE, idx, pos, player, check))
		{
			print_message_taken();
			pos = insert_num(ERROR);
			if (pos == ERROR)
				break;
		}
		if (pos != ERROR)
			return pos;
		else
			return EXSIT;
	}
	else
		return EXSIT;
}

//1 command row
void print_message_taken()
{
	printf("Position is taken, please choose another one:");
}

//1 command row
void print_message_idx(char X_O)
{
	printf("Player %c, please enter the index of the wanted sub-board:", X_O);
}

//1 command row
void print_message_pos(char X_O, int idx)
{
	printf("Player %c, please enter the wanted position in sub-board %d:", X_O, idx);
}

//4 rows of commands
/*Input values from the user*/
int insert_num(int num)
{
	scanf("%d", &num);
	while (check_range(num) == INVALID)
	{
		num = ERROR;
		scanf("%d", &num);
	}
	return num;
}

//5 rows of commands
/*Check input range and propriety*/
int check_range(int num)
{
	if (num == ERROR)
	{
		printf("Input error!\n");
		return ERROR;
	}
	while ((num < 1) || (num > 9))
	{
		print_message_range();
		return INVALID;
	}
	return 0;
}

//1 command row
void print_message_range()
{
	printf("Index out of range. Please enter a value between 1 and 9:");
}


//12 rows of commands
/*Find selected sub board by index and Send to function according to c*/
int sub_board(int board[N][N], int win[L][L], int idx, int pos, int player, int c)
{
	int j = 0, i = 0;
	if (idx == 1)
		i = j = 0;
	else if (idx == 2)
		i = 0, j = 3;
	else if (idx == 3)
		i = 0, j = 6;
	else if (idx == 4)
		i = 3, j = 0;
	else if (idx == 5)
		i = j = 3;
	else if (idx == 6)
		i = 3, j = 6;
	else if (idx == 7)
		i = 6, j = 0;
	else if (idx == 8)
		i = 6, j = 3;
	else if (idx == 9)
		i = j = 6;
	if (c == check)
		return find_position(board, pos, player, i, j);
	else
		return check_win(board, win, player, i, j);
}

//4 rows of commands
/*Check if position in sub board free and insert X/O to the board*/
int find_position(int board[N][N], int pos, int player, int i, int j)
{
	int cnt = 0;
	for (int k = i; k < i + ROW_SIZE; k++)
	{
		for (int l = j; l < j + COL_SIZE; l++)
		{
			cnt++;
			if (cnt == pos)
			{
				if (!board[k][l])
				{
					board[k][l] = player;
					return FREE;
				}
				else
					return TAKEN;
			}
		}
	}
}

//12 rows of commands
/*k=0 Check wins in sub board, k=1 Checks if there a game winner*/
int check_win(int board[N][N], int win[L][L], int player, int i, int j)
{
	int max = win[i / 3][j / 3], cnt[4] = { 0 }, t_arry[L][L] = { 0 };
	win[i / 3][j / 3] = 1;
	for (int k = 0; k < 2; k++)
	{
		if (k == 0)
			temp_sub_board(board, t_arry, i, j);
		else
			temp_win_arry(win, t_arry);

		for (int m = 0; m <ROW_SIZE; m++)
		{
			for (int n = 0; n <COL_SIZE; n++)
			{
				if (!(t_arry[m][n] % player)&&(t_arry[m][n]))
					cnt[0]++;

				if (!(t_arry[n][m] % player)&&(t_arry[n][m]))
					cnt[1]++;

				if (!m)
				{
					if (!(t_arry[n][n] % player)&&(t_arry[n][n]))
						cnt[2]++;
				}
				else if (m == 2)
				{
					if (!(t_arry[n][2-n] % player)&&(t_arry[n][2-n]))
						cnt[3]++;
				}
			}
			for (int l = 0; l < 4; l++)
			{
				if (cnt[l] == 3)
				{
					if (k == 0)
						sub_winner(win, max, player, i, j);
					else
						return print_end_message(player);
				}
			}
			cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
		}
	}
	return 0;
}

//7 rows of commands
/*Restores Index and prevents reprinting of old wins*/
void sub_winner(int win[L][L], int max, int player,int i,int j)
{
	int p;
	if (i == 0)
		p = 1;
	else if (i == 3)
		p = 3;
	else if (i == 6)
		p = 5;
	win[i / 3][j / 3] *= player;
	if (max < win[i / 3][j / 3])
	{
		max = win[i / 3][j / 3];
		print_sub_board_win(((i / 3)+(j / 3) + p), player);
	}
}

//5 rows of commands
/*Copy sub board from board to a temporary array*/
void temp_sub_board(int board[N][N], int t_arry[L][L], int i, int j)
{
	int a = 0, b = 0;
	for (int m = i; m <i + ROW_SIZE; m++)
	{
		for (int n = j; n <j + COL_SIZE; n++)
		{
			t_arry[a][b] = board[m][n];
			b++;
		}
		b = 0;
		a++;
	}
}

//1 command row
/*Copy wins array to temporary array*/
void temp_win_arry(int win[L][L], int t_arry[L][L])
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			t_arry[i][j] = win[i][j];
		}
	}
}

//2 rows of commands
/*Check if board full and if tie*/
int board_full(int board[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == 0)
				return FREE;
		}
	}
	return print_end_message(TIE);
}


int print_end_message(int game_status)
{
	if (game_status == TIE)
	{
		printf("Game over, it's a tie!\n");
	}
	else
		printf("Game over, %c is the winner!\n", player_to_char(game_status));
	return EXSIT;
}

char player_to_char(int player)
{
	switch (player)
	{
	case PLAYER1: return 'X';
	case PLAYER2: return 'O';
	case EMPTY: return ' ';
	}
	return '!';
}

// following 3 functions print the entire board
void print_board(int board[N][N])
{
	print_numbers();
	// print board line by line
	for (int i = 0; i<N; i++)
	{
		printf("%d", i - i % 3 + 1);
		for (int j = 0; j<SUB_NUM; j++)
		{
			for (int k = 0; k<SUB_SIZE; k++)
			{
				if (k>0)
					printf(" ");
				printf("%c ", player_to_char(board[i][j*SUB_SIZE + k]));
			}
			if (j<SUB_NUM)
				printf("|");
		}
		printf("%d\n", i - i % 3 + 3);
		if (i % 3 == 2 && i != 8)
			print_hor_border();
	}
	print_numbers();
}

void print_numbers()
{
	printf(" ");
	for (int i = 1; i <= SUB_NUM; i++)
	{
		for (int j = 0; j < SUB_SIZE; j++)
		{
			if (j > 0) printf("  ");
			printf("%d", i);
		}
		printf("  ");
	}
	printf("\n");
}

void print_hor_border()
{
	printf(" ");
	for (int i = 1; i <= SUB_NUM; i++)
	{
		for (int j = 0; j < 2 * 2 + 3; j++)
		{
			printf("-");
		}
		printf("  ");
	}
	printf("\n");
}

bool is_sub_board_full(int board[N][N], int sub_index)
{
	int sub_row = get_sub_row(sub_index);
	int sub_col = get_sub_col(sub_index);
	for (int i = sub_row; i<sub_row + SUB_SIZE; i++)
	{
		for (int j = sub_col; j<sub_col + SUB_SIZE; j++)
		{
			if (board[i][j] == EMPTY)
				return false;
		}
	}
	return true;
}

int get_sub_row(int sub_index)
{
	return ((sub_index - 1) / SUB_NUM) * SUB_SIZE;
}

int get_sub_col(int sub_index)
{
	return ((sub_index - 1) % SUB_NUM) * SUB_SIZE;
}

void print_sub_board_win(int sub_index, int curr_player)
{
	if (curr_player == NOBODY) return;
	printf("Player %c has won in sub-board %d!\n",
		player_to_char(curr_player), sub_index);
}


