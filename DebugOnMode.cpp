#include "../include/DebugOnMode.h"
#include "../include/Verificator.h"


#ifdef _DEBUG_HASH_DJB
// https://github.com/dim13/djb2/blob/master/docs/hash.md - explanation of the hash function
ErrorNumber calculateHash(StackInf* myStack)
{
    myStack->hash_djb = 5381;

    for(int i = 0; i < (int)sizeof(myStack) - (int)sizeof(myStack->hash_djb) - SIZE_CHICK_CHIRICK * 2;
                i++)
    {
        myStack->hash_djb = myStack->hash_djb * 31 + (int)*(((char*)myStack) + SIZE_CHICK_CHIRICK + i);
    }

    for(int i = 0; i < (int)sizeof(myStack->capacity); i++)
    {
        myStack->hash_djb = myStack->hash_djb * 31 + (int)*(((char*)myStack->data) + i);
    }

    STACK_VERIFICATOR;
    return NO_ERROR;
}
#endif // _DEBUG_HASH_DJB

#ifdef _DEBUG_CHICK_CHIRICK
ErrorNumber StackChickChiric(StackInf* myStack)
{
    if(myStack == NULL)
    {
        return NULL_ADDRESS_ERROR;
    }
    if(myStack->full_data == NULL)
    {
        return NULL_ADDRESS_ERROR;
    }

    int* chick_chirick_in_struct_one = (int*)&(myStack->chick_chirick_one);
    int* chick_chirick_in_struct_two = (int*)&(myStack->chick_chirick_two);

    int* chick_chirick_before_stack = (int*)myStack->full_data;
    int* chick_chirick_after_stack  = (int*)(((char*)myStack->full_data) +
         SIZE_CHICK_CHIRICK + myStack->capacity * (int)sizeof(StackElem_t) +
         (8 - myStack->capacity * (int)sizeof(StackElem_t)) % 8);

    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        chick_chirick_in_struct_one[i] = BAD_BEDA;
        chick_chirick_in_struct_two[i] = BAD_BEDA;
        chick_chirick_before_stack [i] = BAD_BEDA;
        chick_chirick_after_stack  [i] = BAD_BEDA;
    }

    STACK_VERIFICATOR;

    return NO_ERROR;
}
#endif // _DEBUG_CHICK_CHIRICK
