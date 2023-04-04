#include <stdio.h>
#include <cgraph.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int i, j, k = 0, r = 0;
    char str[256];
    FILE *fp = fopen("C:/Users/mihan/OneDrive/Рабочий стол/Flita2/matrix_of_incendence188.txt", "r");
    while(fgets(str, 256, fp) != NULL){
        r++;
    }
    fclose(fp);
    FILE *file = fopen("C:/Users/mihan/OneDrive/Рабочий стол/Flita2/matrix_of_incendence188.txt", "r");
    int matrix_inc[r][strlen(str)/2 + strlen(str)%2];
    int m[strlen(str)/2 + strlen(str)%2][r+1];
    while(fgets(str, 256, file) != NULL){
        i = 0;
        for(j = 0; j < strlen(str)/2 + strlen(str)%2; j++){
            matrix_inc[k][j]=(int)str[i] % 2;
            i+=2;
            m[j][r] = 0;
        }
        k+=1;
    }
    fclose(file);
    for(i = 0; i < k; i++){
        for(j = 0; j < strlen(str)/2 + strlen(str)%2; j++){
            m[j][i]=matrix_inc[i][j];
            m[j][k]+=matrix_inc[i][j];
        }
    }
    FILE * fo;
    fo = fopen("g.dot","wt");
    fprintf( fo, "digraph Graf {\n");
    fprintf( fo, "  edge [dir=\"both\"] \n");
    for(i = 0; i < k; i++){
        int sum = 0;
        for(j = 0; j < strlen(str)/2 + strlen(str)%2; j++){
            sum+=matrix_inc[i][j];
        }
        if(sum==0){
            fprintf( fo, " A%d\n", i+1);
        }
    }
    int x1, x2;
    for(j = 0; j < strlen(str)/2 + strlen(str)%2; j++){
        if(m[j][k] == 2){
            x1 = -1;
            x2 = -1;
            for(int i1 = 0; i1 < k; i1++){
                if(m[j][i1] == 1 && x1 == -1){
                    x1 = i1;
                }
                else if(m[j][i1] == 1 && x1 != -1 && x1 != i1){
                    x2 = i1;
                }
            }
            if(x1 != -1 && x2!=-1){
                //printf("%d %d ",x1+1,x2+1);
                fprintf( fo, " A%d", x1+1);
                fprintf( fo, "->");
                fprintf( fo, "A%d \n", x2+1);
            }
        }
        if(m[j][k] == 1){
            x1 = -1;
            for(int i2 = 0; i2 < k; i2++) {
                if(m[j][i2] == 1 && x1 == -1){
                    x1 = i2;
                    //printf("%d", i2+1);
                }
            }
            if(x1 != -1){
                fprintf( fo, " A%d", x1+1);
                fprintf( fo, "->");
                fprintf( fo, "A%d \n", x1+1);
            }
        }
    }
    fprintf( fo, "}");
    fclose(fo);
    system("dot g.dot -Tpng -og.png");
    return 0;
}
