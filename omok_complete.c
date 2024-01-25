#include <stdio.h>
#define line 5

int check(int* board, int n, int x, int y) ;  // 승리 확인 함수 
void prt_board(int* board, int n) ;  // 오목판 출력 함수 

int main()
{
    int i, j, k ;  // for문 변수 
		int n, x, y ; // 오목판 크기, x좌표(열), y좌표(행) 
		int turn=0, turnNum=0, result ;  // 흑/백 차례, 수, 결과 

		/* 오목판 크기 설정 */ 
    setting_board: printf("  오목판 크기를 정하세요(9x9 ~ 15x15) : ") ;
    scanf("%d", &n) ;
    if(n<9)
    {
        printf("  오목판의 크기는 최소 9x9이상이어야 합니다.\n\n") ;
        goto setting_board ;  // 오목판 크기 재입력 
    }
    else if(n>15)
    {
    	printf("  오목판의 크기는 최대 15x15이하여야 합니다.\n\n") ;
    	goto setting_board ;
		}
    int board[n][n] ;  // 오목 판 배열 선언
		int log[n][2] ;  // 경기 진행을 기록하는 로그 배열 선언 
    for(i=0;i<n;i++) for(j=0;j<n;j++) board[i][j] = 0 ;  // 오목판 배열 0으로 초기화
    for(i=0;i<n;i++) { log[i][0] = 0 ; log[i][1] = 0 ; }  // 로그 배열 0으로 초기화 

    prt_board(board, n) ;  // 오목판 출력. [][]를 입력하지 않음으로서 board배열의 주소를 매개변수로 넣음
    printf("  << 조작법 : 돌을 놓을 때, [ x좌표(열) y좌표(행) ] 형태로 입력. >>\n\n") ;

    /* play game */
    while(turnNum<n*n)  // 진행 횟수가 오목판 크기보다 작거나 같을 때 실행 
    {
        if(turn==0)  // 검은돌 순서
        {
            reput_b: printf("  black >> ") ;
            scanf("%x %x", &x, &y) ;  // 좌표 입력. 편의 위해 [열] [행]으로 입력
            log[turnNum][0] = x ;  // x좌표(열) 기록 
						log[turnNum][1] = y ;  // y좌표(행) 기록 
            x-- ; y-- ; // 1부터 시작 -> 0부터 시작. 사용자 편의
						turnNum++ ;  // 진행 횟수 +1 
            
            if(x<0 || x>n || y<0 || y>n)  // 잘못된 입력 
            {
                printf("  wrong coordinate\n\n") ;
                goto reput_b ;  // 좌표 재입력 
            }
            else if(board[y][x]==1 || board[y][x]==2)  // y행x열에 이미 놓은 돌 있는지 확인
            {
                printf("  already laid\n\n") ;
                goto reput_b ;  // 좌표 재입력 
            }
            else
            {
                board[y][x] = 1 ;  // 돌 놓기
                prt_board(board, n) ;  // 결과 출력
                if(check(board, n, x, y)==1)
                {
                    printf("  [ BLACK WIN!! ]") ;
                    result = 0 ; 
                    break ;
                }
                turn = 1 ;  // 순서 전환 
            }
        }
        else  // 흰돌 순서 
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
    if(turnNum==n*n) { printf("  [ TIE ]\n\n") ; result = 2 ; }  // 무승부
    
    
    /* 게임 기록 저장 */ 
    FILE* fp = fopen("omok_log.txt","a");  // txt 파일 생성 
    
    fprintf(fp, "------------------------------\n") ;
    fprintf(fp, "오목판 크기 : %dx%d\n\n", n, n) ;
    for(i=0;i<turnNum;i++)
    {
    	if(i%2==0) fprintf(fp, "흑 - ") ;
    	else fprintf(fp, "백 - ") ;
    	fprintf(fp, "%d  %d\n", log[i][0], log[i][1]) ;  // 좌표 출력 
		}
		switch(result)  // 게임 결과 출력 
		{
			case 0: fprintf(fp, "\nBLACK WIN\n") ; break ;
			case 1: fprintf(fp, "\nWHITE WIN\n") ; break ;
			case 2: fprintf(fp, "\nTIE\n") ; break ;
		}
		fprintf(fp, "------------------------------\n\n\n") ;
    fclose(fp);  // 파일 작업 마침 
    printf("\n  대국 로그가 저장되었습니다.");

    return 0 ;
}


/******************
 * 승리 확인 함수 * 
 ******************/ 
int check(int* board, int n, int x, int y)
{
    int blockage = 0 ;  // 0 - 안막힘, 1 - 막힘
    int stack, i, r, l ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 가로 방향
    {
        if(r==1 && l==1)  // 양쪽 다 막혔을 때 
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+i)==*(board+n*y+x))  // 기준점에서 오른쪽으로 i만큼 움직인 칸의 값
            {
                stack++ ;  // 이어진 개수 +1 
            } else r = 1 ;  // 아니라면 r을 막힘처리. 이후로 i가 늘어나도 카운트 안함 
            if(l==0 && *(board+n*y+x-i)==*(board+n*y+x))  // 기준점에서 왼쪽으로  i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else l = 1 ; 
        }
    }
    if(stack>line-1) goto gameover ;  // 승리 조건 만족 시, 게임 종료 코드로 이동 

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 세로 방향
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+n*i)==*(board+n*y+x))  // 기준점에서 아래로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i)==*(board+n*y+x))  // 기준점에서 위로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 오른쪽 위로 가는 대각선
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x-n*i+i)==*(board+n*y+x))  // 기준점에서 위로 i, 오른쪽으로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x+n*i-i)==*(board+n*y+x))  // 기준점에서 아래로 i, 왼쪽으로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;

    stack=1 ; r=0 ; l=0 ;
    for(i=1;i<line+1;i++)  // 왼쪽 위로 가는 대각선 
    {
        if(r==1 && l==1)
        {
            break ;
        }
        else
        {
            if(r==0 && *(board+n*y+x+n*i+i)==*(board+n*y+x))  // 기준점에서 아래로 i, 오른쪽으로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else r = 1 ;
            if(l==0 && *(board+n*y+x-n*i-i)==*(board+n*y+x))  // 기준점에서 위로 i, 왼쪽으로 i만큼 움직인 칸의 값 
            {
                stack++ ;
            } else l = 1 ;
        }
    }
    if(stack>line-1) goto gameover ;
    
		return 0 ;  // 게임 지속 
    gameover: return 1 ;  // 승리 
}


/*********************
 *	오목판 출력 함수 * 
 *********************/
void prt_board(int* board, int n)  // 매개변수로 포인터(주소)를 받음 
{
    int i, j, k ;

    printf("\n     ") ;
    for(i=1;i<n+1;i++) printf("%x   ", i) ;  // 10 이상의 수를 표현하기 위해 16진법 사용 
    printf("\n") ;

    for(i=0;i<n;i++)  // 행 
    {
        printf("    ") ;
        for(j=0;j<n;j++) printf("--- ") ;
        printf("\n %x |", i+1) ;
        for(j=0;j<n;j++)  // 열 
        {
            if(*(board+i*n+j)==0)  // 2차원 배열 주소 계산식 이용. i행 j열 
            {
                printf("   |") ;  // 빈칸 
            }
            else if(*(board+i*n+j)==1)
            {
                printf(" @ |") ;  // 검은 돌 
            }
            else
            {
                printf(" O |") ;  // 흰 돌 
            }
        }
        printf("\n") ;
    }
    printf("    ") ;
    for(i=0;i<n;i++) printf("--- ") ;
    printf("\n\n") ;
}
