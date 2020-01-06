/**                                                                             
 *  通用双向链表                                                                
 *                                                                              
 *                                                                              
 */                                                                             
#ifndef _DLIST_H_                                                               
#define _DLIST_H_                                                               
                                                                                
//链表节点                                                                      
typedef struct _DListNode{                                                      
    void *data;                                                                 
    struct _DListNode *prev;                                                    
    struct _DListNode *next;                                                    
}DListNode;                                                                     
                                                                                
//链表                                                                          
typedef struct _DList{                                                          
    //链表头                                                                    
    DListNode *head;                                                            
    //链表当前记录的节点                                                        
    DListNode *current;                                                         
    //链表当前长度                                                              
    int length;                                                                 
}DList;                                                                         
                                                                                
//链表操作返回值，枚举类型，值从1开始                                           
typedef enum _DListRet{                                                         
    DList_RET_OK = 1,                                                           
    DList_RET_FAULT,                                                            
    DList_RET_OOM                                                               
}DListRet;                                                                      
                                                                                
typedef void *(*VisitFunc)(void *ctx, void *data);                              
typedef void (*DesFunc)(DList *dlist, int index);                               
                                                                                
//测试宏                                                                        
#define return_val_if_fail(p, val) do {                                    \       
            if(!(p)) {                                                     \       
                printf("%s:%d "#p" failed\n", __func__, __LINE__);         \       
                return val;                                                \       
            }                                                              \       
        }while(0)                                                               
                                                                                
                                                                                
//创建链表                                                                      
DList *dlist_create();                                                          
//返回链表长度                                                                  
int dlist_len(DList *dlist);                                                    
//获取指定位置的节点值                                                          
DListNode *dlist_get(DList *dlist, int index);                                  
//删除指定位置的节点                                                            
DListRet dlist_delete(DList *dlist, int index);                                 
//添加节点                                                                      
DListRet dlist_add(DList *dlist, int index, void *data);                        
//遍历链表                                                                      
void *dlist_foreach(DList *dlist, VisitFunc visit_func, void *ctx);             
//销毁链表                                                                      
DListRet dlist_destroy(DList *dlist, DesFunc des_func, int index);              
                                                                                
#endif 