//============================================================================
// Name        : Judgelient.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/signal.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#define STD_MB 1048576LL
#define BUFFER_SIZE 5120


#define OJ_WI 0
#define OJ_AC 1
#define OJ_CE 2
#define OJ_WA 3
#define OJ_TL 4
#define OJ_ML 5
#define OJ_RE 6
#define OJ_OL 7
#define OJ_SE 8

int ACflag = OJ_WI;

long get_file_size(const char * filename) {
	struct stat f_stat;

	if (stat(filename, &f_stat) == -1) {
		return 0;
	}

	return (long) f_stat.st_size;
}

int get_proc_status(int pid, const char * mark) {
	FILE * pf;
	char fn[BUFFER_SIZE], buf[BUFFER_SIZE];
	int ret = 0;
	sprintf(fn, "/proc/%d/status", pid);
	pf = fopen(fn, "re");
	int m = strlen(mark);
	while (pf && fgets(buf, BUFFER_SIZE - 1, pf)) {

		buf[strlen(buf) - 1] = 0;
		if (strncmp(buf, mark, m) == 0) {
			sscanf(buf + m + 1, "%d", &ret);
		}
	}
	if (pf)
		fclose(pf);
	return ret;
}
/*
 *
 */
int isInFile(const char fname[]) {
	int l = strlen(fname);
	if (l <= 3 || strcmp(fname + l - 3, ".in") != 0)
		return 0;
	else
		return l - 3;
}
int compile(int lang,char * FILE_PATH)
{
	const char * CP_C[] = { "gcc","Main.c", "-o", "Main","-O2", "-fmax-errors=10", "-Wall",
			"-lm", "--static","-std=c99", "-DONLINE_JUDGE", NULL };
	const char * CP_X[] = { "g++", "-fno-asm", "-fmax-errors=10", "-Wall",		//C++
			"-lm", "--static", "-std=c++11", "-DONLINE_JUDGE", "-o", "Main", "Main.cc", NULL };

	pid_t pid = fork();
	if(pid == 0)
	{			freopen("ce.txt", "w", stderr);
				chroot(FILE_PATH);
				struct rlimit LIM;
				int cpu=6;	//the max run_time
				//if (lang==3) cpu=30;
				LIM.rlim_max = cpu;
				LIM.rlim_cur = cpu;
				setrlimit(RLIMIT_CPU, &LIM);

				alarm(cpu);	//cpu秒后用信号结束程序
				LIM.rlim_max = 40 * STD_MB;
				LIM.rlim_cur = 40 * STD_MB;
				setrlimit(RLIMIT_FSIZE, &LIM);

				switch (lang) {
				case 0:
					execvp(CP_C[0], (char * const *) CP_C);
					break;
				case 1:
					execvp(CP_X[0], (char * const *) CP_X);
					break;
				}
				exit(0);
	}
	else
	{
		int status = 0;

		waitpid(pid, &status, 0); //等待子进程pid结束


		return status;
	}
}
void run_solution(char * PATH,int timelmt,int memlmt,char* inputFile)
{
					chroot(PATH);
                    memlmt /= 1024;
					freopen(inputFile,"r",stdin);
					freopen("user.out","w",stdout);
					freopen("error.out", "a+", stderr);
					struct rlimit LIM;
					//int cpu=20;	//the max run_time
					//if (lang==3) cpu=30;
					timelmt = timelmt/1000+1;
					LIM.rlim_max = timelmt;
					LIM.rlim_cur = timelmt;
					setrlimit(RLIMIT_CPU, &LIM);

					alarm(timelmt);	//cpu秒后用信号结束程序
					LIM.rlim_max = 40 * STD_MB;
					LIM.rlim_cur = 40 * STD_MB;
					setrlimit(RLIMIT_FSIZE, &LIM);

					// set the stack
					LIM.rlim_cur = STD_MB << 7;
					LIM.rlim_max = STD_MB << 7;
					setrlimit(RLIMIT_STACK, &LIM);
						// set the memory
					LIM.rlim_cur = STD_MB * memlmt / 2 * 3;
					LIM.rlim_max = STD_MB * memlmt * 2;
					setrlimit(RLIMIT_AS, &LIM);
					// proc limit
					LIM.rlim_cur = LIM.rlim_max = 1;
					setrlimit(RLIMIT_NPROC, &LIM);
	execl("./Main", "./Main", (char *) NULL);

	exit(0);

}
int run_time=0,run_mem=0;
void watch_solution(pid_t pidApp,int timelmt,int memlmt)
{
	int status, sig, exitcode;
	struct user_regs_struct reg;
	struct rusage ruse;
	int first = true;
	int memory = 0;
		while (1)
		{
			wait4(pidApp, &status, __WALL, &ruse);
					if(first){ //
						ptrace(PTRACE_SETOPTIONS, pidApp, NULL, PTRACE_O_TRACESYSGOOD
											|PTRACE_O_TRACEEXIT
										//	|PTRACE_O_EXITKILL
										//	|PTRACE_O_TRACECLONE
										//	|PTRACE_O_TRACEFORK
										//	|PTRACE_O_TRACEVFORK
						);
					}
			//获取内存
			int tempmemory =  get_proc_status(pidApp, "VmPeak:") << 10;
			if(tempmemory>memory) memory = tempmemory;
			if(tempmemory>memlmt*STD_MB)
			{
				ptrace(PTRACE_KILL, pidApp, NULL, NULL);
				ACflag = OJ_ML;
				printf("memory out!!!");
				break;
			}
			if (WIFEXITED(status))
			break;

			exitcode = WEXITSTATUS(status);

			if(exitcode == 0x05 || exitcode == 0 || exitcode == 133) ;
			else
			{
				if (ACflag == OJ_WI) {
								switch (exitcode) {
								case SIGCHLD:
								case SIGALRM:
									alarm(0);
									printf("alarm:%d\n",timelmt);
								case SIGKILL:
								case SIGXCPU:
									ACflag = OJ_TL;

									printf("TLE\n");
									break;
								case SIGXFSZ:
									ACflag = OJ_OL;
									break;
								default:
									ACflag = OJ_RE;
								}

							}

				ptrace(PTRACE_KILL, pidApp, NULL, NULL);
				printf("exception!!!\n");
				break;
			}
			if (WIFSIGNALED(status))
			{	sig = WIFSIGNALED(status);
				if (ACflag == OJ_WI) {
					switch (sig) {
					case SIGCHLD:
					case SIGALRM:
						alarm(0);
					case SIGKILL:
					case SIGXCPU:
						ACflag = OJ_TL;
						break;
					case SIGXFSZ:
						ACflag = OJ_OL;
						break;

					default:
						ACflag = OJ_RE;
					}
				}
				break;
			}

			ptrace(PTRACE_SYSCALL, pidApp, NULL, NULL);
			first = false;

		}
		int usedtime = 0;
		usedtime += (ruse.ru_utime.tv_sec * 1000 + ruse.ru_utime.tv_usec / 1000) * 1.0;
		usedtime += (ruse.ru_stime.tv_sec * 1000 + ruse.ru_stime.tv_usec / 1000) * 1.0;
		if(usedtime > timelmt) ACflag = OJ_TL;
		printf("memory:%.2f M  run_time:%d ms\n",memory*1.0/STD_MB,usedtime);

		if(usedtime>run_time) run_time = usedtime;
		if(memory>run_mem) run_mem = memory;

}
int judge_solution(char * output)
{
	int ret = OJ_AC;

	FILE * f1, *f2;
	f1 = fopen(output, "re");
	f2 = fopen("user.out", "re");
	if(!f1 || !f2)
	{
		ret = OJ_SE;

	}
	else
	{	int c1,c2;
		c1 = fgetc(f1);
		c2 = fgetc(f2);
		while(c1!=EOF && c2!=EOF)
		{
			if(c1!=c2) break;
			do
			{
				c1 = fgetc(f1);
			}while(c1=='\r'||c1=='\n');
			do
			{
				c2 = fgetc(f2);
			}while(c2=='\r'||c2=='\n');
		}
		if(c1==c2&&c1==EOF) ret = OJ_AC;
		else ret = OJ_WA;

	}

	if (f1)
		fclose(f1);
	if (f2)
		fclose(f2);
	return ret;
}
char PATH[100],temp[100];
void judgeMain(const char*path,char*solution)
{
		strcpy(temp,path);
		int j,timelmt=0,memlmt=0;
		for(j=0;temp[j]&&temp[j]!='#';j++);
		temp[j]='\0';
		strcpy(PATH,temp);
		temp[j]='#';

		for(j=j+1;temp[j]&&temp[j]!='#';j++)
		{
			timelmt=timelmt*10+temp[j]-'0';
		}
		for(j=j+1;temp[j]&&temp[j]!='#';j++)
		{
			memlmt=memlmt*10+temp[j]-'0';
		}
		if(memlmt==0||timelmt==0)
		{
			ACflag = OJ_SE;
			sprintf(solution,"%d#%d#%d#",ACflag,0,0);
            return ;
		}
		chdir(PATH);
		int compile_ok = compile(1,PATH);

		int i;


		if(compile_ok != 0)
		{
			printf("compile failed !\n");
			ACflag = OJ_CE;
		}
		else{

			printf("compile success !\n");
			int testnum = 0;
			DIR *dp;
			dirent *dirp;
			if((dp = opendir(PATH)) == NULL)
			{
				ACflag = OJ_SE;
			}
			while(ACflag == OJ_WI && (dirp = readdir(dp)) != NULL)
			{

				if (isInFile(dirp->d_name) == 0)
					continue;
				char outfile[20];
				strcpy(outfile,dirp->d_name);
				int l = strlen(outfile);
				strcpy(outfile+l-2,"out");

				if(access(outfile, 0) == -1 )
				{
					printf("%s not exsist\n",outfile);
					continue;
				}
				pid_t pid = fork();
				if(pid == 0)
				{			//I am child thread
					ptrace(PTRACE_TRACEME, 0, NULL, NULL);
					run_solution(PATH,timelmt,memlmt,dirp->d_name);

				}
				else
				{
					watch_solution(pid,timelmt,memlmt);
					if(ACflag == OJ_WI)
						ACflag = judge_solution(outfile);
				}
			}
		}
		if(ACflag == OJ_WI) ACflag == OJ_AC;

		switch(ACflag)
		{
		case OJ_AC : printf("Accept\n");break;
		case OJ_CE : printf("Compile error\n");break;
		case OJ_TL : printf("Timeout\n");break;
		case OJ_ML : printf("Memory out limit\n");break;
		case OJ_RE : printf("Runtime error\n");break;
		case OJ_SE : printf("System error\n");break;
		case OJ_OL : printf("Output out limit\n");break;
		case OJ_WA : printf("Wrong answer\n");break;
		}
		sprintf(solution,"%d#%d#%d#",ACflag,run_time,run_mem);
		return ;
}
/*
int main() {

	printf("Input your cpp file path:\n");
	scanf("%s",PATH);
	chdir(PATH);
	int compile_ok = compile(1,PATH);
	int timelmt = 1200; //ms
	int memlmt = 6;	//MB
	if(compile_ok != 0)
	{
		printf("compile failed !\n");
		ACflag = OJ_CE;
	}
	else{

		printf("compile success !\n");
		int testnum = 0;
		DIR *dp;
		dirent *dirp;
		if((dp = opendir(PATH)) == NULL)
		{
			ACflag = OJ_SE;
		}
		while(ACflag == OJ_WI && (dirp = readdir(dp)) != NULL)
		{

			if (isInFile(dirp->d_name) == 0)
				continue;
			char outfile[20];
			strcpy(outfile,dirp->d_name);
			int l = strlen(outfile);
			strcpy(outfile+l-2,"out");

			if(access(outfile, 0) == -1 )
			{
				printf("%s not exsist\n",outfile);
				continue;
			}
			pid_t pid = fork();
			if(pid == 0)
			{			//I am child thread
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				run_solution(PATH,timelmt,memlmt,dirp->d_name);

			}
			else
			{
				watch_solution(pid,timelmt,memlmt);
				if(ACflag == OJ_WI)
					ACflag = judge_solution(outfile);
			}
		}
	}
	if(ACflag == OJ_WI) ACflag == OJ_AC;

	switch(ACflag)
	{
	case OJ_AC : printf("Accept\n");break;
	case OJ_CE : printf("Compile error\n");break;
	case OJ_TL : printf("Timeout\n");break;
	case OJ_ML : printf("Memory out limit\n");break;
	case OJ_RE : printf("Runtime error\n");break;
	case OJ_SE : printf("System error\n");break;
	case OJ_OL : printf("Output out limit\n");break;
	case OJ_WA : printf("Wrong answer\n");break;
	}
	return 0;
}
*/

