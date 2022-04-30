/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);

int main(){
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- [조은지]  [2021076020] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	if(h->rlink==h){
		//헤드노드만 존재
		free(h); //헤드노드 메모리 할당 해제
		return 1;
	}

	listNode *p=h->rlink; //p가 첫번째 노드 가리킴
	listNode *prev=NULL; //삭제할 노드 포인터
	while(p!=NULL&&p!=h){  //p가 마지막 노드가 될 때까지
		prev=p; 
		p=p->rlink; //p가 다음 노드로 계속 이동
		free(prev); //노드 메모리 할당 해제
	}
	free(h); //헤드노드 메모리 할당 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //h->rlink가 첫번째 노드

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key); 
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i); //총 노드 개수


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; //h->rlink (list[0])부터 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if(h==NULL) return -1; //헤드노드가 아무것도 가리키지 않음 

	listNode *node=(listNode*)malloc(sizeof(listNode)); //삽입할 노드 메모리 할당
	node->key=key;
	node->rlink=node->llink=NULL;

	if(h->rlink==h){ // 첫번째 노드로 삽입
		//headnode 다음(오른쪽)에 삽입
		h->rlink=node; 
		h->llink=node; 
		node->rlink=h; 
		node->llink=h;
	}
	else { //마지막 노드로 삽입 
		h->llink->rlink=node; 
		node->rlink=h;
		node->llink=h->llink;
		h->llink=node;
		//headnode 이전(왼쪽)에 삽입 
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	
	if(h->llink==h||h==NULL){ //리스트에 노드가 없음, 헤드노드가 아무것도 가리키지 않음
		printf("nothing to delete.\n");
		return 1;
	}

	listNode *rm=h->llink; //삭제할 노드=h->llink (마지막노드)
	rm->llink->rlink=h; //마지막에서 2번째 노드가 다음 노드 = 첫번째 노드
	h->llink=rm->llink; //h->llink가 마지막에서 2번째 노드를 가리킴

	free(rm); //마지막 노드 메모리 할당 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode *node=(listNode*)malloc(sizeof(listNode)); //추가할 노드 할당
	node->key=key;
	node->rlink=node->llink=NULL;

	node->rlink=h->rlink; //node의 다음 노드는 2번째 노드
	h->rlink->llink=node; //2번째 노드의 이전 노드가 node (새로운 노드)
	h->rlink=node; //h 다음에 node
	node->llink=h; //node 이전에 h
	
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if(h==NULL||h->rlink==h){ //헤드노드가 아무것도 가리키지 않음, 리스트에 노드 없음
		printf("nothing to delete.\n");
		return 0;
	}

	//순서 1. 헤드노드<-> 2. 노드 <->3. 노드 ...

	listNode *rm=h->rlink; //헤드노드의 다음 노드 (2번째) 삭제하기
	rm->rlink->llink=h; //3번째 노드의 이전 노드가 헤드노드
	h->rlink=rm->rlink;//헤드노드의 다음노드로 3번째 노드

	free(rm); //rm 메모리 할당 해제
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	
	if(h->rlink==h||h==NULL){
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink;
	listNode *trail=h;
	listNode *middle =h;

	h->llink=h->rlink;

	while (n!=NULL&&n!=h){ 
		trail=middle; 
		middle=n; 
		n=n->rlink; //	n이 다음 노드로
		middle->rlink=trail; //middle 다음 노드로 trail
		middle->llink=n; //middle 이전 노드로 n
		//n이 헤드노드가 되면 벗어남 (n이 마지막 노드로)
	}
	h->rlink=middle; //middle이 첫번째 노드가 됨

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h==NULL) return -1; //헤드노드가 아무것도 가리키지 않음

	listNode *node=(listNode*)malloc(sizeof(listNode)); //삽입할 노드 메모리 할당
	node->key=key;
	node->llink=node->rlink=NULL;

	if(h->rlink==h) //리스트에 노드 없음
	{
		insertFirst(h,key); //첫번째로 노드 삽입
		return 1;
	}

	listNode*n=h->rlink; //비교할 노드 

	while(n!=NULL&&n!=h){ 
		if(n->key>=key){ //삽입 할 key 값이 기준노드 보다 작음
			if(n==h->rlink){  //n이 첫번째 노드 
			//삽입할 key가 첫노드 key 보다 작은 경우
				insertFirst(h,key);
				//첫번째에 새로운 노드 삽입
			}
			else { //n 이전에 삽입할 새로운 node가 옴
				node->rlink=n; 
				node->llink=n->llink; 
				n->llink->rlink=node;
				n->llink=node;
			}
			return 0;
		}
		n=n->rlink; // 삽입할 key 값이 비교할 key값보다 큼 -> n이 다음 노드로 -> 다시 비교
	}

	insertLast(h,key); //노드를 찾지 못함 마지막에 삽입
	return 0;
}



/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink==h||h==NULL){ //리스트에 노드가 없거나, 헤드노드가 아무것도 가리키지 않음
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n=h->rlink; //비교할 노드

	while(n!=NULL&&n!=h){
		if(n->key==key){ //key값이 같은 경우
			if(n==h->rlink) //비교한 노드가 첫번째 노드인 경우
				deleteFirst(h); //첫번째 노드 삭제
			else if(n->rlink==h) //비교한 노드가 마지막 노드인 경우
				deleteLast(h); //마지막 노드 삭제
			else{ //중간에 있는 노드인 경우
				n->llink->rlink=n->rlink; 
				n->rlink->llink=n->llink;
				//n을 기준으로 이전과 앞뒤가 연결
				free(n); //n 노드 삭제
			}
			return 0;

		}
		n=n->rlink; //n이 다음 노드로
	}

	printf("cannot finde the node for key=%d\n",key);
	return 0;
}


