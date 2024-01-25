#include <stdio.h>
#define line 5

int check(int* board, int n, int x, int y) ;  // �¸� Ȯ�� �Լ� 
void prt_board(int* board, int n) ;  // ������ ��� �Լ� 

int main()
{
    int i, j, k ;  // for�� ���� 
		int n, x, y ; // ������ ũ��, x��ǥ(��), y��ǥ(��) 
		int turn=0, turnNum=0, result ;  // ��/�� ����, ��, ��� 

		/* ������ ũ�� ���� */ 
    setting_board: printf("  ������ ũ�⸦ ���ϼ���(9x9 ~ 15x15) : ") ;
    scanf("%d", &n) ;
    if(n<9)
    {
        printf("  �������� ũ��� �ּ� 9x9�̻��̾�� �մϴ�.\n\n") ;
        goto setting_board ;  // ������ ũ�� ���Է� 
    }
    else if(n>15)
    {
    	printf("  �������� ũ��� �ִ� 15x15���Ͽ��� �մϴ�.\n\n") ;
    	goto setting_board ;
		}
    int board[n][n] ;  // ���� �� �迭 ����
		int log[n][2] ;  // ��� ������ ����ϴ� �α� �迭 ���� 
    for(i=0;i<n;i++) for(j=0;j<n;j++) board[i][j] = 0 ;  // ������ �迭 0���� �ʱ�ȭ
    for(i=0;i<n;i++) { log[i][0] = 0 ; log[i][1] = 0 ; }  // �α� �迭 0���� �ʱ�ȭ 

    prt_board(board, n) ;  // ������ ���. [][]�� �Է����� �������μ� board�迭�� �ּҸ� �Ű������� ����
    printf("  << ���۹� : ���� ���� ��, [ x��ǥ(��) y��ǥ(��) ] ���·� �Է�. >>\n\n") ;

    /* play game */
    while(turnNum<n*n)  // ���� Ƚ���� ������ ũ�⺸�� �۰ų� ���� �� ���� 
    {
        if(turn==0)  // ������ ����
        {
            reput_b: printf("  black >> ") ;
            scanf("%x %x", &x, &y) ;  // ��ǥ �Է�. ���� ���� [��] [��]���� �Է�
            log[turnNum][0] = x ;  // x��ǥ(��) ��� 
						log[turnNum][1] = y ;  // y��ǥ(��) ��� 
            x-- ; y-- ; // 1���� ���� -> 0���� ����. ����� ����
						turnNum++ ;  // ���� Ƚ�� +1 
            
            if(x<0 || x>n || y<0 || y>n)  // �߸��� �Է� 
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_b ;  // ��ǥ ���Է� 
            }
            else if(board[y][x]==1 || board[y][x]==2)  // y��x���� �̹� ���� �� �ִ��� Ȯ��
            {
                printf("  already laid\n\n") ;
                goto reput_b ;  // ��ǥ ���Է� 
            }
            else
            {
                board[y][x] = 1 ;  // �� ����
                prt_board(board, n) ;  // ��� ���
                if(check(board, n, x, y)==1)
                {
                    printf("  [ BLACK WIN!! ]") ;
                    result = 0 ; 
                    break ;
                }
                turn = 1 ;  // ���� ��ȯ 
            }
        }
        else  // �� ���� 
        {

            reput_w: printf("  white >> ") ;
            scanf("%x %x", &x, &y) ;
            log[turnNum][0] = x ; 
						log[turnNum][1] = y ;
            x-- ; y-- ;
            turnNum++ ;
            
            if(x<0 || x>n || y<0 || y>n)
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_w ;
            }
          	else if(board[y][x]==1 || board[y][x]==2)
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
                    result = 1 ;
                    break ;
                }
                turn = 0 ;
            }
        }
    }
    if(turnNum==n*n) { printf("  [ TIE ]\n\n") ; result = 2 ; }  // ���º�
    
    
    /* ���� ��� ���� */ 
    FILE* fp = fopen("omok_log.txt","a");  // txt ���� ���� 
    
    fprintf(fp, "------------------------------\n") ;
    fprintf(fp, "������ ũ�� : %dx%d\n\n", n, n) ;
    for(i=0;i<turnNum;i++)
    {
    	if(i%2==0) fprintf(fp, "�� - ") ;
    	else fprintf(fp, "�� - ") ;
    	fprintf(fp, "%d  %d\n", log[i][0], log[i][1]) ;  // ��ǥ ��� 
		}
		switch(result)  // ���� ��� ��� 
		{
			case 0: fprintf(fp, "\nBLACK WIN\n") ; break ;
			case 1: fprintf(fp, "\nWHITE WIN\n") ; break ;
			case 2: fprintf(fp, "\nTIE\n") ; break ;
		}
		fprintf(fp, "------------------------------\n\n\n") ;
    fclose(fp);  // ���� �۾� ��ħ 
    printf("\n  �뱹 �αװ� ����Ǿ����ϴ�.");

    return 0 ;
}


