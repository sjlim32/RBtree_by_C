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
  struct NODE* parent;
  struct NODE* left;
  struct NODE* right;
} Node;


//! - - - - - - - - - - - - - - function declaration - - - - - - - - - - - - - - !//
/* define Binary Tree Node */
Node* Root;

// Node* initNode(int, Node*, Node*);
int input();
void clearMemory(Node*);
Node* insertion(Node*, Node*);
Node* deletion(Node*, int);
Node* search_min(Node*);
Node* search_max(Node*);
void print(Node*);
void preO_print(Node*);
void check_node(Node*, int);
// void* InO_print(Node*);
// void* postO_print(Node*);

//! - - - - - - - - - - - - - - main - - - - - - - - - - - - - - !//

int main() {
  int command;
  int data;
  Node* Result;

  /* init ment */
  printf("이진탐색트리 생성 프로그램입니다 :)\n");
  printf("명령어 : 0=종료 / 1=데이터 추가 / 2=데이터 삭제 / 3=최소값 출력 / 4=최대값 출력 / 5=전위순회 출력 / 6=노드 데이터 확인 \n\n");

  /* loop select command*/
  for (;;) {
    printf("명령을 입력해주세요 : ");
    /* Verify scanf */
    command = input();
    if (Root == NULL && 1 < command && 7 > command) {
      printf(">> 리스트가 비어있습니다 !\n");
      continue;
    }
    
    switch (command) {
      case 0:
      // free Tree
        if (Root != NULL) {
          clearMemory(Root);
        }
        printf("정상적으로 종료되었습니다.\n");
        return 0;

      case 1:    
      // insert
        printf("추가할 데이터를 입력해주세요 : ");
        /* Verify scanf */
        Node* leaf = (Node*) malloc(sizeof(Node));
        leaf->data = input();
        leaf->left = leaf->right = leaf->parent = NULL;
        Result = insertion(Root, leaf);
        if (Result != NULL) {
          printf("데이터가 정상적으로 추가되었습니다.\n");
        }
        break;

      case 2:
      // delete
        printf("삭제할 데이터를 입력해주세요 : ");
        /* Verify scanf */
        data = input();
        Root = deletion(Root, data);
        break;

      case 3:
      // search minimum
        Result = search_min(Root);
        if (Result == NULL) {
          printf("최소값이 없습니다.\n");
        } else {
          printf("최소값 : %d\n", Result->data);
        }
        break;

      case 4:
      // search maximum
        Result = search_max(Root);
        if (Result == NULL) {
          printf("최대값이 없습니다.\n");
        } else {
          printf("최대값 : %d\n", Result->data);
        }
        break;

      case 5:
      // print tree on preorder's way
        preO_print(Root);
        break;

      case 6:
      // check parent, data
        printf("검색할 데이터를 입력해주세요 : ");
        data = input();
        check_node(Root, data);
        break;

      default:
        printf(">>>>> 잘못된 입력입니다 ! 정수만 입력해주세요 ! <<<<<\n");
        break;
    }
  }
  return 0;
}

//! - - - - - - - - - - - - - - function definition - - - - - - - - - - - - - - !//

/* Verification of the Input */
int input() {
  int input;
  while (scanf("%d", &input) != 1) {
    printf(">>>>> 잘못된 입력입니다 ! 정수만 입력해주세요 ! <<<<<\n");
    while (getchar() != '\n');
    printf("다시 입력해주세요 : ");
  }
  return input;
}

/* 0 : clearMemory & Shutdown */
void clearMemory(Node* node) {
  if (node->right != NULL) {
    clearMemory(node->right);
  } 
  if (node->left != NULL) {
    clearMemory(node->left);
  }
  free(node);
}

/* 1 : insert data to binary tree */
Node* insertion(Node* root, Node* node) {
  if (Root == NULL) {
  // 처음 생성된 트리이므로 루트 노드 생성
    Root = node;
    Root->right = Root->left = Root->parent = NULL;
    return Root;
  }
  // *root 인자가 값을 가지고 있으면, insertion 재귀호출, 값이 없으면 return

  if (root != NULL) {
    if (node->data < root->data) {
      if (root->left == NULL) {
        node->parent = root;
        root->left = node;
        return root;
      } 
      else {
        root->left = insertion(root->left, node);
        }
    }
    else if (node->data > root->data) {
      if (root->right == NULL) {
        node->parent = root;
        root->right = node;
        return root;
      }
      root->right = insertion(root->right, node);
    }
  }
  return root;
}

/* 2 : delete data from binary tree */
Node* deletion(Node* node, int input) {
  if (node == NULL) return NULL;

  // 현재 내 노드가 삭제하고자하는 값과 일치할 때
  if (node->data == input) {
    Node* deleteNode = node;
    
    // 왼쪽 자식과 오른쪽 자식이 둘 다 없을 때
    if (node->left == NULL && node->right == NULL) {
      node = NULL;
    }
    // 왼쪽 자식만 있고, 오른쪽 자식은 없을 때
    else if (node->left != NULL && node->right == NULL) {
      node = node->left;
    }
    // 왼쪽 자식은 없고 오른쪽 자식만 있을 때
    else if (node->left == NULL && node->right != NULL) {
      node = node->right;
    }
    // 양쪽 자식이 모두 존재할 때, 오른쪽 자식노드 중 가장 작은 값을 찾는다( = minNode ) minNode 에 deleteNode 의 자식들을 연결해줌
    // 만약 minNode의 오른쪽 자식이 존재하면, 가져오기 전에 오른쪽 자식을 minNode 의 부모노드와 연결함
    else {
      Node* minNode = search_min(node->right);
      if (minNode->right != NULL) minNode->parent->left = minNode->right;     // minNode->right 가 있을 때, parent 에게 전달
      
    }

    free(deleteNode);
    return node;
  }

  else {
    if (node->data > input) {
      node->left = deletion(node->left, input);
    }
    else {
      node->right = deletion(node->right, input);
    }
  }

  return node;
}

/* 3 : search minimum */
Node* search_min(Node* node) {
  Node* Min = NULL;
  while(Min->left != NULL) Min = Min->left;

  return Min;
}

/* 4 : search maximum */
Node* search_max(Node* node) {
  Node* Max = node;
  while(Max->right != NULL) Max = Max->right;

  return Max;
}

/* 5: print all tree node */
void preO_print(Node* node) {
  if (node == NULL) {
    return;
  }
  printf("%d\n", node->data);
  print(node->left);
  print(node->right);
}

void print(Node* node) {
  if(node == NULL) {
    return;
  }
  printf("%d\n", node->data);
  print(node->left);
  print(node->right);
}

/* 6 : check node's data */
void check_node(Node* node, int input) {
  if (node == NULL) {
    printf("값을 찾을 수 없습니다.\n");
    return;
  }

  if (node->data == input) {
    if (node->parent == NULL) {
      printf("루트 노드입니다. 노드의 값: %d \n", Root->data);
      return;
    } else {
      printf("노드의 부모: %d / 노드의 값: %d \n", node->parent->data, node->data);
      return;
    }
  }
  else {
    if (node->data > input) {
      check_node(node->left, input);
    } 
    else {
      check_node(node->right, input);
    }
  }
}

// void* InO_print(Node*);
// void* postO_print(Node*);



// Node* initNode(int input, Node* left, Node* right) {
//   Node* node = (Node*) malloc(sizeof(Node));
//   node -> data = input;
//   node -> left = left;
//   node -> right = right;
//   return node;
// }