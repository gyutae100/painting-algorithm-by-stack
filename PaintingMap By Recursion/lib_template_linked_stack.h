#pragma once


#include <iostream>
using namespace std;

/** 
@class Node 

@brief ���ø� ��ũ�� ����Ʈ ���� ���� ��� Ŭ����

\ingroup Painting
*/
template <typename DATA_TYPE>
class Node{

private:

	DATA_TYPE _data;	///<���� ����� ������ ��
	Node *_below;		///<���� ��� �Ʒ� ��� �ּҰ�

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

	
	///���� ��� �Ʒ� ��� �ּ� ��ȯ
	Node* GetBelow(){	

		return _below;
	}

};


/**
@class TemplateLinkedStack

@brief ���ø� ��ũ�� ���� Ŭ����

@remark ��� ������ ���� ��� ������ ���� ���� ����, ���� ���� �Ѱ� �뷮���� ���� �� ����� ũ�⸦ ���صθ� ���?\n
@remark ���� �ڷ����� �� �����Ϸ��� ��� �ؾ� �ϴ°�??

\ingroup Painting 
*/
template <typename DATA_TYPE>
class TemplateLinkedStack{

private:

	unsigned int _cnt_element; ///<���� �� ��� ���� 
	Node<DATA_TYPE> *_top;	   ///<���� �ֻ�� ��� ������

	bool _use_maximum_capacity;///<�ִ� ��� ���� ���� ���� ���� �÷���
	long _cnt_max_element;		   ///<���� ���� ���� ���� true ��, �ִ� ���� ��� ����

	Node<DATA_TYPE> *_current_circuit_node; ///<���� �湮 ��ȸ ��� 

public:

	///�ִ� ��� ���� ���� ���� ������
	TemplateLinkedStack(){

		_cnt_element = 0;
		_top = NULL;

		_use_maximum_capacity = false;
		_cnt_max_element = -1;

		_current_circuit_node = NULL;
	}


	///�ִ� ��� ���� ���� ������
	TemplateLinkedStack(long sz_capacity){

		_cnt_element = 0;
		_top = NULL;

		_use_maximum_capacity = true;
		_cnt_max_element = sz_capacity;
	}

	///�Ҹ���
	~TemplateLinkedStack(){

		Node<DATA_TYPE> *old_node;

		while (_top != NULL){

			old_node = _top->GetBelow();
			delete (_top);
			_top = old_node;
		}
	}

	bool push(DATA_TYPE * _data){

		//�ִ� ��� ���� ���� true �� ���
		if (true == _use_maximum_capacity){

			//�뷮 �Ѱ� �ʰ�
			if (_cnt_max_element == _cnt_element){
				return false;
			}

		}

		//��� ���� �߰��Ѵ�.
		_cnt_element++;

		//��Ұ� �������� �ʴ� ��츦 üũ�Ѵ�.
		if (NULL==_top){

			_top = new Node<DATA_TYPE>(*_data, NULL);
		}
		else {

			Node<DATA_TYPE> *tmp = new Node<DATA_TYPE>(*_data, _top);
			_top = tmp;
		}

		//���ο� ��尡 �� �����Ǿ����� üũ�Ѵ�.
		if (_top != NULL) {
		
			return true;
		}
		else {

			return false;
		}
	}


	bool peek(DATA_TYPE * dest_data){

		//��ȯ �� ������
		DATA_TYPE r_data;

		//��Ұ� �������� �ʴ� ��츦 üũ�Ѵ�.
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

		//��Ұ� �������� �ʴ� ��츦 üũ�Ѵ�.
		if (_top == NULL){

			return false;

		}
		else{

			//��� ���� �����Ѵ�.
			_cnt_element--;

			//���� ��� �����´�.
			Node<DATA_TYPE> *delete_node = this->_top;

			//��� ��ȯ�Ѵ�.
			*dest_data = delete_node->GetData();

			//_top �����Ѵ�.
			this->_top = delete_node->GetBelow();

			//���� top ��� �����Ѵ�.
			free(delete_node);


			return true;
		}
	}


	///���� �� ��� ���� ��ȯ
	int GetCount(){

		return _cnt_element;
	}


	///	�湮 ��ȸ ��� �ʱ�ȭ
	bool InitCurrentCircuitNode(){

		_current_circuit_node = _top;
		if ( NULL != _current_circuit_node ) {
			
			return true;
		}
		else {

			return false;
		}
	}


	///���� �湮 ��ȸ ��带 ���� �湮 ��ȸ ���� �����Ѵ�.
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


	///���� �湮 ��ȸ ��� ������ ��ȯ�Ѵ�.
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