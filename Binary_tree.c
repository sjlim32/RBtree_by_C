/*
* 이진탐색트리
- 탐색 작업을 효율적으로 하기 위한 이진트리
- 자신의 왼쪽 서브트리 노드의 키 값은 자신의 키 값보다 작은 값 // 자신의 오른쪽 서브트리 노드의 키 값은 자신의 키 값보다 큰 값
- 이잔탐색트리가 좌, 우로 편향될 경우, 실제로는 선형리스트가 되기 때문에 검색이 비효율적

? 이진트리
-> 자식 노드를 최대 2개 갖는 트리

- 자료구조 구성
+-----------------------------------------------------------+
|                      <Binary Tree>                        |
|                   _____--- 21 ---_____                    |
|               _- 15 - _          _ - 30 - _               |
|              10      18         25        40              |
|             _-_     _-_        _-_       _-_              |
|            7  11   17 20      23 27     37 44             |
+-----------------------------------------------------------+
*/

//? - - - - - - - - - - - - - - Binary_tree.c - - - - - - - - - - - - - - ?//

#include <stdio.h>        // printf, scanf Func library
#include <stdlib.h>       // malloc, free Func library

/* Basic Node Structure */
typedef struct NODE {
  int data;
  struct NODE* leftChild;
  struct NODE* rightChild;
} Node;


//! - - - - - - - - - - - - - - function declaration - - - - - - - - - - - - - - !//
/* define Binary Tree Node */
Node* Root;

// Node* initNode(int, Node*, Node*);
int inspec_scanf();
void clearMemory();
Node* insertion(Node*, int);
Node* deletion(Node*, int);
Node* search_min(Node*);
Node* search_max(Node*);
// Node* print(Node*);
Node* preO_print(Node*);
Node* InO_print(Node*);
Node* postO_print(Node*);

//! - - - - - - - - - - - - - - main - - - - - - - - - - - - - - !//

int main() {
  int command;
  int input;

  /* init ment */
  printf("이진탐색트리 생성 프로그램입니다 :)\n");
  printf("명령어 : 0 = 종료 / 1 = 데이터 추가 / 2 = 데이터 삭제 / 3 = 전위순회 출력 / 4 = 중위순회 출력 / 5 = 후위순회 출력 \n\n");

  /* loop select command*/
  for (;;) {
    printf("명령을 입력해주세요 : ");
    /* Verify scanf */
    command = inspec_scanf();
    
    switch (command) {
      case 0:
      case 1:    
      // insert
        printf("추가할 데이터를 입력해주세요 : ");
        /* Verify scanf */
        input = inspec_scanf();
        Root = insertion(Root, input);
        break;

      case 2:
      // delete
      case 3:
      case 4:
      case 5:
      
      default:
        printf(">>>>> 잘못된 입력입니다 ! 정수만 입력해주세요 ! <<<<<\n");
        break;
    }
  }
  return 0;
}

//! - - - - - - - - - - - - - - function definition - - - - - - - - - - - - - - !//

/* Verification of the Input */
int inspec_scanf() {
  int input;
  while (scanf("%d", &input) != 1) {
    printf(">>>>> 잘못된 입력입니다 ! 정수만 입력해주세요 ! <<<<<\n");
    while (getchar() != '\n');
    printf("다시 입력해주세요 : ");
  }
  return input;
}

/* 0 : clearMemory & Shutdown */
void clearMemory() {

}

/* 1 : insert data to binary tree */
Node* insertion(Node* Root, int input) {
  if (Root == NULL) {
    Root = (Node*) malloc(sizeof(Node));
    Root->rightChild = Root->leftChild = NULL;
    Root->data = input;
    return Root;
  }
  else {
    if (input < Root->data) {
      Root->leftChild = insertion(Root->leftChild, input);
    } else {
      Root->rightChild = insertion(Root->rightChild, input);
    }
  }
  return Root;
}

/* 2 : delete data from binary tree */
Node* deletion(Node* Root, int input) {
  Node* tmpRoot = NULL;

  if (Root == NULL) return NULL;
  if (input < Root->data) Root->leftChild = deletion(Root->leftChild, input);
  else if (input > Root->data) Root->rightChild = deletion(Root->rightChild, input);
  else {
    if (Root->leftChild != NULL && Root->rightChild != NULL) {
      tmpRoot = search_min(Root->rightChild);
      Root->data = tmpRoot->data;
      Root->rightChild = delete(Root->rightChild, tmpRoot->data);
    }
    else {
      tmpRoot = (Root->rightChild == NULL) ? Root->rightChild : Root->leftChild;
      free(Root);
      return tmpRoot;
    }
  }
  return Root;
}

Node* search_min(Node*);
Node* search_max(Node*);
// Node* print(Node*);
Node* preO_print(Node*);
Node* InO_print(Node*);
Node* postO_print(Node*);



// Node* initNode(int input, Node* leftChild, Node* rightChild) {
//   Node* node = (Node*) malloc(sizeof(Node));
//   node -> data = input;
//   node -> leftChild = leftChild;
//   node -> rightChild = rightChild;
//   return node;
// }