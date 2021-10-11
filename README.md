<h1 align="center">Minishell 🐚</h1>
<h4 align="center">As beautiful as a shell </h4>

<p align="center">

 <img alt="Github top language" src="https://img.shields.io/github/languages/top/anolivei/Minishell42?color=3de069">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/anolivei/Minishell42?color=3de069">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/anolivei/Minishell42?color=3de069">

  <img alt="Norminette" src="https://github.com/anolivei/Minishell42/actions/workflows/norminette.yml/badge.svg?event=push">
</p>

<p align="center">
  <a href="#about">About</a> &#xa0; | &#xa0;
  <a href="#links">Links</a> &#xa0; | &#xa0;
  <a href="#functions">Functions</a> &#xa0; | &#xa0;
  <a href="#starting">Starting</a>
</p>


## About ##

- Minishell is a project at school 42 and the instructions were given in the [subject](https://github.com/anolivei/Minishell42/blob/main/subject.pdf).

- The objective of this project is to create a simple shell to learn a lot about processes and file descriptors.

- The existence of shells is linked to the very existence of IT. At the time, all coders agreed that communicating with a computer using aligned 1/0 switches was seriously irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close to english.
With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.

## Links ##

- [Notion](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)

- [Linux Commands](https://www.rapidtables.com/code/linux/index.html)

- [Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=1)

- [Writing a Unix Shell - Part I](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)

- [Writing a Unix Shell - Part II](https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/)

- [Writing a Unix Shell - Part III](https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/)

- [Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)

- [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/index.html)

- [To Understand Pipe](https://www.youtube.com/watch?v=uHH7nHkgZ4w)

- [To Understand Dup](https://www.youtube.com/watch?v=EqndHT606Tw)

- [Pipe and Dup](https://www.youtube.com/watch?v=fOaK6oRqhEo)


## Functions ##
Only the following functions are allowed to be used in this project:<br>
| Function | Description | Function | Description |
|----------|-------------|----------|-------------|
|readline | read a line from the terminal |lstat | get file status | 
|rl_clear_history | clear the history list by deleting all of the entries | fstat | get file status by fd |
|rl_on_new_line | tell the update routines that we have moved onto a new line | unlink | remove a specified file |
|rl_replace_line | replace the contents of rl_line_buffer with text | execve | execute program |
|rl_redisplay | change what's displayed on the screen | dup | duplicate a file descriptor |
|add_history | save the line in a history list of lines | dup2 | duplicate a file descriptor |
|printf | format and print data | pipe | create pipe |
|malloc | allocate dynamic memory | opendir | open a directory |
|free | free dynamic memory | readdir | read a directory |
|write | write to a file descriptor | closedir | close a directory |
|access | check user's permissions for a file | strerror | return string describing error number |
|open | open and can create a file | perror | print a system error message |
|read | read from a file descriptor | isatty | test whether a file descriptor refers to a terminal |
|close | close a file descriptor | ttyname | return name of a terminal |
|fork | create a child process | ttyslot | find the slot of the current user's terminal in some file |
|wait | wait for process to change state | ioctl | control device |
|waitpid | wait for process to change state | getenv | get an environment variable |
|wait3 | wait for process to change state | tcsetattr | control asynchronous communications ports |
|wait4 | wait for process to change state | tcgetattr | control asynchronous communications ports |
|signal | ANSI C signal handling | tgetent | termcap database emulation |
|sigaction | examine and change a signal action | tgetflag |  termcap database emulation |
|kill | send signal to a process | tgetnum |  termcap database emulation |
|exit | cause normal process termination | tgetstr | termcap database emulation |
|getcwd | get current working directory | tgoto | termcap database emulation |
|chdir | change working directory | tputs | curses interfaces to terminfo database |
|stat | get file status by pathname |

## Starting ##

```bash
# Clone this project
$ git clone https://github.com/anolivei/Minishell42

# Access
$ cd Minishell42

# Install the readline lib
$ sudo apt-get install libreadline6-dev

# Compile the project
$ make

# Run the project
$ ./minishell

```
<p align="center">
<img width="500px" src="./bighell.png?raw=true" />
</p>
&#xa0;

<a href="#top">Back to top</a>