/******************
 * �¸� Ȯ�� �Լ� * 
 ******************/ 
int check(int* board, int n, int x, int y)
{
    int blockage = 0 ;  // 0 - �ȸ���, 1 - ����
    int stack, i, r, l ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ���� ����
    {
        if(r==1 && l==1)  // ���� �� ������ �� 
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+i)==*(board+n*y+x))  // ���������� ���������� i��ŭ ������ ĭ�� ��
            {
                stack++ ;  // �̾��� ���� +1 
            } else r = 1 ;  // �ƴ϶�� r�� ����ó��. ���ķ� i�� �þ�� ī��Ʈ ���� 
            if(l==0 && *(board+n*y+x-i)==*(board+n*y+x))  // ���������� ��������  i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else l = 1 ; 
        }
    }
    if(stack>line-1) goto gameover ;  // �¸� ���� ���� ��, ���� ���� �ڵ�� �̵� 

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ���� ����
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+n*i)==*(board+n*y+x))  // ���������� �Ʒ��� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i)==*(board+n*y+x))  // ���������� ���� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ������ ���� ���� �밢��
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x-n*i+i)==*(board+n*y+x))  // ���������� ���� i, ���������� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x+n*i-i)==*(board+n*y+x))  // ���������� �Ʒ��� i, �������� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // ���� ���� ���� �밢�� 
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+n*i+i)==*(board+n*y+x))  // ���������� �Ʒ��� i, ���������� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i-i)==*(board+n*y+x))  // ���������� ���� i, �������� i��ŭ ������ ĭ�� �� 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;
    
		return 0 ;  // ���� ���� 
    gameover: return 1 ;  // �¸� 
}


/*********************
 *	������ ��� �Լ� * 
 *********************/
void prt_board(int* board, int n)  // �Ű������� ������(�ּ�)�� ���� 
{
    int i, j, k ;

    printf("\n     ") ;
    for(i=1;i<n+1;i++) printf("%x   ", i) ;  // 10 �̻��� ���� ǥ���ϱ� ���� 16���� ��� 
    printf("\n") ;

    for(i=0;i<n;i++)  // �� 
    {
        printf("    ") ;
        for(j=0;j<n;j++) printf("--- ") ;
        printf("\n %x |", i+1) ;
        for(j=0;j<n;j++)  // �� 
        {
            if(*(board+i*n+j)==0)  // 2���� �迭 �ּ� ���� �̿�. i�� j�� 
            {
                printf("   |") ;  // ��ĭ 
            }
            else if(*(board+i*n+j)==1)
            {
                printf(" @ |") ;  // ���� �� 
            }
            else
            {
                printf(" O |") ;  // �� �� 
            }
        }
        printf("\n") ;
    }
    printf("    ") ;
    for(i=0;i<n;i++) printf("--- ") ;
    printf("\n\n") ;
}
