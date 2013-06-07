#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>

#define PASSWORD_SIZE 4
#define TRUE 1
#define FALSE 0

typedef struct contact  // 주소록 정보
{
  char lastName[5];  	//성
  char firstName[15];	//(성 제외)이름
  char position[20];	//직책
  char department[20];	//부서
  char company[20];		//회사명
  char address[60];		//주소
  char homePhone[11];	//전화번호
  char faxNumber[11];	//팩스번호
  char mobilePhone[12];	//휴대전화번호
  char email[40];		//E-mail
  char homepage[50];	//홈페이지
  char CheckedNum;		//선택한 번호
} Contact;

int loginState = FALSE;

typedef struct node
{
  Contact sContact;
  struct node *next;
} Node;

Node *head;
Node *tail;

FILE* fp = NULL;
char buff[PASSWORD_SIZE+1];
char inputPassword[PASSWORD_SIZE+1];

int isEmpty();
Node *isFull();
int login();
int isValidPassword();
void linkedListInit();
void viewAllContacts();
void printContactList();
void addContact();
void modifyAddress();
void deleteAddress();
void findAddress();
void changePassword();
void logout();
int printMainMenu();
void changePassword();

int isEmpty()
{
	if( head->next == tail ) 
		return TRUE;
	else return FALSE;
}

Node *isFull()
{
	Node *p = (Node *)malloc(sizeof(Node));
	if(p == NULL)
		return NULL;
	else return p;
}

int login()
{	
	printf("사용자의 비밀번호를 입력하세요: ");
	gets(inputPassword);

	while( isValidPassword() == FALSE ) {
		printf("비밀번호는 네 자리로 입력해주세요\n\n");
		printf("사용자의 비밀번호를 입력하세요: ");
		gets(inputPassword); }

	if( strcmp(buff,inputPassword) != 0 ) {
		printf("비밀번호가 일치하지 않습니다.\n\n");
		return FALSE; }
	else return TRUE;

}

int isValidPassword()
{
	int isValid;
	
	if(strlen(inputPassword) != PASSWORD_SIZE)
		isValid = FALSE;
	else isValid = TRUE;

	return isValid;
}

void linkedListInit()
{
	head = (Node *)malloc(sizeof(Node));
	tail = (Node *)malloc(sizeof(Node));

	head->next = tail;
	tail->next = tail;
}

void viewAllContacts()
{
	Node *p;
	int k=1;

	p = head -> next;
	
	system("cls");
	if( isEmpty() == TRUE )
	{
		printf("고객 정보가 존재하지 않습니다. \n");
	}
	else
	{
		printf("----------------------------------\n");
		printf("번호 성\t이름\t휴대전화번호\n");
		while( p!=tail )
		{
			printf(" %d %4s %4s %14s\n", k++, p->sContact.lastName, p->sContact.firstName, p->sContact.mobilePhone);
			p = p->next;
		}
		printf("----------------------------------\n");
	}
	
	getch();
}

