# Pipex

## Description

In this 42 project you have to recreate the functionality of pipes in a shell.

The aim of this project is to learn how pipes work in a shell. Furthermore, you learn how to fork processes and how to efficiently work with file descriptors.

## Usage

The mandatory part of the project will be executed as follow: **./pipex file1 cmd1 cmd2 file2**

* **file1** and **file2** are file names
* **cmd1** and **cmd2** are shell commands with their parameters

It behaves exactly the same as the shell command below:

```bash
$> < file1 cmd1 | cmd2 > file2
```

### Examples

```bash
$> ./pipex infile "ls -l" "wc -l" outfile
```
Behaves like: < infile ls -l | wc -l > outfile
```bash
$> ./pipex infile "grep a1" "wc -w" outfile 
```
Behaves like: < infile grep a1 | wc -w > outfile

### Bonus part

This project also handles multiple pipes when more then 2 commands are given.

```bash
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Behaves like: < infile cmd1 | cmd2 | cmd3 | ... | cmdn > file2
