#include <stdio.h>
#define line 5

int check(int* board, int n, int x, int y) ;
void prt_board(int* board, int n) ;

int main()
{
    int i, j, k, x, y, n, turn=0, turnNum=0 ;

    printf("  choose board size (9x9 or 15x15) : ") ;
    scanf("%d", &n) ;
    int board[n][n] ;
    for(i=0;i<n;i++) for(j=0;j<n;j++) board[i][j] = 0 ;

    prt_board(board, n) ;

    /* play game */
    while(turnNum<=n*n)
    {
        if(turn==0)  // ������ ������
        {
            turnNum++ ;
            reput_b: printf("  black >> ") ;
            scanf("%x %x", &x, &y) ;  // ��ǥ �Է�
            x-- ; y-- ; // 1���� ���� -> 0���� ����
            if(0<=x<=n && 0<=y<=n)
            {
                if(board[y][x]==1 || board[y][x]==2)  // �̹� ���� �� �ִ��� Ȯ��
                {
                    printf("  already laid\n\n") ;
                    goto reput_b ;  // �ٽ� �ݺ�
                }
                else
                {
                    board[y][x] = 1 ;  // �� ����
                    prt_board(board, n) ;  // ��� ���
                    if(check(board, n, x, y)==1)
                    {
                        printf("\n  BLACK WIN!!") ;
                        break ;
                    }
                    turn = 1 ;  // ���� ��ȯ
                }
            }
            else
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_b ;
            }
        }
        else
        {
            turnNum++ ;
            reput_w: printf("  white >> ") ;
            scanf("%x %x", &x, &y) ;
            x-- ; y-- ;
            if(0<=x<=n && 0<=y<=n)
            {
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
                        printf("  WHITE WIN!!") ;
                        break ;
                    }
                    turn = 0 ;
                }
            }
            else
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_w ;
            }
        }

    }

    return 0 ;
}

int check(int* board, int n, int x, int y)
{
    int blockage = 0 ;  // 0 - �ȸ���, 1 - ����
    int stack, i, r, l ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ���� ����
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
    printf("  horizontal stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ���� ����
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
    printf("  vertical stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // �밢�� �� ����
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
    printf("  positive diagonal stack : %d\n", stack) ;
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // �밢�� �� ����
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
    printf("  negative diagonal stack : %d\n\n", stack) ;
    if(stack>line-1) goto gameover ;
    else return 0 ;

    gameover: return 1 ;
}

/* �ٵ��� ��� �Լ� */
void prt_board(int* board, int n)
{
    int i, j, k ;

    printf("\n     ") ;
    for(i=1;i<n+1;i++) printf("%x   ", i) ;
    printf("\n") ;

    for(i=0;i<n;i++)  // y��ǥ
    {
        printf("    ") ;
        for(j=0;j<n*4-1;j++) printf("-") ;
        printf("\n %x |", i+1) ;
        for(j=0;j<n;j++)  // x��ǥ
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