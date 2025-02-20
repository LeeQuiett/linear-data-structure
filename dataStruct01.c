#include <stdio.h>
#include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

void loadList() {
	puts("=====loadList=====");

	FILE* fp = NULL;
	fopen_s(&fp, "listData.dat", "rb");
	if (fp == NULL) {
		perror("ERROR: Failed to open listData.dat");
		return 1;
	}

	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {
		printf("addr: [%p], age: %d, name: %s, phone: %s\n", &user, user.age, user.name, user.phone);
		memset(&user, 0, sizeof(USERDATA));
	}
	fclose(fp);
}

int main(void) {
	USERDATA user[4] = {
		{12, "lob", "010-1234-5678", NULL},
		{12, "onA", "010-1234-5678", NULL},
		{12, "beat", "010-1234-5678", NULL},
		{12, "Hecop", "010-1234-5678", NULL},
	};

	user[0].pNext = &user[1];
	user[1].pNext = &user[2];
	user[2].pNext = &user[3];
	
	USERDATA* pUser = &user[0];

	while (pUser != NULL)
	{
		printf("addr: [%p], age: %d, name: %s, phone: %s\n",pUser, pUser->age, pUser->name, pUser->phone);
		pUser = pUser->pNext;
	}

	FILE* fp = NULL;
	fopen_s(&fp, "listData.dat", "wb");
	if (fp == NULL) {
		perror("ERROR: Failed to open listData.dat");
		return 1;
	}

	pUser = &user[0];
	while (pUser != NULL) {
		fwrite(pUser, sizeof(USERDATA), 1, fp);
		pUser = pUser->pNext;
	}
	fclose(fp);

	loadList();

	return 0;
} 