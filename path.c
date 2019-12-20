/* Author : Youssef Dahab
File name: path.c */

#include <stdio.h>

#define A_ij A[i * m + j]
#define A_kl A[k * m + l]

#define UP A[(i - 1) * m + j]
#define DOWN A[(i + 1) * m + j]
#define LEFT A[i * m + (j - 1)]
#define RIGHT A[i * m + (j + 1)]


int L = 1;                      /*L is the path length*/
int a = 0;                      /*path array counter*/
int one_time = 1, check = 0;
int cell_jumps = 0;             /*1 less than the path length*/

int find_path(int n, int m, int A[], int i, int j, int k, int l, int path[][2])
{   
    /*range checking*/ 
    if (A_ij == 1 || A_kl == 1) return -1;
    if (i < 0 || i >= n) return -2;
    if (j < 0 || j >= m) return -3; 


    if (one_time == 1)
    {
        one_time += 1;

        path[0][0] = i; path[0][1] = j;
        if (i == k && j == l) return L = 1;
    }

    /*traverse, store in path, mark visited position as -1*/
    
    if (j != m - 1 && RIGHT == 0)
    {
        A_ij = -1; j += 1; a += 1;   

        path[a][0] = i;
        path[a][1] = j;  
        
        L += 1; cell_jumps += 1; check = 0;
    } 
    else check += 1;



    if (i != n - 1 && DOWN == 0)
    {
        A_ij = -1; i += 1; a += 1;
        
        path[a][0] = i;
        path[a][1] = j;  
        
        L += 1; cell_jumps += 1; check = 0;
    } 
    else check += 1;



    if (j != 0 && LEFT == 0)
    {
        A_ij = -1; j -= 1; a += 1;
        
        path[a][0] = i;
        path[a][1] = j;  
        
        L += 1; cell_jumps += 1; check = 0;
    }
    else check += 1;



    if (i != 0 && UP == 0)
    {
        A_ij = -1; i -= 1; a += 1;
        
        path[a][0] = i;
        path[a][1] = j;  
        
        L += 1; cell_jumps += 1; check = 0;

    }
    else check += 1; 


    /*go back 1 position (to look for other paths) if all 4 directions have been checked and no path was found 
    - maybe wrong path was taken*/
    if (check > 3)
    {
        A_ij = -1; a -= 1;
        
        i = path[a][0];
        j = path[a][1];
        
        L -= 1;


        /*revert changes in A - input array same as output*/
        if (cell_jumps == 0)
        {
            for (a = 0; a < n * m; a++) if (A[a] == -1) A[a] = 0;
            return 0;
        }
        else cell_jumps -= 1;
    }   


    if (i != k || j != l) 
    {
        find_path(n, m, A, i, j, k, l, path);
        for (a = 0; a < n * m; a++) if (A[a] == -1) A[a] = 0;
        return L;
    }

    return L;
}

int main(void)
{   
    int path[50][2];

    int A[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    
    int path_length = find_path(3, 3, A, 0, 0, 0, 0, path);

    //print the path
    for (int c = 0; c < path_length; c++)     // c < path_length
    {
        for (int d = 0; d < 2; d++)   //m is 4 & -2 so it prints 2 columns
        {
            printf("%d  ", path[c][d]);
        }
        printf("\n");
    }
    printf("path_length = %d\n", path_length);
}
