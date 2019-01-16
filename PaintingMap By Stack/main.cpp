/**
@file main.cpp

@date 2018/04/24

@author 김규태 ( gyutae100@gmail.com )

@version 1.0    
*/

/**
	\defgroup Painting
	@brief 페인팅 연관 모듈

	\defgroup InputOutput
	@brief I/O 연관 모듈
*/


#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "lib_io.h"
#include "COLOR_TYPE.h"

#include "lib_template_linked_stack.h"

using namespace std;

#define FPS 2000 ///<맵 랜더링 시간

/**
@struct Point

@brief 색상의 좌표 구조체
*/
typedef struct Point{

	int y;
	int x;
}Point;

char g_target_color = '\0';	 //*<변경 할 특정 색상 값  
char g_change_color = '\0';  //*<바꿀 색상 색 값

int g_columns = 0;			 //*<총 행 
int g_rows = 0;				 //*<총 열

void DisplayInsideStack(TemplateLinkedStack<Point> *stack); ///<스택 내부 정보 출력한다.

void main(void)
{

	//페인트 맵 총 행, 열
	int columns = 0;	
	int rows = 0;		

	//*색상 행렬 파일 열기.
	FILE * stream = freopen("map2.txt", "r", stdin);  

	//*총 열, 행 갯수 저장한다.
	scanf("%d", &rows);		
	scanf("%d", &columns);	

	//전역 총 열, 행 갯수 저장한다.
	g_columns = columns;
	g_rows = rows;

	//텍스트 파일 1행 열, 행 읽은 후 바로 다음 문자인 개행 문자는 읽고 바로 버린다.
	char temp = NULL;	
	scanf("%c", &temp);

	//원본 멥 
	char  ** original_map = NULL;

	//출력 맵
	char ** current_map = NULL;

	//------------------------------------------------------------------------------
	//	방문 체크용 맵
	//	
	//	:방문시 해당 좌표 요소 true
	//	:미방문시 해당 좌표 요소 false
	//------------------------------------------------------------------------------
	char ** visited_map = NULL;

	//------------------------------------------------------------------------------
	//*작업에 필요한 모든 이중 동적 배열 메모리 할당한다.
	//------------------------------------------------------------------------------
	if ( ! InitTwoDimensionalArray( &original_map, columns, rows ) ){
		
		///@todo 할당 실패 예외처리가 필요하다.
		return;
	}
	if ( ! InitTwoDimensionalArray( &current_map, columns, rows ) ){
		
		///@see 할당 실패 예외처리가 필요하다.
		return;
	}
	if ( ! InitTwoDimensionalArray( &visited_map, columns, rows ) ){

		///@todo 할당 실패 예외처리가 필요하다.
		return;
	}

	//*original_map 색상 행렬 초기화한다.
	for (int ic = 0; ic < columns; ic++){

		for (int jr = 0; jr < rows; jr++){

			scanf("%c", &original_map[ic][jr]);
			
			//아스키 문자를 숫자화한다.
			original_map[ic][jr] = original_map[ic][jr] - '0'; 
		}

		//각 열의 마지막에 존재하는 개행 문자를 읽은 후 버린다.
		scanf("%c", &temp); 	
	}

	//*파일 읽기 완료한다.
	fclose(stream);

	//*	visited_map 초기화한다.
	for (int ic = 0; ic < columns; ic++){

		memset(visited_map[ic], false, rows);
	}

	//*current_map에 original_map 복사한다.
	///@todo 나중에 memcpy로 대체 할 것.
	if (! CopyTwoDimensionalArray(original_map, current_map, columns, rows)){

		//TODO 복사 실패에 대한 예외처리가 필요하다.
		return;
	}

	//*스텍 생성
	TemplateLinkedStack<Point> Stack;

	//위치 구조체
	Point start_point; //시작 위치
	Point next_point;  //다음 이동 위치
	Point now_point;   //현재 위치


	//---------------------------------------------------------------------
	/*선택한 특정 색상 범위를 선택 색상 범위로 변경한다.\n
	페인팅 맵 변경 과정, 통계 정보 출력한다.*/
	//---------------------------------------------------------------------
	while (true)
	{

		//*바꿀 색 값 설정한다.
		///@todo 바꿀 색 입력 받게 할 수정 필요하다.
		g_change_color = RED;

		//------------------------------------------------------------------------------
		//*시작 좌표 입력 메뉴 출력 및 시작 좌표 위치 키보드 입력한다.
		//------------------------------------------------------------------------------
		printf("시작 좌표 입력([col][공백][row]) :");

		//stdin을 console로 리디렉션
		freopen("CON", "r", stdin);

		//시작 좌표
		int start_x = 0;
		int start_y = 0;

		///@todo 입력 받은 행렬에 대한 인덱스 범위에 대한 예외처리가 필요하다.
		scanf_s("%d %d", &start_y, &start_x);
		start_x--;
		start_y--;

		//*바꿀 대상 색상 저장한다. ( ==바꿀 대상 색상은 시작좌표 위치의 색상 )
		g_target_color = current_map[start_y][start_x];

		//시작 지점 구조체 생성
		start_point = {  start_y , start_x };

		//*시작점 방문 체크한다.
		visited_map[start_y][start_x] == true;

		//총 색칠한 요소 갯수
		int cnt_painting = 0;

		//*시작점 요소 구조체를 스택에 삽입한다.
		Stack.push(&start_point);

		//현재 방문 중인 좌표
		int now_x = 0;
		int now_y = 0;

		//---------------------------------------------------------------------
		/*현재 방문 좌표와 인접한 좌표 중 같은 색상은 선택한 특정 색상으로 변경한다.*/
		//---------------------------------------------------------------------
		while ( Stack.pop( &now_point ) )
		{
			//*화면을 지운다.
			system("cls");

			//*현재 방문 좌표 저장한다.
			now_x = now_point.x;
			now_y = now_point.y;

			//*현재 좌표를 바꿀 색상으로 변경한다.
			current_map[now_y][now_x] = g_change_color;

			//*총 색상변경 갯수 증가
			cnt_painting++;
				
			//다음 이동 좌표 
			int next_x = 0;
			int next_y = 0;

			//*현재 방문 좌표와 인접한 주변 8방향 체크한다.
			for (int weight_y = -1; weight_y <= 1; weight_y++){

				for ( int weight_x = -1; weight_x <= 1; weight_x++){

					//현 좌표 기준 가중치 계산
					next_x = now_x + weight_x;
					next_y = now_y + weight_y;

					//동적할당 이차원 배열 범위 체크한다.
					if (CheckScopeOfTwoDimentionalAlloc(next_y, next_x, rows, columns) ){

						//이전 방문 여부 체크한다.
						if ( false == visited_map[next_y][next_x] ){

							//페인트 가능 여부 체크한다.
							if(CompareElementOfTwoDimensionalAlloc(current_map, next_y, next_x, g_target_color) ){
								
								//스텍 새 요소 설정한다.
								next_point = { next_y, next_x };

								//스택에 넣는다.
								if (Stack.push(&next_point)){	

									//스텍에 넣은 것 체크한다.
									visited_map[next_y][next_x] = true;
								}
								else{

									puts("넣기 실패");
									///@todo 스텍 실패에 대한 예외처리가 필요하다.
									return;
								}
							}
						}
					}
					else {

						///@todo 배열 인덱스 범위를 벗어나는 행, 열 인덱스가 입력된 경우에 대한 예외처리한다.
					}
				}
			}


			//------------------------------------------------------------------------------
			//*통계 정보 출력
			//	
			// :총 페인트 행, 열 정보
			// :칠 시작한 행, 열 정보
			// :현재 칠한 요소 행, 열 정보
			//------------------------------------------------------------------------------
			printf("total rows : %d ,", rows );
			printf(" cols : %d \n", columns );

			printf("start row  : %d ,", start_point.y);
			printf(" col  : %d \n", start_point.x );

			printf("now row    : %d ,", now_y );
			printf(" col  : %d \n", now_x  );

			//------------------------------------------------------------------------------
			//	페인트 맵 출력 함수 호출한다.
			//------------------------------------------------------------------------------
			DisplayPaintMap(current_map, columns, rows, now_x, now_y);
			
			//*변경한 색상 범위 정보 출력한다.
			printf("count painting : %d \n\n", cnt_painting);	

			//------------------------------------------------------------------------------
			//*	스택 내부 정보 출력
			//------------------------------------------------------------------------------
			DisplayInsideStack(&Stack);

			//화면 프레임 만큼 정지한다.
			Sleep(FPS);
			
		}//while


		/**
		페인트 칠이 끝난 후....
		결과 값 5초 유지 후 초기 입력 화면을 위한 화면 지우기 실행한다.
		*/
		Sleep(5000);
		system("cls");


		//------------------------------------------------------------------------------
		//*재반복 위한 초기화 진행한다.
		//------------------------------------------------------------------------------
		//visited_map 초기화한다.
		for (int ic = 0; ic < columns; ic++){

			memset(visited_map[ic], false, rows);
		}

		//original_map 초기화한다.
		if (!CopyTwoDimensionalArray(original_map, current_map, columns, rows)){

			//TODO: 메모리 복사 실패에 예외 처리가 필요하다.
			return;
		}
	}//while
}//main


 ///스택 내부 정보 출력한다.
