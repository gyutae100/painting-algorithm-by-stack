/*
�̷� ����� Ư¡�� �������ڸ� ������ �����ϴ�.

- ���� ������ ������ �ʱ� ���� ������ Ż�� ������ �־�� �Ѵ�.

- �ڵ带 �ܼ�ȭ �� �� �ִ�.

- ��� �Լ��� ȣ�� �� ���� ���� ������ �̿��ϹǷ� �����ϰ� ȣ���ϸ� ���� �����÷ο찡 �Ͼ �� �ִ�.

- ��� �Լ��� ȣ�� Ƚ���� ������ ���� ������ ��� �Լ��� ���� ���� ����� ���� �޶�����.

- ����� �� ���� �帧�� �ľ��ϱ� �����.
*/

/**
@file main.cpp

@date 2018/04/24

@author ����� ( gyutae100@gmail.com )

@version 1.0    
*/

/**
	\defgroup Painting
	@brief ������ ���� ���

	\defgroup InputOutput
	@brief I/O ���� ���
*/
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "lib_io.h"
#include "COLOR_TYPE.h"

#include "lib_template_linked_stack.h"

using namespace std;

#define FPS 2000 ///<�� ������ �ð�

/**
@struct Point

@brief ������ ��ǥ ����ü
*/
typedef struct Point{

	int y;
	int x;
}Point;

char g_target_color = '\0';	 //*<���� �� Ư�� ���� ��  
char g_change_color = '\0';  //*<�ٲ� ���� �� ��

int g_columns = 0;			 //*<�� �� 
int g_rows = 0;				 //*<�� ��

void PaintingRecursion(int now_x, int now_y, char **visited_map, char **current_map, int rows, int columns);///< ��� ����Ʈĥ�Ѵ�.

void main(void)
{

	//����Ʈ �� �� ��, ��
	int columns = 0;	
	int rows = 0;		

	//*���� ��� ���� ����.
	FILE * stream = freopen("map2.txt", "r", stdin);  

	//*�� ��, �� ���� �����Ѵ�.
	scanf("%d", &rows);		
	scanf("%d", &columns);	

	//���� �� ��, �� ���� �����Ѵ�.
	g_columns = columns;
	g_rows = rows;

	//�ؽ�Ʈ ���� 1�� ��, �� ���� �� �ٷ� ���� ������ ���� ���ڴ� �а� �ٷ� ������.
	char temp = NULL;	
	scanf("%c", &temp);

	//���� �� 
	char  ** original_map = NULL;

	//��� ��
	char ** current_map = NULL;

	//------------------------------------------------------------------------------
	//	�湮 üũ�� ��
	//	
	//	:�湮�� �ش� ��ǥ ��� true
	//	:�̹湮�� �ش� ��ǥ ��� false
	//------------------------------------------------------------------------------
	char ** visited_map = NULL;

	//------------------------------------------------------------------------------
	//*�۾��� �ʿ��� ��� ���� ���� �迭 �޸� �Ҵ��Ѵ�.
	//------------------------------------------------------------------------------
	if ( ! InitTwoDimensionalArray( &original_map, columns, rows ) ){
		
		///@todo �Ҵ� ���� ����ó���� �ʿ��ϴ�.
		return;
	}
	if ( ! InitTwoDimensionalArray( &current_map, columns, rows ) ){
		
		///@see �Ҵ� ���� ����ó���� �ʿ��ϴ�.
		return;
	}
	if ( ! InitTwoDimensionalArray( &visited_map, columns, rows ) ){

		///@todo �Ҵ� ���� ����ó���� �ʿ��ϴ�.
		return;
	}

	//*original_map ���� ��� �ʱ�ȭ�Ѵ�.
	for (int ic = 0; ic < columns; ic++){

		for (int jr = 0; jr < rows; jr++){

			scanf("%c", &original_map[ic][jr]);
			
			//�ƽ�Ű ���ڸ� ����ȭ�Ѵ�.
			original_map[ic][jr] = original_map[ic][jr] - '0'; 
		}

		//�� ���� �������� �����ϴ� ���� ���ڸ� ���� �� ������.
		scanf("%c", &temp); 	
	}

	//*���� �б� �Ϸ��Ѵ�.
	fclose(stream);

	//*	visited_map �ʱ�ȭ�Ѵ�.
	for (int ic = 0; ic < columns; ic++){

		memset(visited_map[ic], false, rows);
	}

	//*current_map�� original_map �����Ѵ�.
	///@todo ���߿� memcpy�� ��ü �� ��.
	if (! CopyTwoDimensionalArray(original_map, current_map, columns, rows)){

		//TODO ���� ���п� ���� ����ó���� �ʿ��ϴ�.
		return;
	}

	//��ġ ����ü
	Point start_point; //���� ��ġ
	Point next_point;  //���� �̵� ��ġ
	Point now_point;   //���� ��ġ


	//---------------------------------------------------------------------
	/*������ Ư�� ���� ������ ���� ���� ������ �����Ѵ�.\n
	������ �� ���� ����, ��� ���� ����Ѵ�.*/
	//---------------------------------------------------------------------
	while (true)
	{

		//*�ٲ� �� �� �����Ѵ�.
		///@todo �ٲ� �� �Է� �ް� �� ���� �ʿ��ϴ�.
		g_change_color = RED;

		//------------------------------------------------------------------------------
		//*���� ��ǥ �Է� �޴� ��� �� ���� ��ǥ ��ġ Ű���� �Է��Ѵ�.
		//------------------------------------------------------------------------------
		printf("���� ��ǥ �Է�([col][����][row]) :");

		//stdin�� console�� ���𷺼�
		freopen("CON", "r", stdin);

		//���� ��ǥ
		int start_x = 0;
		int start_y = 0;

		///@todo �Է� ���� ��Ŀ� ���� �ε��� ������ ���� ����ó���� �ʿ��ϴ�.
		scanf_s("%d %d", &start_y, &start_x);
		start_x--;
		start_y--;

		//*�ٲ� ��� ���� �����Ѵ�. ( ==�ٲ� ��� ������ ������ǥ ��ġ�� ���� )
		g_target_color = current_map[start_y][start_x];

		//���� ���� ����ü ����
		start_point = {  start_y , start_x };

		//*������ �湮 üũ�Ѵ�.
		visited_map[start_y][start_x] == true;

		//�� ��ĥ�� ��� ����
		int cnt_painting = 0;

		//���� �湮 ���� ��ǥ
		int now_x = 0;
		int now_y = 0;

		//---------------------------------------------------------------------
		/*���� �湮 ��ǥ�� ������ ��ǥ �� ���� ������ ������ Ư�� �������� �����Ѵ�.*/
		//---------------------------------------------------------------------
		//*ȭ���� �����.
		system("cls");


		//*�� ���󺯰� ���� ����	
		cnt_painting++;
				
		//���� �̵� ��ǥ 
		int next_x = 0;
		int next_y = 0;

			
		//����Ʈ ����Լ� ĥ�ϱ�.
		PaintingRecursion(start_x, start_y, visited_map, current_map, g_rows, g_columns);
				
		//ȭ�� ������ ��ŭ �����Ѵ�.
		Sleep(FPS);

		/**
		����Ʈ ĥ�� ���� ��....
		��� �� 5�� ���� �� �ʱ� �Է� ȭ���� ���� ȭ�� ����� �����Ѵ�.
		*/
		Sleep(5000);
		system("cls");

		//------------------------------------------------------------------------------
		//*��ݺ� ���� �ʱ�ȭ �����Ѵ�.
		//------------------------------------------------------------------------------
		//visited_map �ʱ�ȭ�Ѵ�.
		for (int ic = 0; ic < columns; ic++){

			memset(visited_map[ic], false, rows);
		}

		//original_map �ʱ�ȭ�Ѵ�.
		if (!CopyTwoDimensionalArray(original_map, current_map, columns, rows)){

			//TODO: �޸� ���� ���п� ���� ó���� �ʿ��ϴ�.
			return;
		}
	}//while
}//main


