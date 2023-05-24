#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Membership.h"

using namespace std;


void doTask();
void program_exit();


int main()
{
	FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
  FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");

	doTask();

	return 0;

}

void program_exit()
{
	fprintf(out_fp, "6.1. 종료\n");
}

void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;
	while (!is_program_exit)
	{

		fscanf(in_fp, "%d %d", &menu_level_1, &menu_level_2);

		switch (menu_level_1)
		{
		case 1:
		{
			switch (menu_level_2)
			{
			case 1:
			{
				Join jo_in;
				jo_in.join();
				break;
			}
			}
			case 2:
			{
				Withdraw withdraw;
				withdraw.withdraw();
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2:
		{
			switch (menu_level_2)
			{
			case 1:
			{
				LogIn login;
				login.login();
				break;
			}
			case 2:
			{
				LogOut logout;
				logout.logout();
				break;
			}
			default:
				break;
			}
			break;
		}
    current_state.set_current_state(menu_level_1, menu_level_2);
		fprintf(out_fp, "\n");
    }
    return;
  }