void DisplayInsideStack(TemplateLinkedStack<Point> *stack) 
{
	//------------------------------------------------------------------------------
	//*	스택 내부 정보 출력
	//------------------------------------------------------------------------------
	puts("Stack elements");
	puts("top is next position");

	//스텍 내부에서 탑부터 바텀까지 방문한 노드
	Node<Point> current_circuit_node;
	Point current_circuit_Point = current_circuit_node.GetData();

	//*스텍 내부의 모든 요소를 출력한다. 
	if (stack->InitCurrentCircuitNode()) {

		while (NULL != stack->GetCurrentCircuitNode(&current_circuit_node)) {

			current_circuit_Point = current_circuit_node.GetData();
			printf("(%d %d)\n", current_circuit_Point.y , current_circuit_Point.x);

			stack->NextCurrentCircuitNode();
		}
	}

}





void PaintingRecursion(int now_x, int now_y, char **visited_map, char **current_map, int rows, int columns)///< 재귀 페인트칠한다.
{

	static Point recursion_list[1000];
	static int idx_recursion = 0;

	Point next_point;
	int next_x = 0;
	int next_y = 0;

	//색상을 변경한다.
	current_map[now_y][now_x] = g_change_color;

	//스택 내부 요소를 탑부터 바텀까지 출력한다.
	//	DisplayInsideStack(&Stack);

	//*현재 방문 좌표와 인접한 주변 8방향 체크한다.
	for (int weight_y = -1; weight_y <= 1; weight_y++) {

		for (int weight_x = -1; weight_x <= 1; weight_x++) {

			//현 좌표 기준 가중치 계산
			next_x = now_x + weight_x;
			next_y = now_y + weight_y;

			//동적할당 이차원 배열 범위 체크한다.
			if (CheckScopeOfTwoDimentionalAlloc(next_y, next_x, rows, columns)) {

				//이전 방문 여부 체크한다.
				if (false == visited_map[next_y][next_x]) {

					//페인트 가능 여부 체크한다.
					if (CompareElementOfTwoDimensionalAlloc(current_map, next_y, next_x, g_target_color)) {

						//스텍 새 요소 설정한다.
						next_point = { next_y, next_x };


						//재귀함수 실행한다.
						visited_map[next_y][next_x] = true;
						PaintingRecursion(next_x, next_y, visited_map, current_map, rows, columns);

					}
				}
			}
			else {
				///@todo 배열 인덱스 범위를 벗어나는 행, 열 인덱스가 입력된 경우에 대한 예외처리한다.
			}
		}
	}
}
