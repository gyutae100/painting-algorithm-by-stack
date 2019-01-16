#pragma once


#include "COLOR_TYPE.h"

#include <iostream>
using namespace std;


/*!
@brief 일차원 배열 내 모든 요소 출력한다.

@todo  현재는 3자리 숫자 까지만 출력이 가능하다.
*/
template <typename DATA_TYPE>
void DisplayDatasOfArr(DATA_TYPE *const  arr, int sz_elements){

	for (int ie = 0; ie < sz_elements; ie++) {

		printf("%3d ", arr[ie]);
	}
	printf("\n");
}

/*!
@brief 동적할당 이중배열 내 모든 요소 출력한다. ( 오버라이딩1 )

@remark 제한되지 않은 인덱스 범위 내에서 사용시 이용한다.

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
@brief 동적할당 이중배열 내 모든 요소 출력한다. ( 오버라이딩2 )

@remark 제한된 인덱스 범위 내에서 사용시 이용한다.
*/
bool DisplayCharsOfTwoDimentionalDynamicAlloc(char ** const map, int max_y, int max_x, int now_x, int now_y){

	//*예외처리 : 배열 범위 체크한다.
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


///이중 동적할당 배열 이용하여 색깔 있게 출력한다.
///\ingroup InputOutput
void DisplayPaintMap(char ** const map, int max_y, int max_x, int now_x, int now_y){


	//시작 문자 삽입한다.
	for (int i = 0; i < max_x; i++) {

		printf("--");
	}
	puts("");

	int current_color;
	for (int ic = 0; ic < max_y; ic++){

		for (int jr = 0; jr < max_x; jr++){

			//*현재 요소가 존재 하는지 체크한다.
			if (map[ic][jr] != ' '){

				current_color = (map[ic][jr] ) ;

				//*현재 배열 요소의 색상인 current_color의 수에 매칭되는 컬러 선택
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

				//*정해진 색상에 따라 배열 요소를 출력
				if (ic == now_y && jr == now_x) {

					cout << "▼"; //최근에 색칠 한 곳 표시 기호
				}
				else {

					cout << "■"; //최근 외 색칠 한 곳 표시 기호
				}
			}
			else {
				//*빈 공간인 경우 출력은 공백이다.
				cout << "  ";
			}

			//*콘솔 커서 원래 색상으로 복구한다.( 원래 색상==화이트 )
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		cout<< "\n";
	}

	//*원래 콘솔 색으로 변경한다.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	//마감 문자 삽입한다.
	for (int i = 0; i < max_x; i++) {

		printf("--");
	}
	puts("");
}


/**
 @brief 이중 동적배열 복사 

 @todo  배열 범위 벗어나는 인덱스 접근 시 에러 발생에 대한 예외처리가 필요하다. 

 ///\ingroup InputOutput
*/
//------------------------------------------------------------------------------
template <typename DATA_TYPE>
bool CopyTwoDimensionalArray(DATA_TYPE ** const src_arr, DATA_TYPE **dest_arr, int columns, int rows){

	//*예외 처리1
	if (src_arr == NULL || dest_arr == NULL) {

		return false;
	}
	//*예외 처리2
	if (columns < 0 || rows < 0) {

		return false;
	}
	//*복사 진행한다.
	for (int i = 0; i < columns; i++){

		memcpy(dest_arr[i], src_arr[i], rows);
	}

	return true;
}



/**
   @brief 이중 동적할당의 해당 x,y에 존재하는 요소의 값과 인자를 비교한다.

   @todo  행, 열의 인덱스에 대한 예외처리가 필요하다.
*/
template <typename DATA_TYPE>
bool CompareElementOfTwoDimensionalAlloc(DATA_TYPE **map, int checkY, int checkX, DATA_TYPE matching_data){

	if (map[checkY][checkX] == matching_data){

		return true;
	}
	return false;
}




//*이중 동적할당 배열 범위 체크한다.
bool CheckScopeOfTwoDimentionalAlloc(int check_y, int check_x, int max_y, int max_x){

	//*배열 범위 내 요소 인덱스 가능 여부 체크한다.
	if ((0 <= check_y && check_y < max_y) && 
		(0 <= check_x && check_x < max_x)){

		return true;
	}
	else {

		return false;
	}
}



//*이중 동적배열 초기화한다.
//\ingroup InputOutput
template <typename DATA_TYPE>
bool InitTwoDimensionalArray(DATA_TYPE ***arr, int columns, int rows){

	*arr = (DATA_TYPE**)malloc(sizeof(DATA_TYPE*)*columns);

	//*예외처리
	if (NULL == *arr) {

		false;
	}

	for (int ic = 0; ic < columns; ic++){

		(*arr)[ic] = (DATA_TYPE*)malloc(sizeof(DATA_TYPE)*rows);

		//*예외 처리 : 동적할당이 안된 경우 체크한다.
		if ( NULL ==(*arr)[ic]) {

			false;
		}
	}

	return true;
}




