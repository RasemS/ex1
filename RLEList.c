#include "RLEList.h"



struct RLEList_t{
    char character;
    struct RLEList_t* next;
};

RLEList RLEListCreate(){
    RLEList ptr=malloc(sizeof(*ptr));
    if(!ptr)
        return NULL;
    ptr->character='\0';
    ptr->next =NULL;
    return ptr;
}

void RLEListDestroy(RLEList list){
    if(list->next==NULL){
        free(list);
        return;
    }
        RLEListDestroy (list->next);
        free(list);
}


RLEListResult RLEListAppend(RLEList list, char value){
    if(list==NULL)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList nextList =RLEListCreate();
    if(!nextList)
        return RLE_LIST_OUT_OF_MEMORY;
    list->next=nextList;
    nextList->character=value;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    int counter=1;
    if(list==NULL){
        return -1;
    }
    while(list){
        list =list->next;
        counter++;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(index<0)
      return RLE_LIST_ERROR;
    if(list==NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tempPtr=list;
    for(int i=1;i<index;i++){
        if(tempPtr->next==NULL)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        tempPtr=tempPtr->next;
    }
    
    if(tempPtr->next==NULL)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    
    RLEList startOfConnectionPoint=tempPtr;
    tempPtr=tempPtr->next;
    startOfConnectionPoint->next=tempPtr->next;
    free(tempPtr);
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(list==NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    const int listSize= RLEListSize(list);
    if(index>listSize){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int currentIndex=0;
    while(list){
        if(currentIndex==index){
            *result=RLE_LIST_SUCCESS;
            return list->character;
        }
        list =list->next;
        currentIndex++;
    }
    return 0;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function){

    
    if(list==NULL)
        return RLE_LIST_NULL_ARGUMENT;
    do{
    int tempCharacter=map_function(list->character);
    list->character=tempCharacter;
    
    
    }while(list->next!=NULL);
   
    return RLE_LIST_SUCCESS;

}


char* RLEListExportToEncodedString(RLEList list, RLEListResult* result){
    if(list==NULL){
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char* resultString=malloc((sizeof(char))*(3*RLEListSize(list)+1));
    if(!resultString){
        *result=RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    char currentCharacter=list->character;
    int counter=0;
    int index=0;

    while(list!=NULL){
        
        if(currentCharacter!=list->character){
            resultString[index++]=currentCharacter;
            while(counter>0){
            resultString[index++]=(counter%10)+'0';
            counter/=10;
            }
            
            resultString[index++]='\n';
            currentCharacter=list->character;
            counter=1;

            }else 
                counter++;
        
        list=list->next;

    }

    resultString[index++]=currentCharacter;
    while(counter>0){
        resultString[index++]=(counter%10)+'0';
        counter/=10;
    }
            
    resultString[index++]='\n';

    resultString[index]='\0';
    *result =RLE_LIST_SUCCESS;

    return resultString;
}
