#pragma once


#include "COLOR_TYPE.h"

#include <iostream>
using namespace std;


/*!
@brief ������ �迭 �� ��� ��� ����Ѵ�.

@todo  ����� 3�ڸ� ���� ������ ����� �����ϴ�.
*/
template <typename DATA_TYPE>
void DisplayDatasOfArr(DATA_TYPE *const  arr, int sz_elements){

	for (int ie = 0; ie < sz_elements; ie++) {

		printf("%3d ", arr[ie]);
	}
	printf("\n");
}

/*!
@brief �����Ҵ� ���߹迭 �� ��� ��� ����Ѵ�. ( �������̵�1 )

@remark ���ѵ��� ���� �ε��� ���� ������ ���� �̿��Ѵ�.

\ingroup InputOutput
*/
bool DisplayCharsOfTwoDimentionalDynamicAlloc(char **const map, int max_y, int max_x)
{
	for (int ic = 0; ic < max_y; ic++){

		for (int jr = 0; jr < max_x; jr++) {

			printf("%c", map[ic][jr]);
		}
		printf("\n");
	}

	return true;
}

/*!
@brief �����Ҵ� ���߹迭 �� ��� ��� ����Ѵ�. ( �������̵�2 )

@remark ���ѵ� �ε��� ���� ������ ���� �̿��Ѵ�.
*/
bool DisplayCharsOfTwoDimentionalDynamicAlloc(char ** const map, int max_y, int max_x, int now_x, int now_y){

	//*����ó�� : �迭 ���� üũ�Ѵ�.
	if (max_y <= now_y || max_x <= now_x) {

		return false;
	}


	for (int ic = 0; ic < max_y; ic++)
	{
		for (int jr = 0; jr < max_x; jr++)
		{
				printf("%c", map[ic][jr]);
		}
		printf("\n");

	}

	return true;
}


///���� �����Ҵ� �迭 �̿��Ͽ� ���� �ְ� ����Ѵ�.
///\ingroup InputOutput
void DisplayPaintMap(char ** const map, int max_y, int max_x, int now_x, int now_y){


	//���� ���� �����Ѵ�.
	for (int i = 0; i < max_x; i++) {

		printf("--");
	}
	puts("");

	int current_color;
	for (int ic = 0; ic < max_y; ic++){

		for (int jr = 0; jr < max_x; jr++){

			//*���� ��Ұ� ���� �ϴ��� üũ�Ѵ�.
			if (map[ic][jr] != ' '){

				current_color = (map[ic][jr] ) ;

				//*���� �迭 ����� ������ current_color�� ���� ��Ī�Ǵ� �÷� ����
				switch (current_color){

				//blue
				case 1:	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
					break;
				//green
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					break;
				//blue
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					break;
				//yellow
				case 6:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					break;
				//white
				case 7:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					break;
				}

				//*������ ���� ���� �迭 ��Ҹ� ���
				if (ic == now_y && jr == now_x) {

					cout << "��"; //�ֱٿ� ��ĥ �� �� ǥ�� ��ȣ
				}
				else {

					cout << "��"; //�ֱ� �� ��ĥ �� �� ǥ�� ��ȣ
				}
			}
			else {
				//*�� ������ ��� ����� �����̴�.
				cout << "  ";
			}

			//*�ܼ� Ŀ�� ���� �������� �����Ѵ�.( ���� ����==ȭ��Ʈ )
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		cout<< "\n";
	}

	//*���� �ܼ� ������ �����Ѵ�.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	//���� ���� �����Ѵ�.
	for (int i = 0; i < max_x; i++) {

		printf("--");
	}
	puts("");
}


/**
 @brief ���� �����迭 ���� 

 @todo  �迭 ���� ����� �ε��� ���� �� ���� �߻��� ���� ����ó���� �ʿ��ϴ�. 

 ///\ingroup InputOutput
*/
//------------------------------------------------------------------------------
template <typename DATA_TYPE>
bool CopyTwoDimensionalArray(DATA_TYPE ** const src_arr, DATA_TYPE **dest_arr, int columns, int rows){

	//*���� ó��1
	if (src_arr == NULL || dest_arr == NULL) {

		return false;
	}
	//*���� ó��2
	if (columns < 0 || rows < 0) {

		return false;
	}
	//*���� �����Ѵ�.
	for (int i = 0; i < columns; i++){

		memcpy(dest_arr[i], src_arr[i], rows);
	}

	return true;
}



/**
   @brief ���� �����Ҵ��� �ش� x,y�� �����ϴ� ����� ���� ���ڸ� ���Ѵ�.

   @todo  ��, ���� �ε����� ���� ����ó���� �ʿ��ϴ�.
*/
template <typename DATA_TYPE>
bool CompareElementOfTwoDimensionalAlloc(DATA_TYPE **map, int checkY, int checkX, DATA_TYPE matching_data){

	if (map[checkY][checkX] == matching_data){

		return true;
	}
	return false;
}




//*���� �����Ҵ� �迭 ���� üũ�Ѵ�.
bool CheckScopeOfTwoDimentionalAlloc(int check_y, int check_x, int max_y, int max_x){

	//*�迭 ���� �� ��� �ε��� ���� ���� üũ�Ѵ�.
	if ((0 <= check_y && check_y < max_y) && 
		(0 <= check_x && check_x < max_x)){

		return true;
	}
	else {

		return false;
	}
}



//*���� �����迭 �ʱ�ȭ�Ѵ�.
//\ingroup InputOutput
template <typename DATA_TYPE>
bool InitTwoDimensionalArray(DATA_TYPE ***arr, int columns, int rows){

	*arr = (DATA_TYPE**)malloc(sizeof(DATA_TYPE*)*columns);

	//*����ó��
	if (NULL == *arr) {

		false;
	}

	for (int ic = 0; ic < columns; ic++){

		(*arr)[ic] = (DATA_TYPE*)malloc(sizeof(DATA_TYPE)*rows);

		//*���� ó�� : �����Ҵ��� �ȵ� ��� üũ�Ѵ�.
		if ( NULL ==(*arr)[ic]) {

			false;
		}
	}

	return true;
}