///��� ����Ʈĥ�Ѵ�.
void PaintingRecursion(int now_x, int now_y, char **visited_map, char **current_map, int rows, int columns)
{
	static int idx_recursion = 0;

	Point next_point;
	int next_x = 0;
	int next_y = 0;

	//------------------------------------------------------------------------------
	//*��� ���� ���
	//	
	// :�� ����Ʈ ��, �� ����
	// :ĥ ������ ��, �� ����
	// :���� ĥ�� ��� ��, �� ����
	//------------------------------------------------------------------------------
	printf("total rows : %d ,", rows);
	printf(" cols : %d \n", columns);

	printf("now row    : %d ,", now_y);
	printf(" col  : %d \n", now_x);

	//������ �����Ѵ�.
	current_map[now_y][now_x] = g_change_color;

	//------------------------------------------------------------------------------
	//	����Ʈ �� ��� �Լ� ȣ���Ѵ�.
	//------------------------------------------------------------------------------
	DisplayPaintMap(current_map, columns, rows, now_x, now_y);
	Sleep(1000);
	system("cls");

	//*���� �湮 ��ǥ�� ������ �ֺ� 8���� üũ�Ѵ�.
	for (int weight_y = -1; weight_y <= 1; weight_y++) {

		for (int weight_x = -1; weight_x <= 1; weight_x++) {

			//�� ��ǥ ���� ����ġ ���
 			next_x = now_x + weight_x;
			next_y = now_y + weight_y;

			//�����Ҵ� ������ �迭 ���� üũ�Ѵ�.
			if (CheckScopeOfTwoDimentionalAlloc(next_y, next_x, rows, columns)) {

				//���� �湮 ���� üũ�Ѵ�.
				if (false == visited_map[next_y][next_x]) {

					//����Ʈ ���� ���� üũ�Ѵ�.
					if (CompareElementOfTwoDimensionalAlloc(current_map, next_y, next_x, g_target_color)) {

						//���� �� ��� �����Ѵ�.
						next_point = { next_y, next_x };

						//����Լ� �����Ѵ�.
						visited_map[next_y][next_x] = true;
						PaintingRecursion(next_x, next_y, visited_map, current_map, rows, columns);
					}
				}
			}
			else {

				///@todo �迭 �ε��� ������ ����� ��, �� �ε����� �Էµ� ��쿡 ���� ����ó���Ѵ�.
			}
		}
	}
}
