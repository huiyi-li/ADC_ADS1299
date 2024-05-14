#include "main.h"
#include <stdlib.h>
#include <stdio.h>

// 初始化链表
void initList(Node** head)
{
    *head = NULL;
}

// 插入数据到链表末尾
void insertData(Node** head, uint8_t* newData) 
{
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
	{
        // 内存分配失败
        printf("Memory allocation failed!\n");
        return;
    }
    // 将数据复制到新节点
    for (int i = 0; i < DATA_SIZE; i++) 
   {
        newNode->data[i] = newData[i];
    }
    newNode->next = NULL;

    if (*head == NULL) 
	{
        // 链表为空，新节点即为头节点
        *head = newNode;
    } 
	else 
	{
        // 遍历链表找到末尾节点
        Node* current = *head;
        while (current->next != NULL) 
		{
            current = current->next;
        }
        // 将新节点连接到链表末尾
        current->next = newNode;
    }
}

// 从链表中取出数据
void extractData(Node** head, uint8_t* extractedData)
{
	
    if (*head == NULL)
	{
        // 链表为空
        printf("List is empty!\n");
        return;
    }

    // 取出头节点的数据
    Node* temp = *head;
    for (int i = 0; i < DATA_SIZE; i++) 
    {
        extractedData[i] = temp->data[i];
    }

    // 更新头指针为下一个节点
    *head = (*head)->next;
     
//	u8 *data_test = temp->data;
//	free(data_test);
    // 释放内存
    free(temp);
	temp = NULL;
}

// 检查链表是否为空
int isEmpty(Node* head) 
{
    return head == NULL;
}

// 计算链表长度
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
