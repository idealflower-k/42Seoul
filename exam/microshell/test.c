#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void	write_error(char* str) {
	while (*str)
		write(2, str++, 1);
}

void	cd_exe(int idx, int cmd_num, char** av) {
	if (cmd_num != 1) {
		write_error("error: cd: bad arguments\n");
		return ;
	}
	char *path = av[idx - cmd_num];
	if (chdir(path) == -1) {
		write_error("error: cd: cannot change directory to ");
		write_error(path);
		write_error("\n");
	}
}

int	exe_pipe(int path_idx, int cmd_num, char** av, char** env, int pre_fd) {
	char *arr[100];
	for (int i = 0; i < 100; i++)
		arr[i] = NULL;
	for (int i = 0; (i < cmd_num && strcmp(av[path_idx + i], ";")); i++) {
		arr[i]	= av[path_idx + i];
	}
	int	_pipe[2];
	if (pipe(_pipe) == -1) {
		write_error("error: fatal\n");
		exit(1);
	}
	int pid = fork();
	if (pid == -1) {
		write_error("error: fatal\n");
		exit(1);
	}
	if (pid == 0) {
		close(_pipe[0]);
		_pipe[0] = pre_fd;
		dup2(_pipe[0], 0);
		close(_pipe[0]);
		dup2(_pipe[1], 1);
		close(_pipe[1]);
		execve(arr[0], arr, env);
		write_error("error: cannot execute ");
		write_error(arr[0]);
		write_error("\n");
		exit(1);
	}
	else {
		if (pre_fd > 0)
			close(pre_fd);
		close(_pipe[1]);
	}
	return (_pipe[0]);
}

void	exe_last(int path_idx, int cmd_num, char** av, char** env, int pre_fd) {
	char *arr[100];
	for (int i = 0; i < 100; i++)
		arr[i] = NULL;
	for (int i = 0; (i < cmd_num && strcmp(av[path_idx + i], ";")); i++) {
		arr[i]	= av[path_idx + i];
	}
	int pid = fork();
	if (pid == -1) {
		write_error("error: fatal\n");
		exit(1);
	}
	if (pid == 0) {
		if (pre_fd > 0) {
			dup2(pre_fd, 0);
			close(pre_fd);
		}
		execve(arr[0], arr, env);
		write_error("error: cannot execute ");
		write_error(arr[0]);
		write_error("\n");
		exit(1);
	}
}

int	main(int ac, char** av, char** env)
{
	if (ac < 2)
		exit(1);
	int	idx = 1;
	int pre_fd = 0;
	int num_exe = 0;
	while (av[idx] != NULL) {
		int cmd_num = 0;
		if (!strcmp(av[idx], ";"))
			idx++;
		else if (!strcmp(av[idx], "cd")) {
			idx++;
			while (av[idx] != NULL && strcmp(av[idx], ";")) {
				idx++;
				cmd_num++;
			}
			cd_exe(idx, cmd_num, av);
		}
		else if (strcmp(av[idx], "|") && strcmp(av[idx], ";")) {
			int path_idx = idx;
			while (av[idx] != NULL && strcmp(av[idx], "|") && strcmp(av[idx], ";")) {
				idx++;
				cmd_num++;
			}
			if (av[idx] != NULL && !strcmp(av[idx], "|")) {
				pre_fd = exe_pipe(path_idx, cmd_num, av, env, pre_fd);
				idx++;
				num_exe++;
			}
			else if (av[idx] == NULL || !strcmp(av[idx], ";")) {
				exe_last(path_idx, cmd_num, av, env, pre_fd);
				if (av[idx] != NULL && !strcmp(av[idx], ";"))
					idx++;
				num_exe++;
				if (pre_fd > 0)
					close(pre_fd);
			}
		}
	}
	for (int i = 0; i < num_exe; i++)
		wait(0);
	exit(0);
}