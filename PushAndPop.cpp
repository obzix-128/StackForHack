#include "../include/PushAndPop.h"
#include "../include/Verificator.h"
#include "../include/DebugOnMode.h"


ErrorNumber StackPush(StackInf* myStack, StackElem_t element_value)
{
    ErrorNumber check_error = NO_ERROR;

    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    check_error = StackMemory(myStack);
    if(check_error != NO_ERROR)
    {
        return check_error;
    }
    _CHECK_HASH_DJB;

    myStack->data[myStack->size] = element_value;
    myStack->size++;

    #ifdef _DEBUG_HASH_DJB
    calculateHash(myStack);
    #endif // _DEBUG_HASH_DJB

    STACK_VERIFICATOR;

    return NO_ERROR;
}

ErrorNumber StackPop(StackInf* myStack, StackElem_t* element_value)
{
    ErrorNumber check_error = NO_ERROR;

    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    if(myStack->size <= 0)
    {
        return POP_ERROR;
    }

    myStack->size--;
    *element_value = myStack->data[myStack->size];

    for(int i = 0; i < (int)sizeof(StackElem_t); i++)
    {
        ((char*)(&myStack->data[myStack->size]))[i] = 52;
    }

    #ifdef _DEBUG_HASH_DJB
    calculateHash(myStack);
    #endif // _DEBUG_HASH_DJB

    check_error = StackMemory(myStack);
    if(check_error != NO_ERROR)
    {
        return check_error;
    }

    _CHECK_HASH_DJB;

    STACK_VERIFICATOR;

    return NO_ERROR;
}

ErrorNumber StackMemory(StackInf* myStack)
{
    STACK_VERIFICATOR;

    _CHECK_HASH_DJB;

    int new_size = 0;
    if(myStack->size < MIN_STACK_SIZE)
    {
        return NO_ERROR;
    }
    if(myStack->size == myStack->capacity)
    {
        new_size = myStack->capacity * 2;
    }
    if(myStack->size == myStack->capacity / 4)
    {
        new_size = myStack->capacity / 2;
    }
    if(new_size == 0)
    {
        return NO_ERROR;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    myStack->full_data = (StackElem_t*) realloc(myStack->full_data, new_size * sizeof(StackElem_t) +
                                                                    SIZE_CHICK_CHIRICK * 2);
    if(myStack->full_data == NULL)
    {
        return CALLOC_ERROR;
    }
    myStack->data = (StackElem_t*)((char*)myStack->full_data + SIZE_CHICK_CHIRICK);
    #else
    myStack->data = (StackElem_t*) realloc(myStack->data, new_size * sizeof(StackElem_t));
    if(myStack->data == NULL)
    {
        return CALLOC_ERROR;
    }
    #endif // _DEBUG_CHICK_CHIRICK

    for(int i = 0; i < myStack->size; i++)
    {
        memset(&(myStack->data[myStack->size]), 52, myStack->size * (int)sizeof(StackElem_t));
    }

    myStack->capacity = new_size;

    #ifdef _DEBUG_CHICK_CHIRICK
    StackChickChiric(myStack);
    #endif // _DEBUG_CHICK_CHIRICK

    #ifdef _DEBUG_HASH_DJB
    calculateHash(myStack);
    #endif // _DEBUG_HASH_DJB

    STACK_VERIFICATOR;

    return NO_ERROR;
}
