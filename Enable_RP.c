#include<stdio.h>
#include<string.h>
#include <libcgroup.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/types.h>
#define dbnamecount 4




int main(){
	int dbfound=2;
	char *dbnames[]= {"matho-primes","matho-primes","matho-primes","matho-primes"};
	//char *dbnames[]= {"mysqld","oracle","mongod","couchdb"};
	char *substring=NULL;
	char line[100]="";
	char *process_command = NULL;
	char *token=NULL;
	char *command=NULL;
	int pid;
        int ret;
	int flag=0;
        char string[100];
	pid_t _pid1;
        struct cgroup_controller  *cpu;
        char *mount_point;
        int a_a=0;
         pid_t sid,ssid;

    /* Fork off the parent process */
        sid = fork();
        

  if (sid < 0) {
                exit(EXIT_FAILURE);
        }
if (sid > 0) {
 printf ("pid > 0\n");
             //   exit(EXIT_SUCCESS);
        }

umask(0);

 ssid = setsid();


        
//starting of creation of cgroups
printf("Cgroup successfully created");

	ret = cgroup_init();
        if (ret) {
		//printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
		//printf("FAIL: c");
		//exit(3);
	}

//aDDING CPU DETAILS
	strcpy(string, "cpu");
	ret = cgroup_get_subsys_mount_point(string, &mount_point);
	
	if (ret) {
		//printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
		//printf("FAIL: c");
		//exit(3);
	}

//creation of hirhy of cgroup for cpu a1(databse specific)....a2 others..
//within a1 - 4 parts for instance caging

//===========================adding a1/b0===============================


	
struct cgroup *myCg = cgroup_new_cgroup("a1/b0");
struct cgroup_controller *myMemCtl = cgroup_add_controller(myCg,"cpu");
cgroup_set_value_int64(myMemCtl,"cpu.shares",2048);
	
ret = cgroup_create_cgroup(myCg, 1);
	
	if (ret) {
		//exit(3);
	}



//===========================adding a1/b1===============================

struct cgroup *myCg1 = cgroup_new_cgroup("a1/b1");
struct cgroup_controller *myMemCtl1 = cgroup_add_controller(myCg1,"cpu");
cgroup_set_value_int64(myMemCtl1,"cpu.shares",1024);
ret = cgroup_create_cgroup(myCg1, 1);
	if (ret) {
		
		//exit(3);
	}


//========================adding a1/b2========================


struct cgroup *myCg2 = cgroup_new_cgroup("a1/b2");
struct cgroup_controller *myMemCtl2 = cgroup_add_controller(myCg2,"cpu");
cgroup_set_value_int64(myMemCtl2,"cpu.shares",512);
ret = cgroup_create_cgroup(myCg2, 1);
	if (ret) {
		printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		//exit(3);
	}

//printf("after creation b3\n");

//========================adding a1/b3========================


struct cgroup *myCg3 = cgroup_new_cgroup("a1/b3");
struct cgroup_controller *myMemCtl3 = cgroup_add_controller(myCg3,"cpu");
cgroup_set_value_int64(myMemCtl3,"cpu.shares",256);
ret = cgroup_create_cgroup(myCg3, 1);
	if (ret) {
		printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		//exit(3);
	}

//=============================adding a2===========================

struct cgroup *myCga2 = cgroup_new_cgroup("a2");
struct cgroup_controller *myMemCtla2 = cgroup_add_controller(myCga2,"cpu");
ret = cgroup_set_value_int64(myMemCtla2,"cpu.shares",50);

ret = cgroup_create_cgroup(myCga2, 1);
	if (ret) {
		printf("FAIL: error rassss   cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
		exit(3);
	}




//=================================CPUSET=======================================


strcpy(string, "cpuset");
ret = cgroup_get_subsys_mount_point(string, &mount_point);


//=================================setting allowed cpus in the set,kernel will do atomatic load balancing,=======================================
//sched_relax_domain_level===========is set to high the wider the range of CPUs over which immediate load balancing is attempted

struct cgroup *myCgcAl = cgroup_new_cgroup("a1");
struct cgroup_controller *myMemCtlcAl = cgroup_add_controller(myCgcAl,"cpuset");
ret = cgroup_set_value_string(myMemCtlcAl,"cpuset.cpus","0-2");
//ret = cgroup_set_value_int64(myMemCtlcAl,"cpuset.sched_relax_domain_level",1);

ret = cgroup_create_cgroup(myCgcAl, 1);
	if (ret) {
		printf("FAIL: error rassss  hereeeee cpusettt cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
		//exit(3);
	}


//=================================a2=======================================



struct cgroup *myCgca2 = cgroup_new_cgroup("a2");
struct cgroup_controller *myMemCtlca2 = cgroup_add_controller(myCgca2,"cpuset");
ret = cgroup_set_value_string(myMemCtlca2,"cpuset.cpus","3");


ret = cgroup_create_cgroup(myCgca2, 1);
	if (ret) {
		printf("FAIL: error rassss  cpusettt cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
		exit(3);
	}





//=====================================aDDING MEMORY DETAILS====================
strcpy(string,"memory");
ret = cgroup_get_subsys_mount_point(string, &mount_point);

struct cgroup *myCgcm1 = cgroup_new_cgroup("a1");
struct cgroup_controller *myMemCtlcm1 = cgroup_add_controller(myCgcm1,"memory");
ret = cgroup_set_value_uint64(myMemCtlcm1,"memory.soft_limit_in_bytes",9999999999);
ret = cgroup_create_cgroup(myCgcm1, 1);
	if (ret) {
		printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}


struct cgroup *myCgcm2 = cgroup_new_cgroup("a2");
struct cgroup_controller *myMemCtlcm2 = cgroup_add_controller(myCgcm2,"memory");
ret = cgroup_set_value_uint64(myMemCtlcm2,"memory.soft_limit_in_bytes",333333333);
ret = cgroup_create_cgroup(myCgcm2, 1);
	if (ret) {
		printf("FAIL: cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}







//=====================================aDDING blkio DETAILS====================
strcpy(string,"blkio");
ret = cgroup_get_subsys_mount_point(string, &mount_point);

struct cgroup *myCgcb1 = cgroup_new_cgroup("a1");
struct cgroup_controller *myMemCtlcb1 = cgroup_add_controller(myCgcb1,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcb1,"blkio.weight",1000);
ret = cgroup_create_cgroup(myCgcb1, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}



//=====================================a1/b0====================

struct cgroup *myCgcbb0 = cgroup_new_cgroup("a1/b0");
struct cgroup_controller *myMemCtlcbb0 = cgroup_add_controller(myCgcbb0,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcbb0,"blkio.weight",1000);
ret = cgroup_create_cgroup(myCgcbb0, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}



//=====================================a1/b1====================

struct cgroup *myCgcbb1 = cgroup_new_cgroup("a1/b1");
struct cgroup_controller *myMemCtlcbb1 = cgroup_add_controller(myCgcbb1,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcbb1,"blkio.weight",500);
ret = cgroup_create_cgroup(myCgcbb1, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}

//=====================================a1/b2====================

struct cgroup *myCgcbb2 = cgroup_new_cgroup("a1/b2");
struct cgroup_controller *myMemCtlcbb2 = cgroup_add_controller(myCgcbb2,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcbb2,"blkio.weight",250);
ret = cgroup_create_cgroup(myCgcbb2, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}


//=====================================a1/b3====================

struct cgroup *myCgcbb3 = cgroup_new_cgroup("a1/b3");
struct cgroup_controller *myMemCtlcbb3 = cgroup_add_controller(myCgcbb3,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcbb3,"blkio.weight",250);
ret = cgroup_create_cgroup(myCgcbb3, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}


//=====================================a2====================

struct cgroup *myCgcba2 = cgroup_new_cgroup("a2");
struct cgroup_controller *myMemCtlcba2 = cgroup_add_controller(myCgcba2,"blkio");
ret = cgroup_set_value_uint64(myMemCtlcba2,"blkio.weight",100);
ret = cgroup_create_cgroup(myCgcba2, 1);
	if (ret) {
		printf("FAIL: blkio.weight  cgroup_create_cgroup failed with %s\n", cgroup_strerror(ret));
printf("FAIL: c");
		exit(3);
	}








printf("Cgroup successfully created\n");
printf("Applcation PID are been added to different cgroup based on application type\n");




	while(1){
             //  printf("finish11111111111\n");
		FILE *file = fopen("ps_output.txt", "w");
		if(file!=NULL){
			command="ps -A> ps_output.txt";
			system(command); 
			fclose(file);
		}	
		file = fopen("ps_output.txt", "r");

		if(file!=NULL){	
			while (fgets(line, sizeof(line), file) != NULL) {
				token = strtok(line, " ");
				//printf("token: %s %ld\n",token,sizeof(token));
				pid = atoi( token );
				_pid1=pid;
				while (token != NULL)
				{
					process_command = token;
					token = strtok(NULL, " \t\n");      
				}	
			
				int i;
				for(i=0;i<dbnamecount;i++){
				
					substring =strstr(process_command,dbnames[i]);
					if(substring!=NULL)		
						dbfound= strcmp(dbnames[i],substring);
					if(dbfound==0){
						//printf("dbfound is : %d for process name : %s and pid % d\n",dbfound,process_command,pid);
								
						
						flag=1;
						dbfound=2;					
						break;
					}
                                     
				
				}
                            
     				if(flag==1)
				{                                        
				    //Logic for Instance caging
                                         
					
					if(a_a==4)
                                          {
                                             a_a=0;
 					
                                          }
				         if(a_a==0)
						{
                                               ret = cgroup_attach_task_pid(myCg, _pid1);
                                                ret = cgroup_attach_task_pid(myCgcbb0, _pid1);
                                              ret = cgroup_attach_task_pid(myCgcAl, _pid1);
                                         ret = cgroup_attach_task_pid(myCgcm1, _pid1);
						}
					 if(a_a==1)
						{
                            ret = cgroup_attach_task_pid(myCg1, _pid1);
				  ret = cgroup_attach_task_pid(myCgcbb1, _pid1);
ret = cgroup_attach_task_pid(myCgcAl, _pid1);
                                         ret = cgroup_attach_task_pid(myCgcm1, _pid1);
                                        
                           		}
					 if(a_a==2)
						{
                                ret = cgroup_attach_task_pid(myCg2, _pid1);
				  ret = cgroup_attach_task_pid(myCgcbb2, _pid1);
ret = cgroup_attach_task_pid(myCgcAl, _pid1);
                                         ret = cgroup_attach_task_pid(myCgcm1, _pid1);
                                        
                            		}
					 if(a_a==3)
						{
                              ret = cgroup_attach_task_pid(myCg3, _pid1);
				  ret = cgroup_attach_task_pid(myCgcbb3, _pid1);
ret = cgroup_attach_task_pid(myCgcAl, _pid1);
                                         ret = cgroup_attach_task_pid(myCgcm1, _pid1);
                                        

                            // printf("iafter icre1 %d",a_a);
						}
					
					
					a_a++;
						
				       flag=0; 
				}
				else
				{
                                         ret = cgroup_attach_task_pid(myCga2, _pid1);
                                         ret = cgroup_attach_task_pid(myCgca2, _pid1);
                                         ret = cgroup_attach_task_pid(myCgcm1, _pid1);
				         ret = cgroup_attach_task_pid(myCgcba2, _pid1);
                                        
					
					
					// printf("nnnnnnnnnnnnnnnnnnnnnnnnn found pid % d\n",pid);
					
				}
				sleep(0.01);

			
			
			}
			fclose(file);
		}

	}
	

return 0;
}
