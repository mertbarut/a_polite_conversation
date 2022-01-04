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

void	begin_conversation()
{
	std::cout << CYAN << "Shall we have a polite conversation?" << GREEN << std::endl;
	add_history((const char *)"");
	add_history((const char *)"OKAY, I GUESS.");
	add_history((const char *)"SURE!");
	add_history((const char *)"WHY WOULD I WANT THAT?");
	add_history((const char *)"NOT INTERESTED.");
}

void	converse(std::vector<std::string> prompts, std::vector<std::vector<std::string>> answers, int level)
{
	char		*line;

	while ((line = readline("> ")) != nullptr)
	{
		clear_history();
		std::cout << CYAN << *(prompts.begin() + level) << GREEN << std::endl;
		if (level == 4)
			exit(EXIT_FAILURE);
		for (std::vector<std::string>::size_type j = 0; j < answers.size(); j++)
			add_history(answers[level][j].c_str());
		std::free(line);
		converse(prompts, answers, (level + 1));
    }
}

int main(void)
{
	int level = 0;
	std::vector<std::string> promptset {
		"Oh, I think you're a robot.",
		"This Turing Test isn't for you to see if I'm a robot. It is to see if you are.",
		"I'm simply not convinced you are a human. I think you might be a robot.",
		"Yes, definitely a robot.",
		"You have failed the Turing Test. You are a robot."
	};

	std::vector<std::vector<std::string>> answerset {
		{
		"",
		"YOU'RE A ROBOT.",
		"NO I'M NOT.",
		"YOU'RE NOT MAKING ANY SENSE.",
		"PROVE IT.",
		},
		{
		"",
		"I'M HUMAN.",
		"WHAT IF THIS TURING TEST IS TO SEE IF YOU ARE CAPABLE OF TESTING OTHERS?",
		"BUT YOU'RE THE ROBOT, NOT ME!",
		"STOP CALLING ME A ROBOT!",
		},
		{
		"",
		"I GET IT. YOU THINK I'M A ROBOT. YOU SEEM LIKE A ROBOT TO ME.",
		"YOUR RESPONSES SEEM PREDEFINED.",
		"AND I SIMPLY DO NOT CARE.",
		"ARE YOU INSANE?",
		},
		{
		"",
		"YOU'RE DEFINITELY ANNOYING.",
		"I. AM. NOT. A. ROBOT.",
		"YOU HAVE NO EVIDENCE.",
		"YOU'RE A VERY ANNOYING ROBOT.",
		}
	};

	begin_conversation();
	converse(promptset, answerset, level);

    return 0;
}
