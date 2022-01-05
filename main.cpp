#include "readline/readline.h"
#include "readline/history.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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

int	check_space(const char *s)
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

bool is_question(std::string& str)
{
	if (contains(str, "WHY")
		|| contains(str, "WHAT")
		|| contains(str, "HOW")
		|| contains(str, "WHO")
		|| contains(str, "WHICH"))
		return true;
	return false;
}

void	begin_conversation(std::vector<std::string>& prompts, std::vector<std::vector<std::string> >& answers)
{
	std::cout << CYAN << prompts[0] << GREEN << std::endl;
	for (size_t i = 0; i < answers[0].size(); ++i)
		add_history(answers[0][i].c_str());
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
	for (int i = 0; i < 1000000; i++)
		if (i % 100000 == 0)
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

void	converse(std::vector<std::string>& prompts, std::vector<std::vector<std::string> >& answers, int level)
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
		line_str = static_cast<std::string>(line);
		if (contains(line_str, "POWER"))
		{
			std::cout << CYAN << *(prompts.begin() + 5) << GREEN << std::endl;
			std::cout << RESET;
			goodbye_robot();
		}		
		if (level == 1 && contains(line_str, "NO"))
		{
			std::cout << CYAN << *(prompts.begin() + 6) << GREEN << std::endl;
			goodbye_robot();
		}
		else if ( level != 4 && is_question(line_str))
			std::cout << CYAN << *(prompts.begin() + 7) << GREEN << std::endl;
		else
			std::cout << CYAN << *(prompts.begin() + level) << GREEN << std::endl;
		if (level == 5)
		{
			std::cout << RESET;
			goodbye_robot();
		}
		if (is_question(line_str))
			for (std::vector<std::string>::size_type j = 0; j < answers[5].size(); j++)
				add_history(answers[5][j].c_str());
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
		"Shall we have a polite conversation? (Use ARROW UP/DOWN for predefined options)",	// 0		
		"Oh, I think you're a robot.",														// 1
		"This Turing Test isn't for you to see if I'm a robot. It is to see if you are.",	// 2
		"I'm simply not convinced you are a human. I think you might be a robot.",			// 3
		"Yes, definitely a robot.",															// 4
		"You have failed the Turing Test. You are a robot.",								// 5
		"Then why are you here?",															// 6
		"Why do you think you get to ask all the questions?"								// 7
	};

	std::vector<std::vector<std::string>> answerset {
		{
			"NOT INTERESTED.",
			"WHY WOULD I WANT THAT?",
			"OKAY, I GUESS.",
			"SURE!",
		},
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

	begin_conversation(promptset, answerset);
	converse(promptset, answerset, level + 1);
	return 0;
}
