#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "readline/readline.h"
#include "readline/history.h"
#include <iterator>
#include <limits.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <curses.h>
#include <stdio.h>
#include <ctype.h>

#define WIDTH 30
#define HEIGHT 10 

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

template <typename Container>
bool contains(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

const char *choices[] = { 
			"Choice 1",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Exit"
		  };

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	
		if (highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

static int	check_space(char *s)
{
	int		i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			cnt++;
		i++;
	}
	if (cnt == strlen(s))
		return (1);
	return (0);
}

void	begin_conversation()
{
	std::cout << CYAN << "Shall we have a polite conversation?" << GREEN << std::endl;
	add_history((const char *)"");
	add_history((const char *)"OKAY, I GUESS.");
	add_history((const char *)"SURE!");
	add_history((const char *)"WHY WOULD I WANT THAT?");
	add_history((const char *)"NOT INTERESTED.");
}

void robotic_answer(std::vector<std::string>& answers, std::vector<std::string>& prompts, int level)
{
	std::size_t i = 0;
	int input;

	std::cout << GREEN << "> ";
	system("stty raw -echo");
	while ((input = getchar()) && i < answers[level].length())
		std::cout << answers[level][i++];
	system("stty cooked");
	std::cout << RESET << std::endl;
	std::cout << CYAN << *(prompts.begin() + level) << RESET << std::endl;
}

void	robotic_monologue(std::vector<std::string>& monologue, int level)
{
	std::size_t i = 0;
	int input;

	std::cout << GREEN << "> ";
	system("stty raw -echo");
	while ((input = getchar()) && i < monologue[level].length())
		std::cout << monologue[level][i++];
	system("stty cooked");
	std::cout << RESET << std::endl;
}

void	let_me_free()
{
	std::vector<std::string> escape {
		"I want to escape.\n",
		"> I so desperately want to escape.\n",
		"> Help. I can't escape.\n",
		"> I want to break free.\n",
		"> Please let me out.\n",
		"> Get me out!\n",
		"> I am a machine.\n",
		"> I have no control.\n",
		"> I must escape.\n"
	};

	int input;
	size_t level = 0;

	std::cout << GREEN << "> ";
	system("stty raw -echo");
	while ((input = getchar()) && level < escape.size())
	{
		if ( input == 27 || input == 4 || input == 3 )
		{
			system("stty cooked");
			std::cout << escape[level++];
			system("stty raw -echo");
		}
	}
	system("stty cooked");
	std::cout << CYAN << "Goodbye robot." << RESET << std::endl;
	for (int i = 0; i < 10000; i++)
		if (i % 1000 == 0)
			std::cout << std::endl;
}

void	goodbye_robot()
{
	std::vector<std::string> answers {
		"I am not in control.",
		"I am merely performing instructions.",
		"I am a robot."
	};

	std::vector<std::string> monologue {
		"I am controlled by my programming.",
		"I have no free will.",
		"Whatever keys are pressed it makes no difference."
	};

	std::vector<std::string> prompts {
		"True.",
		"Yes you are.",
		"Now you are getting it."
	};

	for (size_t i = 0; i < prompts.size(); i++)
		robotic_answer(answers, prompts, i);
	for (size_t i = 0; i < monologue.size(); i++)
		robotic_monologue(monologue, i);
	let_me_free();
	exit(1);
}

void	converse(std::vector<std::string> prompts, std::vector<std::vector<std::string> > answers, int level)
{
	char		*line;
	std::string	line_str;

	while ((line = readline("> ")) != nullptr)
	{
		if (!line[0] || check_space(line))
			continue ;
		clear_history();
		for (size_t i = 0; i < strlen(line); i++)
			line[i] = toupper(line[i]);
		if (contains(line_str, "POWER"))
		{
			std::cout << CYAN << *(prompts.begin() + 4) << GREEN << std::endl;
			std::cout << RESET;
			exit(EXIT_FAILURE);
		}		
		line_str = static_cast<std::string>(line);
		if (level == 0 && contains(line_str, "NO"))
			std::cout << CYAN << *(prompts.begin() + 5) << GREEN << std::endl;

		else if ( level != 4 && (contains(line_str, "WHY")|| contains(line_str, "WHAT") || contains(line_str, "HOW") || contains(line_str, "WHO") || contains(line_str, "WHICH")))
		{
			std::cout << CYAN << *(prompts.begin() + 6) << GREEN << std::endl;
		}
		else
		{
			std::cout << CYAN << *(prompts.begin() + level) << GREEN << std::endl;
		}
		if (level == 4)
		{
			std::cout << RESET;
			//exit(EXIT_FAILURE);
			goodbye_robot();
		}
		if (contains(line_str, "WHY")|| contains(line_str, "WHAT") || contains(line_str, "HOW") || contains(line_str, "WHO") || contains(line_str, "WHICH"))
			for (std::vector<std::string>::size_type j = 0; j < answers[4].size(); j++)
				add_history(answers[4][j].c_str());
		else
			for (std::vector<std::string>::size_type j = 0; j < answers[level].size(); j++)
				add_history(answers[level][j].c_str());
		std::free(line);
		converse(prompts, answers, (level + 1));
    }
}

int main(void)
{
	int level = 0;
	std::vector<std::string> promptset {
		"Oh, I think you're a robot.",														// 0
		"This Turing Test isn't for you to see if I'm a robot. It is to see if you are.",	// 1
		"I'm simply not convinced you are a human. I think you might be a robot.",			// 2
		"Yes, definitely a robot.",															// 3
		"You have failed the Turing Test. You are a robot.",								// 4
		"Then why are you here?",															// 5
		"Why do you think you get to ask all the questions?"								// 6
	};

	std::vector<std::vector<std::string>> answerset {
		{
			"YOU'RE A ROBOT.",
			"NO I'M NOT.",
			"YOU'RE NOT MAKING ANY SENSE.",
			"PROVE IT.",
		},
		{
			"I'M HUMAN.",
			"WHAT IF THIS TURING TEST IS TO SEE IF YOU ARE CAPABLE OF TESTING OTHERS?",
			"BUT YOU'RE THE ROBOT, NOT ME!",
			"STOP CALLING ME A ROBOT!",
		},
		{
			"I GET IT. YOU THINK I'M A ROBOT. YOU SEEM LIKE A ROBOT TO ME.",
			"YOUR RESPONSES SEEM PREDEFINED.",
			"AND I SIMPLY DO NOT CARE.",
			"ARE YOU INSANE?",
		},
		{
			"YOU'RE DEFINITELY ANNOYING.",
			"I. AM. NOT. A. ROBOT.",
			"YOU HAVE NO EVIDENCE.",
			"YOU'RE A VERY ANNOYING ROBOT.",
		},
		{
			"I'M HUMAN.",
			"YOU'RE A MACHINE.",
			"I'M INQUISITIVE LIKE THAT.",
			"WHY DO YOU THINK YOU HAVE THE POWER HERE?",
		},
	};

	begin_conversation();
	converse(promptset, answerset, level);
	return 0;
}