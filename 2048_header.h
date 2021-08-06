#define OPERATION 1 //add sub assign value
#define DIRECTION 2 //up down
#define OTHERS 3 // is in VAR to
#define IDENTIFIER 4
#define NUMBER 5
#define FULLSTOP 6
#define COMMA 7
#define OUT_OF_BOUNDS 8
#define SUCCESS 0
#define FAILURE 10

#include<bits/stdc++.h>
#include<string>
#include<time.h>
using namespace std;
bool insert_random_tile();
int print_output(int error_code);
int assign_value(int value,int x,int y);
void Do_move(string* op, string* direction); 
int set_name(string* name,int x,int y);
int get_value(int x,int y);
bool is_possible_to_insert();

