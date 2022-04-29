#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { //노드 구조체 생성
	int key; //int형 key
	struct Node* llink; //노드구조체형 포인터 llink
	struct Node* rlink; //노드구조체형 포인터 rlink
} listNode; //listNode로 호출가능

/* 함수 리스트 */
int initialize(listNode** h); //int형 initialize 함수 이중포인터listNode h를 인자로 받아온다
int freeList(listNode* h); //int형 freeList 함수 포인터listNode h를 인자로 받아온다
int insertLast(listNode* h, int key); //int형 insertLast 함수 포인터listNode h, int형 key를 인자로 받아온다
int deleteLast(listNode* h);  //int형 deleteLast 함수  포인터listNode h를 인자로 받아온다
int insertFirst(listNode* h, int key); //int형 insertFirst 함수 포인터listNode h, int형 key를 인자로 받아온다
int deleteFirst(listNode* h); //int형 deleteFirst 함수 포인터listNode h를 인자로 받아온다
int invertList(listNode* h); //int형 invertList 함수 포인터listNode h를 인자로 받아온다

int insertNode(listNode* h, int key); //int형 insertNode 함수 포인터listNode h, int형 key를 인자로 받아온다
int deleteNode(listNode* h, int key); //int형 deleteNode 함수 포인터listNode h, int형 key를 인자로 받아온다

void printList(listNode* h); //void형 printList 함수 포인터listNode h를 인자로 받아온다



