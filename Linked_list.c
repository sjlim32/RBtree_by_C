/*
* 연결리스트
- 각 노드가 데이터와 포인터를 가지고 한 줄로 연결되어 있는 방식으로 데이터를 저장하는 자료구조
- 각 노드의 포인터가 다음이나 이전 노드와의 연결을 담당함
장점) 원하는 만큼 노드를 동적으로 추가 / 삭제 가능
단점) 배열처럼 메모리공간에 정렬되어 있지 않기 때문에, 배열의 인덱스처럼 특정 노드에 바로 접근 불가. 순차적으로 탐색함

* 자료 구조 구성
-----------------------------------------------------
|  <Head>                                           |
|   Data                                            |
|   Address   -> Data       <Tail>                  |
|                Adress  ->  Data                   |
|                            Address   -> NULL      |
-----------------------------------------------------
*/

//? - - - - - - - - - - - - - - Linked_list.c - - - - - - - - - - - - - - ?//

#include <stdio.h>        // printf, scanf func library
#include <stdlib.h>       // malloc, free func library
typedef struct NODE {
  int data;                 // Node's Data
  struct NODE* next;        // Self-reference Structure Pointer to direct Next node's address 
} Node;

//! - - - - - - - - - - - - - - function declaration - - - - - - - - - - - - - - !//

Node* Head = NULL;    // Head Node's pointer initialize NULL
Node* Tail = NULL;    // Tail Node's pointer initialize NULL

int inspect_cmd_scanf();
int inspect_inp_scanf();
void clearMemory();
void insertion(int);
void deletion(int);
void printer();
void searching(int);

//! - - - - - - - - - - - - - - main - - - - - - - - - - - - - - !//

int main() {
  int command;
  int input;

  /* init ment */
  printf("연결 리스트 생성 프로그램입니다 :)\n");
  printf("명령어 : 0 = 종료 / 1 = 자료 추가 / 2 = 자료 삭제 / 3 = 자료 검색 / 4 = 전체 리스트 출력 \n\n");

  /* loop select command*/
  for (;;) {
    printf("명령을 입력해주세요: ");
    command = inspect_cmd_scanf();

  /* do deletion, search, print if not NULL*/
    if (Head == NULL && 1 < command && 5 > command) {
        printf(">> 리스트가 비어있습니다 !\n");
        continue;
      }

  /*switch Start*/
    switch (command) {
      case 0:
      // exit
        clearMemory();
        printf(">> 메모리 할당을 정상적으로 해제한 뒤 종료하였습니다.\n");
        return 0;  

      case 1:
      // insert
        printf("추가할 자료를 입력해주세요 : ");
        input = inspect_inp_scanf();
        insertion(input);
        printf(">> 추가 완료!\n");
        break;

      case 2:
      // delete
        printf("삭제할 자료를 입력해주세요 : ");
        input = inspect_inp_scanf();
        deletion(input);
        break;

      case 3:
      // search
        printf("검색할 자료를 입력해주세요 : ");
        input = inspect_inp_scanf();
        searching(input);
        break; 

      case 4:
      // print all
        printer();
        break;

      default:
      // wrong input
        printf(">>>>> 잘못된 입력입니다 ! 0부터 4까지의 정수만 입력해주세요. <<<<<\n");
        break;
      }
      /* switch End */
      printf("\n");     // command seperation

  }                     // loop END

  return 0;             // program END
}

//! - - - - - - - - - - - - - - function definition - - - - - - - - - - - - - - !//

int inspect_cmd_scanf() {
  int input;
  while (scanf("%d", &input) != 1) {
    printf(">>>>> 잘못된 입력입니다 ! 0부터 4까지의 정수만 입력해주세요. <<<<<\n");
    while (getchar() != '\n');
    printf("명령을 다시 내려주세요 : ");
  }
  return input;
}

int inspect_inp_scanf() {
  int input;
  while (scanf("%d", &input) != 1) {
    printf(">>>>> 잘못된 입력입니다 ! 정수만 입력해주세요. <<<<<\n");
    while (getchar() != '\n');
    printf("처리하고 싶은 자료를 다시 입력해주세요 : ");
  }
  return input;
}

/* 0 : memory deallocation */
void clearMemory() {
  Node* target = Head;
  Node* temp = target;

  while(target != NULL) {
    temp = temp->next;
    free(target);
    target = temp;
  }
}

/* 1 : insertion */
void insertion(int input) {
  Node* newNode = (Node*)malloc(sizeof(Node));

  if (newNode != NULL) {
    newNode->data = input;
    newNode->next = NULL;
  } else return;
  
  if (Head == NULL) {    // if First Node
    Head = Tail = newNode;
  } else {
    Tail->next = newNode;
    Tail = newNode;
  }
}

/* 2 : deletion */
void deletion(int input) {
  Node* curr = Head;
  if (curr->data == input) {       // 삭제하는 값이 Head 노드일 경우
    Head = Head->next;
    free(curr);
    printf(">> Head 노드 삭제를 완료했습니다 !\n");
    return;
  }
  
  Node* pre = Head;
  while(curr->next != NULL) {     // 삭제하려는 값이 중간에 있을 경우
    if (curr->data == input) {
      pre->next = curr->next;
      free(curr);
      printf(">> 중간 노드 삭제를 완료했습니다 !\n");
      return;
    }
    pre = curr;
    curr = curr->next;
  }
  
  if (curr->next == NULL && curr->data == input) {   // 삭제하려는 값이 tail 노드일 경우
    pre->next = NULL;
    Tail = pre;
    free(curr);
    printf(">> Tail 노드 삭제를 완료했습니다 !\n");
    return;
  }
  printf(">> 리스트에 없는 값입니다.\n");
}

/* 3 : print all data */
void printer() {
  Node* curr = Head;
  printf("------리스트------\n");

  while(curr != NULL) {
    printf("%d\n", curr->data);
    curr = curr->next;
  }

  printf("------------------\n");
}

/* 4 : searching data */
void searching(int input) {
  Node* curr = Head;
  int order = 1;

  while(curr != NULL) {
    if (curr->data == input) {
      printf(">> 값을 찾았습니다 ! 순서 : %d 번째, 값 : %d\n", order, curr->data);
      return;
    }
    order += 1;
    curr = curr->next;
  }
  printf(">> 값을 찾지 못했습니다.\n");
}