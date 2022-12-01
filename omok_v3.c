#include <stdio.h>
#define line 5

int check(int* board, int n, int x, int y) ;
void prt_board(int* board, int n) ;

int main()
{
    int i, j, k, x, y, n, turn=0, turnNum=0 ;

    reput_board: printf("  choose board size (9x9 ~ 15x15) : ") ;
    scanf("%d", &n) ;
    if(n<9)
    {
        printf("  The board size must be at least 9x9\n") ;
        goto reput_board ;
    }
    int board[n][n] ;
    for(i=0;i<n;i++) for(j=0;j<n;j++) board[i][j] = 0 ;

    prt_board(board, n) ;

    /* play game */
    while(turnNum<n*n)
    {
        if(turn==0)  // 검은돌 순서면
        {
            turnNum++ ;
            reput_b: printf("  black >> ") ;
            scanf("%x %x", &x, &y) ;  // 좌표 입력
            x-- ; y-- ; // 1부터 시작 -> 0부터 시작
            if(x<0 || x>n || y<0 || y>n)
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_b ;
            }
            if(board[y][x]==1 || board[y][x]==2)  // 이미 놓은 돌 있는지 확인
            {
                printf("  already laid\n\n") ;
                goto reput_b ;  // 다시 반복
            }
            else
            {
                board[y][x] = 1 ;  // 돌 놓기
                prt_board(board, n) ;  // 결과 출력
                if(check(board, n, x, y)==1)
                {
                    printf("\n  [ BLACK WIN!! ]") ;
                    break ;
                }
                turn = 1 ;  // 순서 전환
            }
        }
        else
        {
            turnNum++ ;
            reput_w: printf("  white >> ") ;
            scanf("%x %x", &x, &y) ;
            x-- ; y-- ;
            if(x<0 || x>n || y<0 || y>n)
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_w ;
            }
            if(board[y][x]==1 || board[y][x]==2)
            {
                printf("  already laid\n\n") ;
                goto reput_w ;
            }
            else
            {
                board[y][x] = 2 ;
                prt_board(board, n) ;
                if(check(board, n, x, y)==1)
                {
                    printf("  [ WHITE WIN!! ]") ;
                    break ;
                }
                turn = 0 ;
            }
        }
    }
    if(turnNum==n*n) printf("  [ TIE ]\n") ;

    return 0 ;
}

int check(int* board, int n, int x, int y)
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
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-i)==*(board+n*y+x))
            {
                stack++ ;
            } else l = 1 ;
        }
    }
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
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i)==*(board+n*y+x))
            {
                stack++ ;
            } else l = 1 ;
        }
    }
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
            } else r = 1 ;
            if(l==0 && *(board+n*y+x+n*i-i)==*(board+n*y+x))
            {
                stack++ ;
            } else l = 1 ;
        }
    }
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
            if(r==0 && *(board+n*y+x+n*i+i)==*(board+n*y+x))
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i-i)==*(board+n*y+x))
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;
    else return 0 ;

    gameover: return 1 ;
}

/* 바둑판 출력 함수 */
void prt_board(int* board, int n)
{
    int i, j, k ;

    printf("\n     ") ;
    for(i=1;i<n+1;i++) printf("%x   ", i) ;
    printf("\n") ;

    for(i=0;i<n;i++)  // y좌표
    {
        printf("    ") ;
        for(j=0;j<n;j++) printf("--- ") ;
        printf("\n %x |", i+1) ;
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
    printf("    ") ;
    for(i=0;i<n;i++) printf("--- ") ;
    printf("\n\n") ;
}
