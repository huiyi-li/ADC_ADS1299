#include "main.h"
#include <stdlib.h>
#include <stdio.h>

// ��ʼ������
void initList(Node** head)
{
    *head = NULL;
}

// �������ݵ�����ĩβ
void insertData(Node** head, uint8_t* newData) 
{
    // �����½ڵ�
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
	{
        // �ڴ����ʧ��
        printf("Memory allocation failed!\n");
        return;
    }
    // �����ݸ��Ƶ��½ڵ�
    for (int i = 0; i < DATA_SIZE; i++) 
   {
        newNode->data[i] = newData[i];
    }
    newNode->next = NULL;

    if (*head == NULL) 
	{
        // ����Ϊ�գ��½ڵ㼴Ϊͷ�ڵ�
        *head = newNode;
    } 
	else 
	{
        // ���������ҵ�ĩβ�ڵ�
        Node* current = *head;
        while (current->next != NULL) 
		{
            current = current->next;
        }
        // ���½ڵ����ӵ�����ĩβ
        current->next = newNode;
    }
}

// ��������ȡ������
void extractData(Node** head, uint8_t* extractedData)
{
	
    if (*head == NULL)
	{
        // ����Ϊ��
        printf("List is empty!\n");
        return;
    }

    // ȡ��ͷ�ڵ������
    Node* temp = *head;
    for (int i = 0; i < DATA_SIZE; i++) 
    {
        extractedData[i] = temp->data[i];
    }

    // ����ͷָ��Ϊ��һ���ڵ�
    *head = (*head)->next;
     
//	u8 *data_test = temp->data;
//	free(data_test);
    // �ͷ��ڴ�
    free(temp);
	temp = NULL;
}

// ��������Ƿ�Ϊ��
int isEmpty(Node* head) 
{
    return head == NULL;
}

// ����������
int length(Node* head) 
{
    int len = 0;
    Node* current = head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}