int main()
{
	char command; //command받아올 char형 변수
	int key; //int형 key변수
	listNode* headnode=NULL; //listNode형 포인터 headnode를 생성하고 NULL로 초기화함

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
		scanf(" %c", &command); //command입력 받아옴

		switch(command) { //command를 받아올 switch
		case 'z': case 'Z': //z일경우
			initialize(&headnode); //initialize함수 호출 headnode주소 인자로 받아옴
			break;
		case 'p': case 'P': //p일경우
			printList(headnode); //printList함수 호출 headnode 인자로 받아옴
			break;
		case 'i': case 'I': //i일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아옴
			insertNode(headnode, key); //insertNode함수 호출 headnode, key 인자로 받아옴
			break;
		case 'd': case 'D': //d일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아옴
			deleteNode(headnode, key); //deleteNode함수 호출 headnode, key 인자로 받아옴
			break;
		case 'n': case 'N': //n일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아옴
			insertLast(headnode, key); //insertLast함수 호출 headnode, key 인자로 받아옴
			break;
		case 'e': case 'E': //e일경우
			deleteLast(headnode); //deleteLast함수 호출 headnode 인자로 받아옴
			break;
		case 'f': case 'F': //f일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아옴
			insertFirst(headnode, key); //insertFirst함수 호출 headnode, key 인자로 받아옴
			break;
		case 't': case 'T': //t일경우
			deleteFirst(headnode); //deleteFirst함수 호출 headnode 인자로 받아옴
			break;
		case 'r': case 'R': //r일경우
			invertList(headnode); //invertList함수 호출 headnode 인자로 받아옴
			break;
		case 'q': case 'Q': //q일경우
			freeList(headnode); //freeList함수 호출 headnode 인자로 받아옴
			break;
		default: //위 case와 다른거일경우 오류 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 아닐경우 계속

	return 1;
}


int initialize(listNode** h) { //받아온 listnode형 포인터 h에 동적할당을 해주는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; //오른쪽 링크엔 h*주소
	(*h)->llink = *h; //왼쪽 링크엔 h*주소
	(*h)->key = -9999; //key값을 -9999를 넣어준다.
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	if(h->rlink == h)//만약 head노드 밖에 없다면
	{
		free(h); //head노드 동적할당 해제
		return 1;
	}

	listNode* p = h->rlink; //listNode 포인터 p에 h의 rlink를 값을 넣는다

	listNode* prev = NULL; //listNode 포인터 prev를 NULL로 초기화
	while(p != NULL && p != h) { //p가 NULL, h가 아니라면 루프
		prev = p; //prev에 p값 넣어줌
		p = p->rlink; //p에 p의 rlink넣어줌(오른쪽 노드로 이동)
		free(prev); //prev의 동적할당 해제
	}
	free(h); //a마지막남음 head 노드 동적할당 해제
	return 0;
}



void printList(listNode* h) { //list출력 함수
	int i = 0; //int형 변수 i 를 0으로 초기화
	listNode* p; //listNode형 포인터 p 생성

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL이면출력할 것이 없다는 오류
		printf("Nothing to print....\n"); 
		return;
	}

	p = h->rlink; //p는 h의 rlink가됨

	while(p != NULL && p != h) { //p가 NULL 혹은 h가 아니라면 루프
		printf("[ [%d]=%d ] ", i, p->key);  //i번째에 p의key값 이런 문장을 을 출력
		p = p->rlink; //p에 p의 rlink를 넣어줌(오른쪽노드로 이중)
		i++; //i값 증가
	}
	printf("  items = %d\n", i); //몇개의 노드가 있는지 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //head노드에 어떤값이 있는지 출력

	i = 0; //i를  0으로 초기화 
	p = h->rlink; //p를 h의 rlink로 함
	while(p != NULL && p != h) { //p가 NULL 혹은 h가 아니라면 루프
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //i번째 노드에 어떤값이 있는지 출력
		p = p->rlink; //p에 p의 rlink값을 넣어줌 
		i++; //i값 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //해드노드가 비었으면 동작안함

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node를  동적할당으로 생성
	node->key = key; //노드의 key값을 받아론 key로
	node->rlink = NULL; //노드들의 왼링크 오른링크를 NULL로 초기화
	node->llink = NULL;

	if (h->rlink == h) /* 첫 노드로 삽입 */ //해드노드만 존재하는 링크라면
	{
		h->rlink = node; //해드노드의 rlink를 node주소로
		h->llink = node; //해드노드의 llink를 node주소로
		node->rlink = h; //노드의 rlink를 해드주소로
		node->llink = h; //노드의 llink를 해드주소로
	} else { //해드노드말고 다른 주소도 존재한다면
		h->llink->rlink = node; //h의 llink주소의 노드의 rlink를 node값으로 넣어줌(해드노드의 왼쪽에에 노드를 넣는다)
		node->llink = h->llink; //node의 왼쪽주소에 해드노드의 왼쪽 주소를 넣는다.
		h->llink = node; //해드노드의의 왼쪽주소에 node의 주소를 넣는다.
		node->rlink = h; //node의 오른쪽 주소에 해드노드의 주소를 넣는다.
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //링크가 비었으면
	{
		printf("nothing to delete.\n"); //삭제할것이 없다는 오류
		return 1;
	}

	listNode* nodetoremove = h->llink; //제거할 노드를 담을 포인터 지정후 해드노드의 왼쪽 주소 넣어줌

	/* link 정리 */
	nodetoremove->llink->rlink = h; //제거할 노드의 왼쪽주소의 노드의 오른쪽주소를 해드노드의 주소로 변경
	h->llink = nodetoremove->llink; //해드노드의 왼쪽주소에 제거할주소의 왼쪽주소를 넣어줌

	free(nodetoremove); //연결되지 않은 제거될 노드를 동적할당 하제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //연결해줄 node를 동적할당
	node->key = key; //node의 key값을 받아온 key로 설정
	node->rlink = NULL; //오른쪽왼쪽 주소를 NULL로 초기화
	node->llink = NULL;


	node->rlink = h->rlink; //노드의 오른쪽주소를 해드노드의 오른쪽주소로
	h->rlink->llink = node; //해드노드의 오른쪽주소의 왼쪽주소를 노드로
	node->llink = h; //노드의 왼쪽주소를 해드노드로
	h->rlink = node; //해드노드의 오른쪽주소를 노드로


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) { 

	if (h == NULL || h->rlink == h) //링크가 비었으면 삭제할것이 없다는 오류
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //삭제할 노드저장할 포인터 생성후 해드노드의 오른쪽 노드 주소 넣어줌

	/* link 정리 */
	nodetoremove->rlink->llink = h; //삭제노드의 오른쪽주소의 왼쪽주소를 해드노드로만들음 (오른쪽에서 2번째 노드에 해드노드 주소넣음)
	h->rlink = nodetoremove->rlink; //해드노드의 으론쪽주소를 삭제할 노드의 오른쪽주소로 변경함

	free(nodetoremove); //아무런 노드랑도 연결안된 삭제할 노드 동적할당 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //링크가 비었으면 비었다는 오류 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //n 포인터 생성후 h의 오른쪽 링크 넣어줌
	listNode *trail = h; //trail포인터 생성후 해드노드 주소 넣어줌
	listNode *middle = h; //middle포인터 생성후 해드노드 주소 넣어줌

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;  //해드노드의 왼쪽노드는 해드노드의 오른쪽 노드가됨

	while(n != NULL && n != h){ //n이 비거나 해드노드가 아닐떄까지 반복
		trail = middle; //trail에 middle 값 넣어줌
		middle = n; //middle에 n값 넣어줌
		n = n->rlink; //n에 n의 오른쪽 링크 넣어줌
		middle->rlink = trail; //middle의 오른쪽 링크를 trail로변경
		middle->llink = n; //middle의 왼쪽링크를 n으로 변경
	}

	h->rlink = middle; //h의 오른쪽링크를 middle로 변경

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h가 비었다면 tlfgoddksgka

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node를 동적할당으로 생성
	node->key = key; //노드의 key값에 받아온 key값 넣어줌
	node->llink = node->rlink = NULL; //노드의 왼오링크를 NULL로 초기화

	if (h->rlink == h) //링크가 해드노드 하나라면 
	{
		insertFirst(h, key); //그냥 1개의 노드를 추가함
		return 1;
	}

	listNode* n = h->rlink; //n포인터에 해드노드의 오른쪽링크를 넣어줌

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 NULL이거나 해드노드가 아닐때까지
		if(n->key >= key) { //n의 key값이 받아온 key값보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //해드노드의 오른쪽링크가 n일경우(key값이 가장 작다면)
				insertFirst(h, key); // 그냥 1개의 노드를 추가함
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //노드의 오른쪽링크를 n으로
				node->llink = n->llink; //노드의 왼쪽링크를 n의 왼쪽링크로
				n->llink->rlink = node; //n의 왼쪽링크의 오른쪽링크를 node로
				n->llink = node; //n의 왼쪽링크를 node로 
			}
			return 0;
		}

		n = n->rlink; //n을 n의 rlink로 변경
	}//반복

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) //링크가 비었으면 비었다는 오류출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //n 포인터 생성 h의 왼쪽링크를 n으로 설정

	while(n != NULL && n != h) { //n이 NULL이거나 h일떄까지 반복
		if(n->key == key) { //n의 key값이 받아온 key값과 같은경우
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫번째 노드 삭제 함수 호출
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 왼쪽노드의 오른쪽링크를 n의 오른쪽링크로 변경
				n->rlink->llink = n->llink; //n의 오른쪽노드의 왼쪽링크를 n의 왼쪽링크로 변경
				free(n); //n의 동적할당을 해제
			}
			return 0;
		}

		n = n->rlink; //n의 왼쪽링크를 n에다가 넣어줌
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


