#include <cstdlib>
#include <cstring>
#include <iostream>
#include "readline/readline.h"
#include "readline/history.h"
#include <stdlib.h>
#include <string>
#include <vector>

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

		else if (contains(line_str, "WHY")|| contains(line_str, "WHAT") || contains(line_str, "HOW") || contains(line_str, "WHO") || contains(line_str, "WHICH"))
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
			exit(EXIT_FAILURE);
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
