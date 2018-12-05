#include "dlist.h"
#include <malloc.h>
/**
 * @brief   dlist_alloc ����ڵ��ڴ�
 *
 * @return  
 */
static DListNode *dlist_alloc()
{
    return (DListNode *)calloc(1, sizeof(DListNode));
}

/**
 * @brief   dlist_create ��������
 *
 * @return  
 */
DList *dlist_create() 
{
    //calloc(�������,����Ԫ�ص��ڴ��С);��malloc()�Ĳ����calloc�ڷ����ڴ��ʱ��
    //�Զ����ڴ�ռ��ڵ�ֵ����Ϊ0������ʹ��memset()���ڴ�ռ��ֵ��0
    DList *dlist = (DList *)calloc(1, sizeof(DList));
    if(dlist == NULL) {
        return NULL;
    }
    //��¼�ṹ���ʼ����
    dlist->length = 0;
    //��¼����ͷ
    dlist->head = dlist_alloc();
    if(dlist->head == NULL) {
        return NULL;
    }
    dlist->current = dlist->head;

    return dlist;
}

/*
 *  
 */

/**
 * @brief   data_node_check �����������
 *
 * @param   Dlist *dlist
 * @param   void *data
 *
 * @return  
 */
int data_node_check(DList *dlist, void *data)
{
    int flag = 1;

    if(dlist == NULL) {
        return flag = 0;
    }

    if(data == NULL) {
        return flag = 0;
    }

    return flag;
}

/**
 * @brief   dlist_add ��ӽڵ�
 *
 * @param   DList *dlist
 * @param   int index
 * @param   void *data
 *
 * @return  
 */
DListRet dlist_add(DList *dlist, int index, void *data)
{
    int flag = 1;
    int len = 0;
    DListNode *node = NULL;
    DListNode *dlistnode = NULL;
    
    return_val_if_fail(dlist != NULL&&data != NULL, DList_RET_FAULT);

    flag = data_node_check(dlist, data);
    if(flag == 0) {
        return DList_RET_FAULT;
    }
    
    len = dlist->length;
    
    return_val_if_fail(index <= len, DList_RET_FAULT);

    
    //������ڵ��λ��Ҫ��������+1Ҫ����������������޷�����
    if(index > len) {
        return DList_RET_FAULT;
    }
    
    node = dlist_alloc();
    if(node == NULL) {
        return DList_RET_OOM;
    }
    
    node->data = data;

    //��ʼ������ͷ
    if(dlist->head == NULL) {
        dlist->head = dlistnode;
        dlist->current = dlist->head;
        dlist->length = 1;
        return DList_RET_OK;
    }

    //node->data = strcpy(data);
    //ͷ��
    if(index == 0) {
        dlistnode = dlist->head;
        dlist->head = node;
        dlist->head->prev = NULL;
        dlist->head->next = dlistnode;
        dlistnode->prev = dlist->head;
        dlist->current = node;
        node->prev = NULL;
        
        dlist->length++;

        return DList_RET_OK;
    } else if(index > 0) {
        dlistnode = dlist_get(dlist, index);
        if(dlistnode == NULL) {
            return DList_RET_FAULT;
        }
        dlistnode->prev->next = node;
        node->prev = dlistnode->prev;
        dlistnode->prev = node;
        node->next = dlistnode;
        dlist->current = node;
        
        dlist->length++;

        return DList_RET_OK;
    }

    return DList_RET_FAULT;
}

/**
 * @brief   dlist_delte ɾ��ָ��λ�õĽڵ�
 *
 * @param   string  dlist
 * @param   string  index
 *
 * @return  
 */
DListRet dlist_delte(DList *dlist, int index)
{
    int len = 0;
    DListNode *dlistnode = NULL;
    
    return_val_if_fail(dlist != NULL, DList_RET_FAULT);

    if(dlist == NULL) {
        return DList_RET_FAULT;
    }

    len = dlist_len(dlist);
    if(index >= len) {
        return DList_RET_FAULT;
    }

    if(index != 0) {
        dlistnode = dlist_get(dlist, index);
        if(dlistnode == NULL) {
            return DList_RET_FAULT;
        }
        dlistnode->next->prev = dlistnode->prev;
        dlistnode->prev->next = dlistnode->next;
        if(dlist->current == dlistnode) {
            dlist->current = dlistnode->next;
        }

        dlistnode->prev = NULL;
        dlistnode->next = NULL;
        dlistnode->data = NULL;
        
        free(dlistnode);

        dlistnode = NULL;
        dlist->length--;

        return DList_RET_OK;
    } else if(index == 0) {
        dlistnode = dlist->head;
        dlist->head = dlist->head->next;
        dlistnode->next->prev = NULL;
        
        if(dlist->current == dlistnode) {
            dlist->current = dlist->head;
        }
        
        dlistnode->prev = NULL;
        dlistnode->next = NULL;     
        dlistnode->data = NULL;
        

        free(dlistnode);

        dlistnode = NULL;
        dlist->length--;

        return DList_RET_OK;
    }

    return DList_RET_FAULT;
}

/**
 * @brief   dlist_get ��ȡָ���ڵ�
 *
 * @param   DList *dlist
 * @param   int  index
 *
 * @return  
 */
DListNode *dlist_get(DList *dlist, int index)
{
    return_val_if_fail(dlist != NULL, NULL);

    int n=0;
    DListNode *dlistnode = NULL;

    dlistnode = dlist->head;
    while(n < index) {
        dlistnode = dlistnode->next;
        n++;
    }

    return dlistnode;
}

/**
 * @brief   dlist_foreach ��������
 *
 * @param   string  dlist
 * @param   string  visit_func
 * @param   string  ctx
 *
 * @return  
 */
void *dlist_foreach(DList *dlist, VisitFunc visit_func, void *ctx)
{
    return_val_if_fail(dlist != NULL, NULL);

    DListNode *ipointer = NULL;
    void *retp = NULL;

    ipointer = dlist->head->next;
    for(ipointer; ipointer != NULL;) {
        retp = visit_func(ctx, ipointer->data);
        ipointer = ipointer->next;
    }
    return retp;
}

/**
 * @brief   dlist_len ��ȡ������
 *
 * @param   string  dlist
 *
 * @return  
 */
int dlist_len(DList *dlist)
{
    return_val_if_fail(dlist != NULL, DList_RET_FAULT);

    int len = 0;
    DListNode *dlistnode = NULL;

    dlistnode = dlist->head;
    while(dlistnode != NULL) {
        dlistnode = dlistnode->next;
        len++;
    }

    return len;
}

/**
 * @brief   dlist_destroy ��������
 *
 * @param   string  dlist
 * @param   string  des_func
 * @param   string  index
 *
 * @return  
 */
DListRet dlist_destroy(DList *dlist, DesFunc des_func, int index)
{
    DListNode *cursor = NULL;
    DListNode *dlistnode = NULL;

    cursor = dlist->head;
    if(des_func != NULL) {
        des_func(dlist, index);
    } else {
       while(cursor != NULL) {
           dlistnode = cursor;
           cursor = cursor->next;
           
           dlistnode->prev = NULL;
           dlistnode->next = NULL;
           dlistnode->data = NULL;

           free(dlistnode);

           dlistnode = NULL;
       } 
    }
    return DList_RET_OK;
}
