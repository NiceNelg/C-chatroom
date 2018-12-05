/**
 *  ͨ��˫������
 *
 *
 */
#ifndef _DLIST_H_
#define _DLIST_H_

//����ڵ�
typedef struct _DListNode{
    void *data;
    struct _DListNode *prev;
    struct _DListNode *next;
}DListNode;

//����
typedef struct _DList{
    //����ͷ
    DListNode *head;
    //����ǰ��¼�Ľڵ�
    DListNode *current;
    //����ǰ����
    int length;
}DList;

//�����������ֵ��ö�����ͣ�ֵ��1��ʼ
typedef enum _DListRet{
    DList_RET_OK = 1,
    DList_RET_FAULT,
    DList_RET_OOM
}DListRet;

typedef void *(*VisitFunc)(void *ctx, void *data);
typedef void (*DesFunc)(DList *dlist, int index);

//���Ժ�
#define return_val_if_fail(p, val) do {                                    \
            if(!(p)) {                                                     \
                printf("%s:%d "#p" failed\n", __func__, __LINE__);         \
                return val;                                                \
            }                                                              \
        }while(0)


//��������
DList *dlist_create();
//����������
int dlist_len(DList *dlist);
//��ȡָ��λ�õĽڵ�ֵ
DListNode *dlist_get(DList *dlist, int index);
//ɾ��ָ��λ�õĽڵ�
DListRet dlist_delete(DList *dlist, int index);
//��ӽڵ�
DListRet dlist_add(DList *dlist, int index, void *data);
//��������
void *dlist_foreach(DList *dlist, VisitFunc visit_func, void *ctx);
//��������
DListRet dlist_destroy(DList *dlist, DesFunc des_func, int index);

#endif
