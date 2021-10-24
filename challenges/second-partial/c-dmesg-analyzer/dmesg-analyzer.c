#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define REPORT_FILE "report.txt"

#define HASH_SIZE 4000

void analizeLog(char *logFile, char *report);
unsigned hash(char *key);
void insert(char *key, char *log);

struct logData {
    char *data[HASH_SIZE];
    char *key;
};

struct logData *hashArray[HASH_SIZE];

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage:./dmesg-analizer logfile.txt\n");
        return 1;
    }

    analizeLog(argv[1], REPORT_FILE);
    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    hashArray[HASH_SIZE] = (struct logData*) malloc(sizeof(struct logData));
    
    FILE *fp;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(logFile,"r");

    if (fp  == NULL){
		return;
	}

    while ((read = getline(&line, &len, fp)) != -1) {
		if(strcmp("\n", line) != 0){
            int time, pos, start, len;
            time = pos = start = len = 0;
            
            if(line[pos] == '['){
                while(line[pos] != ']'){
                    pos++;
                    time++;
                }

                pos += 2;
                time += 1;
                start = pos;
                
                while(':' != line[pos] && pos < strlen(line)){
                    pos++;
                    len++;
                }

                char log[len];
                char timeArr[time];
                
                //Check if the log string was found or not
                if(pos != strlen(line)){
                    strncpy(log, line + start, len);
                    strncpy(timeArr, line, time);
                    log[len] = '\0';
                    timeArr[time] = '\0';

                    char msg[strlen(line) - len - time];
                    msg[strlen(line) - len - time] = '\0';
                    strncpy(msg, line + pos + 1, strlen(line) - len - time);

                    char logMsg[strlen(line) - len + 1];
                    strcpy(logMsg, timeArr);
                    strcat(logMsg, msg);
                    logMsg[strlen(line) - len + 1] = '\0';
                    insert(log, logMsg);
      
                }else{
                    strncpy(timeArr, line, time);
                    timeArr[time] = '\0';

                    char msg[strlen(line) - time];
                    strncpy(msg, line + time, strlen(line) - time);
                    msg[strlen(line) - time] = '\0';

                    char logMsg[strlen(line)];
                    strcpy(logMsg, timeArr);
                    strcat(logMsg, msg);
                    logMsg[strlen(line)] = '\0';   

                    insert("General", logMsg);
                }               
            }
		}
    }
    
    int i = 0;
    FILE *rep;
    rep = fopen(REPORT_FILE, "w+");

    for(i = 0; i < HASH_SIZE; i++) {
        if(hashArray[i] != NULL){
            fprintf(rep,"%s:\n",hashArray[i]->key );
            for(int j = 0; j < HASH_SIZE; j ++ ){
                if(hashArray[i]->data[j] !=NULL ){
                    fprintf(rep, "\t%s",  hashArray[i]->data[j]);
                }
            } 
        }
    }


    int fd;
    fd=open(REPORT_FILE,O_RDWR);
    if (fd != -1)
    {
        write(1,"Report is generated at: ", sizeof("Report is generated at: "));
        printf("[%s]\n", REPORT_FILE);
        close(fd);
    }
}

unsigned hash(char *key){
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++){
        hashval = *key + 31 *hashval;
        return  hashval % HASH_SIZE;
    }
}


void insert(char* key, char* log) {
    struct logData *item = (struct logData*) malloc(sizeof(struct logData));
    int index = hash(key);
    int i = 0;
    
    while(hashArray[index] != NULL) {
        if(strcmp(hashArray[index]->key, key) == 0){
            while(hashArray[index]->data[i] != NULL) i++;
            hashArray[index]->data[i] = malloc (sizeof(char) * strlen(log));
            strncpy(hashArray[index]->data[i], log, strlen(log));
            return;
        }
      ++index;
      index %= HASH_SIZE;
    }

    item->key = malloc (sizeof(char) * strlen(key));
    strncpy(item->key, key, strlen(key));
    item->data[0] =  malloc (sizeof(char) * strlen(log));
    strncpy(item->data[0], log, strlen(log));
    hashArray[index] = item;
}