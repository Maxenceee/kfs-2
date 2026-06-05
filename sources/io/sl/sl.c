/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:23:42 by mgama             #+#    #+#             */
/*   Updated: 2026/06/05 13:23:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "timer/delay.h"
#include "std/std.h"
#include "_sl.h"

#define OK  0
#define ERR 1

int CAR_COUNT = 0;
int ACCIDENT = 0;
int LOGO     = 0;
int FLY      = 0;
int C51      = 0;

static uint16_t back_buffer[VGA_HEIGHT * VGA_WIDTH];
int reset_smoke_trigger = 0;

int my_mvaddstr(int y, int x, char *str)
{
	if (y < 0 || y >= VGA_HEIGHT) return OK; 

	uint8_t attrib = (VGA_BACK_BLACK | VGA_FORE_WHITE);

	for (; *str != '\0'; ++str, ++x)
	{
		if (x < 0 || x >= VGA_WIDTH)
			continue;

		back_buffer[y * VGA_WIDTH + x] = (uint16_t)((attrib << 8) | *str);
	}

	return OK;
}

void parse_options(const char *str)
{
	while (*str != '\0')
	{
		switch (*str++)
		{
			case 'a': ACCIDENT  = 1; break;
			case 'f': FLY       = 1; break;
			case 'l': LOGO      = 1; break;
			case 'c': C51       = 1; break;
			case 'n': CAR_COUNT = katoi(str); break;
			default:                break;
		}
	}
}

void add_smoke(int y, int x, int move_smoke);
void add_man(int y, int x);
int add_sl(int x, int move_smoke);
int add_D51(int x, int move_smoke);
int add_C51(int x, int move_smoke);

void run_sl(const char *args)
{
	ACCIDENT = 0;
	LOGO     = 0;
	FLY      = 0;
	C51      = 0;
	CAR_COUNT = 1;
	reset_smoke_trigger = 1;

	if (args)
	{
		for (int i = 0; args[i] != '\0'; ++i)
		{
			if (args[i] == '-' && args[i + 1] != '\0')
			{
				parse_options(&args[i + 1]);
			}
		}
	}

	if (CAR_COUNT < 1) CAR_COUNT = 1;

	vga_clear_screen();
	disable_cursor();

	int max_length = D51LENGTH;
	int car_width = 30;

	if (LOGO == 1)
	{
		max_length = LOGOLENGTH;
		car_width = 21;
	}
	else if (C51 == 1)
	{
		max_length = C51LENGTH;
	}

	max_length += ((CAR_COUNT - 1) * car_width);

	uint16_t blank_char = (uint16_t)((' ' | (VGA_BACK_BLACK | VGA_FORE_WHITE) << 8));
	volatile uint16_t *vga_hardware = (uint16_t *)VGA_TEXT_BUFFER;

	for (int x = VGA_WIDTH - 1; x > -max_length; --x)
	{
		int move_smoke = (x % 4 == 0);

		for (int idx = 0; idx < VGA_HEIGHT * VGA_WIDTH; idx++)
		{
			back_buffer[idx] = blank_char;
		}

		if (LOGO == 1)      add_sl(x, move_smoke);
		else if (C51 == 1)  add_C51(x, move_smoke);
		else                add_D51(x, move_smoke);

		for (int idx = 0; idx < VGA_HEIGHT * VGA_WIDTH; idx++)
		{
			vga_hardware[idx] = back_buffer[idx];
		}

		kmsleep(40); 
	}

	vga_clear_screen();
	enable_cursor(14, 15);
}

int add_sl(int x, int move_smoke)
{
	static char *sl[LOGOPATTERNS][LOGOHEIGHT + 1] = {
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL11, LWHL12, DELLN},
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL21, LWHL22, DELLN},
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL31, LWHL32, DELLN},
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL41, LWHL42, DELLN},
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL51, LWHL52, DELLN},
		{LOGO1, LOGO2, LOGO3, LOGO4, LWHL61, LWHL62, DELLN}
	};

	static char *coal[LOGOHEIGHT + 1] = {LCOAL1, LCOAL2, LCOAL3, LCOAL4, LCOAL5, LCOAL6, DELLN};
	static char *car[LOGOHEIGHT + 1]  = {LCAR1, LCAR2, LCAR3, LCAR4, LCAR5, LCAR6, DELLN};

	int i, y, py1 = 0, py2 = 0;
	y = VGA_HEIGHT / 2 - 3;

	if (FLY == 1)
	{
		y = (x / 6) + VGA_HEIGHT - (VGA_WIDTH / 6) - LOGOHEIGHT;
		py1 = 2;  py2 = 4;
	}
	
	for (i = 0; i <= LOGOHEIGHT; ++i)
	{
		my_mvaddstr(y + i, x, sl[(LOGOLENGTH + x) / 3 % LOGOPATTERNS][i]);
		my_mvaddstr(y + i + py1, x + 21, coal[i]);

		for (int w = 0; w < CAR_COUNT - 1; ++w)
		{
			int offset_x = 42 + (w * 21);
			int fly_y_offset = py2 + (w * 2);
			
			my_mvaddstr(y + i + (FLY ? fly_y_offset : 0), x + offset_x, car[i]);
		}
	}
	
	if (ACCIDENT == 1)
	{
		add_man(y + 1, x + 14);
		for (int w = 0; w < CAR_COUNT - 1; ++w)
		{
			int offset_x = 42 + (w * 21);
			int fly_y_offset = py2 + (w * 2);
			int current_y = y + 1 + (FLY ? fly_y_offset : 0);
			add_man(current_y, x + offset_x + 3);
			add_man(current_y, x + offset_x + 11);
		}
	}

	add_smoke(y - 1, x + LOGOFUNNEL, move_smoke);

	return OK;
}

int add_D51(int x, int move_smoke)
{
	static char *d51[D51PATTERNS][D51HEIGHT + 1] = {
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL11, D51WHL12, D51WHL13, D51DEL},
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL21, D51WHL22, D51WHL23, D51DEL},
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL31, D51WHL32, D51WHL33, D51DEL},
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL41, D51WHL42, D51WHL43, D51DEL},
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL51, D51WHL52, D51WHL53, D51DEL},
		{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7, D51WHL61, D51WHL62, D51WHL63, D51DEL}
	};
	
	static char *coal[D51HEIGHT + 1] = {COAL01, COAL02, COAL03, COAL04, COAL05, COAL06, COAL07, COAL08, COAL09, COAL10, COALDEL};

	int y, i, dy = 0;
	y = VGA_HEIGHT / 2 - 5;

	if (FLY == 1)
	{
		y = (x / 7) + VGA_HEIGHT - (VGA_WIDTH / 7) - D51HEIGHT;
		dy = 1;
	}
	for (i = 0; i <= D51HEIGHT; ++i)
	{
		my_mvaddstr(y + i, x, d51[(D51LENGTH + x) % D51PATTERNS][i]);
		my_mvaddstr(y + i + dy, x + 53, coal[i]);

		for (int w = 0; w < CAR_COUNT - 1; ++w)
		{
			int offset_x = 53 + 30 + (w * 30); 
			my_mvaddstr(y + i + dy + (FLY ? w : 0), x + offset_x, coal[i]);
		}
	}
	if (ACCIDENT == 1)
	{
		add_man(y + 2, x + 43);
		add_man(y + 2, x + 47);
	}
	add_smoke(y - 1, x + D51FUNNEL, move_smoke);

	return OK;
}

int add_C51(int x, int move_smoke)
{
	static char *c51[C51PATTERNS][C51HEIGHT + 1] = {
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH11, C51WH12, C51WH13, C51WH14, C51DEL},
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH21, C51WH22, C51WH23, C51WH24, C51DEL},
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH31, C51WH32, C51WH33, C51WH34, C51DEL},
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH41, C51WH42, C51WH43, C51WH44, C51DEL},
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH51, C51WH52, C51WH53, C51WH54, C51DEL},
		{C51STR1, C51STR2, C51STR3, C51STR4, C51STR5, C51STR6, C51STR7, C51WH61, C51WH62, C51WH63, C51WH64, C51DEL}
	};
	
	static char *coal[C51HEIGHT + 1] = {COALDEL, COAL01, COAL02, COAL03, COAL04, COAL05, COAL06, COAL07, COAL08, COAL09, COAL10, COALDEL};

	int y, i, dy = 0;
	y = VGA_HEIGHT / 2 - 5;

	if (FLY == 1)
	{
		y = (x / 7) + VGA_HEIGHT - (VGA_WIDTH / 7) - C51HEIGHT;
		dy = 1;
	}
	for (i = 0; i <= C51HEIGHT; ++i)
	{
		my_mvaddstr(y + i, x, c51[(C51LENGTH + x) % C51PATTERNS][i]);
		my_mvaddstr(y + i + dy, x + 55, coal[i]);

		for (int w = 0; w < CAR_COUNT - 1; ++w)
		{
			int offset_x = 55 + 30 + (w * 30);
			my_mvaddstr(y + i + dy + (FLY ? w : 0), x + offset_x, coal[i]);
		}
	}
	if (ACCIDENT == 1)
	{
		add_man(y + 3, x + 45);
		add_man(y + 3, x + 49);
	}
	add_smoke(y - 1, x + C51FUNNEL, move_smoke);

	return OK;
}

void add_man(int y, int x)
{
	static char *man[2][2] = {{"", "(O)"}, {"Help!", "\\O/"}};
	for (int i = 0; i < 2; ++i)
	{
		my_mvaddstr(y + i, x, man[(D51LENGTH + x) / 12 % 2][i]);
	}
}

void add_smoke(int y, int x, int move_smoke)
#define SMOKEPTNS        16
{
	static struct smokes {
		int y, x;
		int ptrn, kind;
	} S[1000];
	static int sum = 0;

	if (reset_smoke_trigger == 1)
	{
		sum = 0;
		reset_smoke_trigger = 0;
	}

	static char *Smoke[2][SMOKEPTNS] = {
		{"(   )", "(    )", "(    )", "(   )", "(  )", "(  )" , "( )"   , "( )"   , "()"   , "()"  , "O"    , "O"     , "O"     , "O"    , "O"   , " "},
		{"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)", "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  , "@"    , "@"     , "@"     , "@"    , "@"   , " "}
	};
			
	static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0 };
	static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2, 2,  2, 2, 3, 3, 3 };

	if (move_smoke && sum < 1000)
	{
		for (int i = 0; i < sum; ++i)
		{
			S[i].y    -= dy[S[i].ptrn];
			S[i].x    += dx[S[i].ptrn];
			S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
		}
		S[sum].y = y;    
		S[sum].x = x;
		S[sum].ptrn = 0; 
		S[sum].kind = sum % 2;
		sum++;
	}

	for (int i = 0; i < sum; ++i)
	{
		my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
	}
}