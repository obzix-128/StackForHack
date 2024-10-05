#include "../include/Verificator.h"
#include "../include/Dump.h"


bool StackVerificator(StackInf* myStack)
{
    if(myStack == NULL)
    {
        StackDump(myStack);
        return true;
    }
    if(myStack->data == NULL)
    {
        StackDump(myStack);
        return true;
    }
    if(myStack->size < 0)
    {
        StackDump(myStack);
        return true;
    }
    if(myStack->capacity < MIN_STACK_SIZE)
    {
        StackDump(myStack);
        return true;
    }
    if(myStack->size > myStack->capacity)
    {
        StackDump(myStack);
        return true;
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_one = (int*)&(myStack->chick_chirick_one);
    int* chick_chirick_in_struct_two = (int*)&(myStack->chick_chirick_two);

    int* chick_chirick_before_stack = (int*)myStack->full_data;
    int* chick_chirick_after_stack  = (int*)(((char*)myStack->full_data) +
         SIZE_CHICK_CHIRICK + myStack->capacity * (int)sizeof(StackElem_t) +
         (8 - myStack->capacity * (int)sizeof(StackElem_t)) % 8);

    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        if(chick_chirick_in_struct_one[i] != BAD_BEDA ||
           chick_chirick_in_struct_two[i] != BAD_BEDA ||
           chick_chirick_before_stack [i] != BAD_BEDA ||
           chick_chirick_after_stack  [i] != BAD_BEDA)
        {
            StackDump(myStack);
            return true;
        }
    }
    #endif // _DEBUG_CHICK_CHIRICK

    return false;
}
