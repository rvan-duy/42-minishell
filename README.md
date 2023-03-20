# 42-minishell
This project is a simple command-line interpreter, also known as a shell. It allows users to execute basic shell commands such as "ls", "cd", "echo", and "pwd". In addition, it supports pipes and redirections.

## Requirements
- A C compiler
- Make
- Git

## Installation
To install the Minishell project, follow these steps:

1. Clone this repository onto your local machine.
```bash
git clone https://github.com/rvan-duy/42-minishell.git
```
2. Navigate to the project directory.
```bash
cd minishell
```
3. Compile the project using the Makefile.
```bash
make
```
4. Run the executable file.
```bash
./minishell
```

## Usage
To use the Minishell project, simply enter a command at the prompt and press "Enter". For example:

```bash
$ ls
```

You can also use pipes and redirections to modify the input and output of commands. For example:

```bash
$ ls | grep foo > output.txt
```
This command will list all files in the current directory that contain the string "foo" and save the output to a file called "output.txt".

## Contributing
Contributions to the Minishell project are welcome. If you find a bug or have an idea for a new feature, please open an issue on the project's GitHub page.
