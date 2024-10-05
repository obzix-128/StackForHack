#include "../include/CtorAndDtor.h"
#include "../include/DebugOnMode.h"
#include "../include/Verificator.h"


ErrorNumber StackCtor(StackInf* myStack)
{
    #ifdef _DEBUG_CHICK_CHIRICK
    myStack->full_data = (StackElem_t*) calloc(1, MIN_STACK_SIZE * sizeof(StackElem_t) +
                                                  SIZE_CHICK_CHIRICK * 2);
    if(myStack->full_data == NULL)
    {
        return CALLOC_ERROR;
    }
    myStack->data = (StackElem_t*)((char*)myStack->full_data + SIZE_CHICK_CHIRICK);
    #else
    myStack->data = (StackElem_t*) calloc(MIN_STACK_SIZE, sizeof(StackElem_t));
    if(myStack->data == NULL)
    {
        return CALLOC_ERROR;
    }
    #endif // _DEBUG_CHICK_CHIRICK

    myStack->size = 0;
    myStack->capacity = MIN_STACK_SIZE;

    for(int i = 0; i < myStack->capacity * (int)sizeof(StackElem_t); i++)
    {
        ((char*)(&myStack->data[myStack->size]))[i] = 52;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    StackChickChiric(myStack);
    #endif // _DEBUG_CHICK_CHIRICK

    #ifdef _DEBUG_HASH_DJB
    calculateHash(myStack);
    #endif // _DEBUG_HASH_DJB

    STACK_VERIFICATOR;

    return NO_ERROR;
}

ErrorNumber StackDtor(StackInf* myStack)
{
    STACK_VERIFICATOR;

    #ifdef _DEBUG_CHICK_CHIRICK
    free(myStack->full_data);
    #else
    free(myStack->data);
    #endif // _DEBUG_CHICK_CHIRICK

    *myStack = {};

    return NO_ERROR;
}