void addContact()
{
	Node *t;
	Node *searchNode;
	Node *searchPreNode;
	Contact pContact;
	char temp;
	
	searchNode = searchPreNode = head->next;
	t = isFull();

	if( t == NULL ) {
		printf("더 이상 저장할 공간이 없습니다.\n");
		system("cls");
	}
	
	system("cls"); ///
	printf("주소록 추가\n");
	printf("----------------------------------\n");
	printf("1. 성 : "); gets(pContact.lastName);
	printf("2. (성 제외) 이름 : "); gets(pContact.firstName);
	printf("3. 직책 : "); gets(pContact.position);
	printf("4. 부서 : "); gets(pContact.department);
	printf("5. 회사명 : "); gets(pContact.company);
	printf("6. 주소 : "); gets(pContact.address);
	printf("7. 전화번호 : "); gets(pContact.homePhone);
	printf("8. 팩스번호 : "); gets(pContact.faxNumber);
	printf("9. 휴대전화번호 : "); gets(pContact.mobilePhone);
	printf("10. E-mail : "); gets(pContact.email);
	printf("11. 홈페이지 : "); gets(pContact.homepage);
	printf("----------------------------------\n\n");
	
	t->sContact = pContact;
	
	printf("정말로 등록하시겠습니까? (y/n) : ");
	temp = getch();
	
	if(temp == 'y' || temp == 'Y')
	{
		if( isEmpty() == TRUE )
		{
			head->next = t;
			t->next = tail; //데이터가 없을 경우, head와 tail 사이에 직접 삽입
		}
		else
		{
			while( searchNode != tail ) {
				if((strcmp(searchNode->sContact.lastName,t->sContact.lastName)<0) ||
					((strcmp(searchNode->sContact.lastName,t->sContact.lastName)==0) && (strcmp(searchNode->sContact.firstName,t->sContact.firstName)<0)))
				{	searchPreNode = searchNode;
					searchNode = searchNode->next;}
				else break;}
			if( searchNode == head->next ) {	// 입력된 정보가 가장 처음에 삽입되어야 할 경우
				t->next = head->next;
				head->next = t;
			}
			else if( searchNode == tail ) {	// 입력된 정보가 가장 마지막에 삽입되어야 할 경우
				searchPreNode->next = t;
				t->next = tail;
			}
			else {							// 입력된 정보가 중간에 삽입되어야 할 경우
				t->next = searchNode;
				searchPreNode->next = t;
			}
		}
	
		system("cls");
		printf("등록이 정상적으로 완료되었습니다.\n");
	}
	else
	{
		free(t);
		system("cls");
		printf("등록을 취소하였습니다.\n");
	}
	Sleep(1000);	//1초(1000) 딜레이	
}
/*
void modifyAddress(){
	Node *t;
	Contact *pContact;
	char temp;
	char lastName[5];	//성
	char firstName[15];	//(성 제외)이름
	char position[20];		//직책
	char department[20];	//부서
	char company[20];	//회사명
	char homeAddress[60];	//주소
	char homePhone[11];	//전화번호
	char faxNumber[11];	//팩스번호
	char mobilePhone[12];	//휴대전화번호
	char email[40];		//E-mail
	char homepage[50];	//홈페이지
	char CheckedNum;
	
	t = isFull()
	if( t == NULL ) {
		printf("더 이상 저장할 공간이 없습니다.\n");
		system("cls");
	}
	
	pContact = (Contact *)malloc(sizeof(Contact));
	char SearchName;


	t = (node *)malloc(sizeof(node));
	pContact = (address *)malloc(sizeof(address));
	
	system("cls");
	
	searchpersonMenu();	//한글자이름명단

	printf("출력된 항목 중 수정하고자 하는 이름을 입력하세요\n");
	scanf//이름 받기
	//받은 이름에 대하여 

	printf("어떤 항목을 수정하겠습니까\n");
	scanf("%s",CheckedNum);
	switch(CheckedNum) {
		case '1':
		printf("1. 성 : "); gets("%s", pContact->lastName); break;
		case '2':
		printf("2. (성 제외) 이름 : "); gets("%s", pContact->firstName); break;
		case '3':
		printf("3. 직책 : "); gets("%s", pContact->position); break;
		case '4':
		printf("4. 부서 : "); gets("%s", pContact->department); break;
		case '5':
		printf("5. 회사명 : "); gets("%s", pContact->company); break;
		case '6':
		printf("6. 주소 : "); gets("%s", pContact->homeAddress); break;
		case '7':
		printf("7. 전화번호 : "); gets("%s", pContact->homePhone); break;
		case '8':
		printf("8. 팩스번호 : "); gets("%s", pContact->faxNumber); break;
		case '9':
		printf("9. 휴대전화번호 : "); gets("%s", pContact->mobilePhone); break;
		case '10':
		printf("10. E-mail : "); gets("%s", pContact->email); break;
		case '11':
		printf("11. 홈페이지 : "); gets("%s", pContact->homepage); break;
	}

	printf("정말로 수정하시겠습니까? (y/n) : "); //수정해야 함 
	temp = getch();
	
	if(temp == 'y' || temp == 'Y')
	{
		if(head->next == tail)
		{
			t->next = tail; //데이터가 없을 경우, head와 tail 사이에 직접 삽입
		}
		else
		{
			t->next = head->next;
		}
		head->next = t;
		system("cls");
		printf("수정이 정상적으로 완료되었습니다.\n");
	}
	else
	{
		free(t);
		free(pContact);
		system("cls");
		printf("수정을 취소하였습니다.\n");
	}
	Sleep(1000);	//1초(1000) 딜레이	
}

void deleteAddress(){
	node *t;
	address *pContact;
	char temp;
	char lastName[5];	//성
	char firstName[15];	//(성 제외)이름
	char position[20];		//직책
	char department[20];	//부서
	char company[20];	//회사명
	char homeAddress[60];	//주소
	char homePhone[11];	//전화번호
	char faxNumber[11];	//팩스번호
	char mobilePhone[12];	//휴대전화번호
	char email[40];		//E-mail
	char homepage[50];	//홈페이지
	char CheckedNum;

	t = (node *)malloc(sizeof(node));
	pContact = (address *)malloc(sizeof(address));
	
	system("cls");
	
	t->sAddress = pContact;
	
	printf("연락처 하나만 삭제하려면 1을, 전체 주소록을 삭제하려면 2를 눌러주세요");
	scanf("%s",CheckedNum);
	switch(CheckedNum) {
		case '1':
			searchpersonMenu();//한글자이름명단
			break;
		case '2':
			//모두 삭제
			break;
	}
	printf("정말로 삭제하시겠습니까? (y/n) : ");
	temp = getch();
	
	if(temp == 'y' || temp == 'Y') //수정해야 함 
	{
		if(head->next == tail)
		{
			t->next = tail; //데이터가 없을 경우, head와 tail 사이에 직접 삽입
		}
		else
		{
			t->next = head->next;
		}
		head->next = t;
		system("cls");
		printf("삭제가 정상적으로 완료되었습니다.\n");
	}
	else
	{
		free(t);
		free(pContact);
		system("cls");
		printf("삭제를 취소하였습니다.\n");
	}
	Sleep(1000);	//1초(1000) 딜레이	
}
void findAddress(){

	searchpersonMenu();
	
	scanf //찾을 이름 받기 
	printContactList();	//리스트 출력
}

void changePassword(){;}
void Logout(){;}

void searchpersonMenu(){

char *SearchName;
SearchName = (char*)malloc(sizeof(char)*2);
1. 한 글자 입력받음
2. 주소록에 저장되어 있던 사람과 대조
3. 입력받은 글자가 포함된 사람 명단 출력
return 명단;

	사용자가 어떤 사람에 대해 저장을 했는지 여부를 알기 위해 숫자 ‘5’를 누르고 ‘Enter’를 쳤다. 
	화면에 검색하고자 하는 이름의 한 글자를 입력하라고 하길래 ‘강’을 쓰고 ‘Enter’를 쳤다. 
	화면에는 ‘강’을 포함한 이름을 가진 목록들이 나온다.

printf("수정하고자 하는 이름 중 한 글자를 입력하세요\n");
	scanf("%s",SearchName);
	if (SearchName==*lastName){}
	if (SearchName==*firstName){}
	//출력


}*/

