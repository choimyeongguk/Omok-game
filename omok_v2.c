#include <stdio.h>
#include <stdlib.h>

int check(int *board, int x, int y) ;
void prt_board(int* board) ;

const int n = 15 ;
const int line = 5 ;

int main()
{
    int i, j, k, x, y, turn=0 ;
    int* board ;
    board = (int*)malloc(sizeof(int)*(n*n)) ;

    /* 0으로 초기화 */
    for(i=0;i<n*n;i++)
    {
        board[i] = 0 ;
    }

    prt_board(board) ;

    /* play game */
    while(1)
    {
        if(turn==0)  // 검은돌 순서면
        {
            reput_b: printf("  black >> ") ;
            scanf("%d %d", &x, &y) ;  // 좌표 입력
            if(board[(y-1)*n+x-1]==1 || board[(y-1)*n+x-1]==2)  // 이미 놓은 돌 있는지 확인
            {
                printf("  already laid\n\n") ;
                goto reput_b ;  // 다시 반복
            }
            else
            {
                board[(y-1)*n+x-1] = 1 ;  // 돌 놓기
                prt_board(board) ;  // 결과 출력
                if(check(board, x-1, y-1)==1)
                {
                    printf("\n  BLACK WIN!!") ;
                    break ;
                }
                turn = 1 ;  // 순서 전환
            }
        }
        else
        {
            reput_w: printf("  white >> ") ;
            scanf("%d %d", &x, &y) ;
            if(board[(y-1)*n+x-1]==1 || board[(y-1)*n+x-1]==2)
            {
                printf("  already laid\n") ;
                goto reput_w ;
            }
            else
            {
                board[(y-1)*n+x-1] = 2 ;
                prt_board(board) ;
                if(check(board, x-1, y-1)==1)
                {
                    printf("  WHITE WIN!!") ;
                    break ;
                }
                turn = 0 ;
            }
        }

    }

    /* 저장공간 해제 */
    free(board) ;
    return 0 ;
}

int check(int* board, int x, int y)
{
    int blockage = 0 ;  // 0 - 안막힘, 1 - 막힘
    int stack, i, r, l ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 가로 방향
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+i)==*(board+n*y+x))
            {
                stack++ ;
            } else r=1 ;
            if(l==0 && *(board+n*y+x-i)==*(board+n*y+x))
            {
                stack++ ;
            } else l=1 ;
        }
    }
    printf("  horizontal stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 세로 방향
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+n*i)==*(board+n*y+x))
            {
                stack++ ;
            } else r=1 ;
            if(l==0 && *(board+n*y+x-n*i)==*(board+n*y+x))
            {
                stack++ ;
            } else l=1 ;
        }
    }
    printf("  vertical stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 대각선 양 방향
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x-n*i+i)==*(board+n*y+x))
            {
                stack++ ;
            } else r=1 ;
            if(l==0 && *(board+n*y+x+n*i-i)==*(board+n*y+x))
            {
                stack++ ;
            } else l=1 ;
        }
    }
    printf("  positive diagonal stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 대각선 음 방향
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x-n*i-i)==*(board+n*y+x))
            {
                stack++ ;
            } else r=1 ;
            if(l==0 && *(board+n*y+x+n*i+i)==*(board+n*y+x))
            {
                stack++ ;
            } else l=1 ;
        }
    }
    printf("  negative diagonal stack : %d\n\n", stack) ;
    if(stack>line-1) goto gameover ;
    else return 0 ;

    gameover: return 1 ;
}

/* 바둑판 출력 함수 */
void prt_board(int* board)
{
    int i, j, k ;

    printf("\n      ") ;
    for(i=0;i<n;i++)
    {
        if(i+1>9) printf("%d  ", i+1) ;
        else printf("%d   ", i+1) ;
    }
    printf("\n") ;

    for(i=0;i<n;i++)  // y좌표
    {
        printf("     ") ;
        for(k=0;k<n*4-1;k++) printf("-") ;
        if(i+1>9) printf("\n %d |", i+1) ;
        else printf("\n %d  |", i+1) ;
        for(j=0;j<n;j++)  // x좌표
        {
            if(*(board+i*n+j)==0)
            {
                printf("   |", *(board+i*n+j)) ;
            }
            else if(*(board+i*n+j)==1)
            {
                printf(" @ |") ;
            }
            else
            {
                printf(" O |", *(board+i*n+j)) ;
            }
        }
        printf("\n") ;
    }
    printf("     ") ;
    for(i=0;i<n*4-1;i++) printf("-") ;
    printf("\n\n") ;
}
