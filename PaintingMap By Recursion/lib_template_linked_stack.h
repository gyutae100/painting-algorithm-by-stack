#pragma once


#include <iostream>
using namespace std;

/** 
@class Node 

@brief 템플릿 링크드 리스트 형식 스택 노드 클래스

\ingroup Painting
*/
template <typename DATA_TYPE>
class Node{

private:

	DATA_TYPE _data;	///<현재 노드의 데이터 값
	Node *_below;		///<현재 노드 아래 노드 주소값

public:

	Node(DATA_TYPE data, Node * below){

		_data = data;
		_below = below;
	}

	Node(){

		_below = NULL;
	}

	DATA_TYPE GetData(){

		return _data;
	}

	
	///현재 요소 아래 노드 주소 반환
	Node* GetBelow(){	

		return _below;
	}

};


/**
@class TemplateLinkedStack

@brief 템플릿 링크드 스택 클래스

@remark 요소 갯수로 스택 요소 갯수를 한정 짓지 말고, 스택 내부 한계 용량으로 스택 내 요소의 크기를 정해두면 어떨까?\n
@remark 여러 자료형을 다 저장하려면 어떻게 해야 하는가??

\ingroup Painting 
*/
template <typename DATA_TYPE>
class TemplateLinkedStack{

private:

	unsigned int _cnt_element; ///<스택 내 요소 개수 
	Node<DATA_TYPE> *_top;	   ///<스택 최상단 요소 포인터

	bool _use_maximum_capacity;///<최대 요소 개수 저장 설정 여부 플래그
	long _cnt_max_element;		   ///<개수 저장 설정 여부 true 시, 최대 스택 요소 개수

	Node<DATA_TYPE> *_current_circuit_node; ///<현재 방문 순회 노드 

public:

	///최대 요소 갯수 설정 없는 생성자
	TemplateLinkedStack(){

		_cnt_element = 0;
		_top = NULL;

		_use_maximum_capacity = false;
		_cnt_max_element = -1;

		_current_circuit_node = NULL;
	}


	///최대 요소 갯수 설정 생성자
	TemplateLinkedStack(long sz_capacity){

		_cnt_element = 0;
		_top = NULL;

		_use_maximum_capacity = true;
		_cnt_max_element = sz_capacity;
	}

	///소멸자
	~TemplateLinkedStack(){

		Node<DATA_TYPE> *old_node;

		while (_top != NULL){

			old_node = _top->GetBelow();
			delete (_top);
			_top = old_node;
		}
	}

	bool push(DATA_TYPE * _data){

		//최대 요소 개수 설정 true 인 경우
		if (true == _use_maximum_capacity){

			//용량 한계 초과
			if (_cnt_max_element == _cnt_element){
				return false;
			}

		}

		//요소 개수 추가한다.
		_cnt_element++;

		//요소가 존재하지 않는 경우를 체크한다.
		if (NULL==_top){

			_top = new Node<DATA_TYPE>(*_data, NULL);
		}
		else {

			Node<DATA_TYPE> *tmp = new Node<DATA_TYPE>(*_data, _top);
			_top = tmp;
		}

		//새로운 노드가 잘 생성되었는지 체크한다.
		if (_top != NULL) {
		
			return true;
		}
		else {

			return false;
		}
	}


	bool peek(DATA_TYPE * dest_data){

		//반환 할 데이터
		DATA_TYPE r_data;

		//요소가 존재하지 않는 경우를 체크한다.
		if (_top == NULL){

			return false;
		}
		else{

			r_data = this->_top->GetData();
			*dest_data = r_data;
			return true;
		}
	}


	bool pop(DATA_TYPE *dest_data){

		//요소가 존재하지 않는 경우를 체크한다.
		if (_top == NULL){

			return false;

		}
		else{

			//요소 갯수 감소한다.
			_cnt_element--;

			//삭제 노드 가져온다.
			Node<DATA_TYPE> *delete_node = this->_top;

			//요소 반환한다.
			*dest_data = delete_node->GetData();

			//_top 변경한다.
			this->_top = delete_node->GetBelow();

			//이전 top 요소 삭제한다.
			free(delete_node);


			return true;
		}
	}


	///스택 내 요소 갯수 반환
	int GetCount(){

		return _cnt_element;
	}


	///	방문 순회 노드 초기화
	bool InitCurrentCircuitNode(){

		_current_circuit_node = _top;
		if ( NULL != _current_circuit_node ) {
			
			return true;
		}
		else {

			return false;
		}
	}


	///현재 방문 순회 노드를 다음 방문 순회 노드로 변경한다.
	bool NextCurrentCircuitNode()
	{

		Node<DATA_TYPE> *tmp_node = _current_circuit_node->GetBelow();
		if (NULL != tmp_node) {

			_current_circuit_node = tmp_node;
			return true;
		}
		else {
			_current_circuit_node = NULL;
			return false;
		}
	}


	///현재 방문 순회 노드 데이터 반환한다.
	bool GetCurrentCircuitNode(Node<DATA_TYPE> *dest_data){

		if (_current_circuit_node != NULL){
			

				*dest_data = *_current_circuit_node;
				return true;
		}
		else {

			Point null_point = { -1, -1 };
			Node<DATA_TYPE> *null_node = new Node<DATA_TYPE>(null_point, NULL);
			*dest_data = *null_node;

			return false;
		}
	}
};