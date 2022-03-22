/** 
  test_helper.c  
**/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "unittest_defs.h"
#include "test_helper.h"

int debug_mode = 0;

int test_assert_file_exist(const char* filename)
{
  FILE *fp;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    fclose(fp);
    return(1);
  }
  return(0);
}

double get_preset_ucvm_surface(double y, double x) {
   if(y == -118.1 && x == 34.0) {
      return 55.827;
   }
   return 0;
}


/* Execute cvms_txt as a child process */
int runCVMSTxt(const char *bindir, const char *infile, const char *outfile)
{
  char currentdir[1280];
  char runpath[1280];

  sprintf(runpath,"%s/run_cvms_txt.sh", bindir);

  /* Save current directory */
  getcwd(currentdir, 1280);
  
  /* Fork process */
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    return(1);
  } else if (pid == 0) {
    /* Change dir to cvmdir */
    if (chdir(bindir) != 0) {
      printf("FAIL: Error changing dir in runfortran\n");
      return(1);
    }

    execl( runpath, runpath, infile, outfile, (char *)0);
    perror("execl"); /* shall never get to here */
    printf("FAIL: CVM exited abnormally\n");
    return(1);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      return(0);
    } else {
      printf("FAIL: CVM exited abnormally\n");
      return(1);
    }
  }

  return(0);
}

/*************************************************************************/
int runCVMS(const char *bindir, const char *cvmdir, 
	  const char *infile, const char *outfile, int mode)
{
  cvms_point_t pt;
  cvms_properties_t ret;

  FILE *infp, *outfp;
  char line[1000];

  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvms"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvms"), 0) != 0) {
    return(1);
  }

  if (test_assert_int(model_setparam(0, UCVM_PARAM_QUERY_MODE, mode), 0) != 0) {
      return(1);
  }

  /* open infile, outfile */
  infp = fopen(infile, "r");
  if (infp == NULL) {
    printf("FAIL: cannot open %s\n", infile);
    return(1);
  }
  outfp = fopen(outfile, "w");
  if (outfp == NULL) {
    printf("FAIL: cannot open %s\n", outfile);
    return(1);
  }

/* process one term at a time */
  while(fgets(line, 1000, infp) != NULL) {
    if(line[0] == '#') continue; // a comment 
    if (sscanf(line,"%lf %lf %lf",
         &pt.longitude,&pt.latitude,&pt.depth) == 3) {
      if (test_assert_int(model_query(&pt, &ret, 1), 0) == 0) {
         fprintf(outfp,"%lf %lf %lf %lf %lf %lf\n", pt.longitude, pt.latitude, pt.depth, ret.vs, ret.vp, ret.rho);
      }
    }
  }
  fclose(infp);
  fclose(outfp);
                
  if (test_assert_int(model_finalize(),0) != 0) {
      return(1);
  }

  return(0);
}



int runVXCVMS(const char *bindir, const char *cvmdir,
          const char *infile, const char *outfile)
{
  char currentdir[1280];
  char runpath[1280];
  char flags[1280]="";

  sprintf(runpath, "%s/run_vx_cvms.sh", bindir);

  if(debug_mode) { strcat(flags, "-d "); }

  /* Save current directory */
  getcwd(currentdir, 1280);

  /* Fork process */
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    return(1);
  } else if (pid == 0) {
    /* Change dir to cvmdir */
    if (chdir(bindir) != 0) {
      printf("FAIL: Error changing dir in run_vx_cvms.sh\n");
      return(1);
    }

    if (strlen(flags) == 0) {
      execl(runpath, runpath, infile, outfile, (char *)0);
    } else {
      execl(runpath, runpath, flags, infile, outfile, (char *)0);
    }

    perror("execl"); /* shall never get to here */
    printf("FAIL: CVM exited abnormally\n");
    return(1);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      return(0);
    } else {
      printf("FAIL: CVM exited abnormally\n");
      return(1);
    }
  }

  return(0);
}


