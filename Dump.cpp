#include "../include/Dump.h"


ErrorNumber StackDump(StackInf* myStack)
{
    FILE* file_address = fopen("DumpOutput.txt", "w");
    if(file_address == NULL)
    {
        return OPEN_ERROR;
    }

    if(myStack != NULL)
    {
        fprintf(file_address,
                "myStack address[%p]\n",
                myStack);
    }
    else
    {
        fprintf(file_address,
                "Broken address myStack\n");
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_one = (int*)&(myStack->chick_chirick_one);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_in_struct_one[i], &chick_chirick_in_struct_one[i]);
    }

    if(myStack->full_data != NULL)
    {
        fprintf(file_address,
                "myStack->full_data address = [%p]\n",
                myStack->full_data);
    }
    else
    {
        fprintf(file_address,
                "Broken address myStack->full_data\n");
    }
    #define _ " "
    #else
    #define _
    #endif // _DEBUG_CHICK_CHIRICK

    if(myStack->data != NULL)
    {
        fprintf(file_address,
                "myStack->data     " _ "address = [%p]\n",
                myStack->data);
    }
    else
    {
        fprintf(file_address,
                "Broken address myStack->data\n");
    }

    fprintf(file_address,
            "myStack->size     " _ "address = [%p], size     value = <%4.d>\n"
            "myStack->capacity " _ "address = [%p], capacity value = <%4.d>\n",
            &myStack->size,     myStack->size,
            &myStack->capacity, myStack->capacity);

    #ifdef _DEBUG_HASH_DJB
    fprintf(file_address,
            "myStack->hash_djb = %lld\n", // PRI64
            myStack->hash_djb);
    #endif // _DEBUG_HASH_DJB

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_in_struct_two = (int*)&(myStack->chick_chirick_two);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_in_struct_two[i], &chick_chirick_in_struct_two[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    fprintf(file_address,
            "\nStack Contents:\n{\n");

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_before_stack = (int*)myStack->full_data;
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_before_stack[i], &chick_chirick_before_stack[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    for(int i = 0; i < myStack->capacity; i++)
    {
        fprintf(file_address,
                "size = (%4.d), element value = <" STACK_ELEM_T ">, element address = [%p]\n",
                i, myStack->data[i], &myStack->data[i]);
    }

    #ifdef _DEBUG_CHICK_CHIRICK
    int* chick_chirick_after_stack  = (int*)(((char*)myStack->full_data) +
         SIZE_CHICK_CHIRICK + myStack->capacity * (int)sizeof(StackElem_t) +
         (8 - myStack->capacity * (int)sizeof(StackElem_t)) % 8);
    for(int i = 0; i < SIZE_CHICK_CHIRICK / (int)sizeof(int); i++)
    {
        fprintf(file_address,
                "chick_chirick[%d] = <%x>, chick_chirick address = [%p]\n",
                i, chick_chirick_after_stack[i], &chick_chirick_after_stack[i]);
    }
    #endif // _DEBUG_CHICK_CHIRICK

    fprintf(file_address,
            "}\n");

    fclose(file_address);

    #undef  _

    return NO_ERROR;
}