void changePassword()
{
	char input1[PASSWORD_SIZE+1], input2[PASSWORD_SIZE+1];

	printf("현재 비밀번호를 입력하세요 : ");
	gets(inputPassword);

	while( isValidPassword() == FALSE ) {
		printf("비밀번호는 네 자리로 입력해주세요\n");
		printf("사용자의 비밀번호를 입력하세요: ");
		gets(inputPassword); }

	if( strcmp(buff,inputPassword) != 0 ) {
		printf("비밀번호가 일치하지 않습니다.\n");
		Sleep(1000);
		return ;}

	printf("1. 비밀번호 입력(4자리) : ");
	gets(input1);
	printf("2. 비밀번호 확인(4자리) : ");
	gets(input2);

	if(strcmp(input1,input2) != 0) {
		printf("입력하신 두 비밀번호가 일치하지 않습니다.\n");
		Sleep(1000);
		return ;}
	else {
		printf("%s를 비밀번호로 설정합니다.\n",input1);
		fseek(fp,0,SEEK_SET);
		fputs(input1, fp);
		Sleep(1000);
	}
}

void logout()
{
	system("cls");
	printf("\n로그아웃 되었습니다.\n사용해 주셔서 감사합니다.");
	Sleep(2000);
	system("cls");
}

int printMainMenu()
{
	int menuChoice;

	system("cls");
	printf("메인 메뉴\n");
	printf("----------------------------------\n");
	printf("1. 주소록 전체보기\n");
	printf("2. 주소록 추가\n");
	printf("3. 주소록 수정\n");
	printf("4. 주소록 삭제\n");
	printf("5. 주소록 검색\n");
	printf("6. 비밀번호 변경\n");
	printf("7. 로그아웃\n");
	printf("8. 종료\n");
	printf("----------------------------------\n\n");
	printf("번호를 입력하세요(1~8) : ");
	scanf("%d", &menuChoice);
	fflush(stdin); //버퍼 삭제
	return menuChoice;
}

int main(void)
{
	int menuChoice = 0;

	fp = fopen("address_book.txt","r+");
	if(fp == NULL) {
		printf("일치하는 주소록이 없습니다.\n");
		return ;}
			
label :
	fgets(buff, sizeof(int)*PASSWORD_SIZE, fp);

	printf("주소록 시스템에 오신걸 환영합니다.\n\n");

	do { loginState = login(); }while( loginState == FALSE );

	printf("로그인에 성공하였습니다!\n\n");
	Sleep(1000);

	linkedListInit();	//연결리스트 초기화
		
	while( loginState == TRUE && menuChoice != 8 ) 
	{
		menuChoice = printMainMenu();
		if(!(menuChoice >=1 && menuChoice <=8))
		{
			continue;
		}
		
		switch(menuChoice) 
		{
		case 1: 
		  viewAllContacts(); //주소록 전체보기
		  break;
		case 2: 
		  addContact(); //주소록 추가
		  break;
	/*	case 3: 
		  modifyAddress(); //주소록 수정
		  break;
		case 4: 
		  deleteAddress(); //주소록 삭제
		  break;
		case 5: 
		  findAddress(); //주소록 검색
		  break;*/
		case 6: 
		  changePassword(); //비밀번호 변경
		  break;
		case 7: 
		  logout(); //로그아웃
		  goto label;
		  break;
		case 8: 
		  exit(1); //종료
		  break;
		default: printf("잘못 입력하셨습니다.\n");
		}
	}

	fclose(fp);
	return 0;
}


