#include<stdio.h>
int main(int argc, char *argv[]){
    FILE *fp;
    char filename[30], x[30];
    //filename = argv[1]; 
//    printf("filename %s\n", filename);
    if((fp=fopen(argv[1], "r+"))==NULL){
        exit(0);

    }
    fgets(x, 30, fp);
    printf("%s\n", x);
    fclose(fp);
    return 0;

}
