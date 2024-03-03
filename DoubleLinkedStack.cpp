#pragma once
#ifndef _STACK_ON_DOUBLE_LINKED_LIST_
#define _STACK_ON_DOUBLE_LINKED_LIST_

#include <iostream>

//Stack based on double linked list
template <class DataType>
class SDLL {
protected:
	class Node {
	public:
		Node():Prev(nullptr), Next(nullptr),Val(){}
		Node* Prev;
		Node* Next;

		DataType Val;
	};
public:
	SDLL():Head(nullptr),Tail(nullptr){}
	~SDLL() { while (Head != nullptr) { popH(); delete Head; delete Tail; }}
protected:
	Node* Head;
	Node* Tail;

	bool EqualData(const DataType& data1, const DataType& data2) {
		return data1 == data2;
	}

public:
	bool empty() {
		return (Head == nullptr) && (Tail == nullptr);
	}

	DataType get() {
		if (Tail == nullptr) {
			return DataType();
		}
		return Tail->Val;
	}

	DataType find(const DataType& data) {
		Node* node = Tail;
		while (node != nullptr) {

			if (EqualData(node->Val, data)) {
				return node->Val;
			}
			node = node->Prev;
		}
		return nullptr;
	}

	DataType findH(const DataType& data) {
		Node* node = Head;
		while (node != nullptr) {

			if (EqualData(node->Val, data)) {
				return node->Val;
			}
			node = node->Next;
		}
		return nullptr;
	}

	DataType getH()const {
		if (Head == nullptr) {
			return DataType();
		}
		return Head->Val;
	}

	void add(const DataType& data) {

		Node* newNode = new Node();
		newNode->Val = data;

		if (empty()) {
			Head = newNode;
			Tail = newNode;

			return;
		}

		Node* prevNode = Tail;

		prevNode->Next = newNode;
		newNode->Prev = prevNode;
		Tail = newNode;

	}

	void addH(const DataType& data) {

		Node* newNode = new Node();
		newNode->Val = data;

		if (empty()) {
			Head = newNode;
			Tail = newNode;

			return;
		}

		Node* nextNode = Head;

		nextNode->Prev = newNode;
		newNode->Next = nextNode;
		Head = newNode;

	}

	DataType pop() {

		if (Head == Tail) {
			if (Tail == nullptr) {
				return DataType();
			}
			DataType Save = Tail->Val;
			Head = nullptr;
			Tail = nullptr;
			return Save;
		}
		DataType TailNodeSave = Tail->Val;
		Node* TailNode = Tail;
		Node* prevNode = TailNode->Prev;

		prevNode->Next = nullptr;
		Tail = prevNode;

		delete TailNode;
		return TailNodeSave;
	}

	DataType popH() {
		if (Head == Tail) {
			if (Head == nullptr) {
				return DataType();
			}
			DataType Save = Head->Val;
			Head = nullptr;
			Tail = nullptr;
			return Save;
		}

		DataType HeadNodeSave = Head->Val;
		Node* HeadNode = Head;
		Node* nextNode = HeadNode->Next;

		nextNode->Prev = nullptr;
		Head = nextNode;
		delete HeadNode;
		return HeadNodeSave;
	}

	void del(const DataType& data) {
		if (empty()) {
			return;
		}

		Node* node = Tail;
		if (Head == Tail && EqualData(node->Val, data)) {
			Head = nullptr;
			Tail = nullptr;

			delete node;
			return;
		}

		while (node != nullptr) {
			if (EqualData(node->Val, data)) {
				if (node == Head) {
					popH();
					return;
				}
				else if (node == Tail) {
					pop();
					return;
				}

				Node* prevNode = node->Prev;
				Node* nextNode = node->Next;

				prevNode->Next = nextNode;
				delete node;
				return;
			}
			node = node->Prev;
		}
	}

	void delH (const DataType& data) {
		if (empty()) {
			return;
		}

		Node* node = Head;
		if (Head == Tail && EqualData(node->Val, data)) {
			Head = nullptr;
			Tail = nullptr;

			delete node;
			return;
		}

		while (node != nullptr) {
			if (EqualData(node->Val, data)) {

				if (node == Head) {
					popH();
					return;
				}
				else if (node == Tail) {
					pop();
					return;
				}

				Node* prevNode = node->Prev;
				Node* nextNode = node->Next;

				prevNode->Next = nextNode;
				delete node;
				return;
			}
			node = node->Next;
		}
	}

	void log() const {

		if (Head == nullptr && Tail == nullptr) {
			std::cout << "\n\n--Current stack is empty--\n\n";
			return;
		}

		Node* node = Head;
		int c = 0;

		std::cout << "\n\n--Start Stack Log--\n";

		while (node != nullptr) {
			std::cout << ++c << ". " << node->Val << "\n";
			node = node->Next;
		}

		std::cout << "--End Stack Log--\n\n";
	}

	void print()const {
		if (Head == nullptr && Tail == nullptr) {
			std::cout << "--Current stack is empty--";
		}

		Node* node = Head;
		while (node != nullptr) {
			std::cout << node->Val <<" ";
			node = node->Next;
		}
	}

};

#endif
