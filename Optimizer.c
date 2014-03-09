/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2014                              *
 *  Authors: Ulrich Kremer                   *
 *           Hans Christian Woithe           *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"
//#include "Instr.h"
void markCritical(Instruction *node, int field);

void markCritical(Instruction *node, int field){
    while(node != NULL){
        if(node->prev->opcode  == STORE){
            if(node->prev->field1 == field){        //if the field1 macthces, then its critical
                node->prev->critical = 1;
                printf("%d", field);
                markCritical(node->prev, node->prev->field2);   //call markCritical on the previous node
            }
        }
        else if(node->prev->opcode == MUL){
            if(node->prev->field1 == field){
                node->prev->critical =1;
                printf("%d", field);
                markCritical(node->prev, node->prev->field2);
                markCritical(node->prev, node->prev->field3);
            }
        }
        else if(node->prev->opcode == ADD){
            if(node->prev->field1 == field){
                node->prev->critical =1;
                printf("%d", field);
                markCritical(node->prev, node->prev->field2);
                markCritical(node->prev, node->prev->field3);
            }
        }
        else if(node->prev->opcode == SUB){
            if(node->prev->field1 == field){
                node->prev->critical =1;
                printf("%d", field);
                markCritical(node->prev, node->prev->field2);
                markCritical(node->prev, node->prev->field3);
            }
        }
        else if(node->prev->opcode == LOADI){
            if(node->prev->field1 == field){
                node->prev->critical = 1;
                printf("%d", field);
            }
        }
        else if(node->prev->opcode == LOAD){
            if(node->prev->field1 == field){
                node->prev->critical = 1;
                printf("%d", field);
                markCritical(node->prev, node->prev->field2);
            }
        }
        node = node->prev;
    }
}

int main()
{
    Instruction *head;
    head = ReadInstructionList(stdin);
    if (!head) {
        WARNING("No instructions\n");
        exit(EXIT_FAILURE);
    }
    /* YOUR CODE GOES HERE */
    Instruction *ptr;
    for(ptr = head; ptr!=NULL; ptr=ptr->next){
        if(ptr->opcode == WRITE || ptr->opcode == READ){
            ptr->critical = 1;
        }
        if(ptr->opcode == WRITE){
            markCritical(ptr, ptr->field1);
        }
    }
    ptr = head;
    while(ptr != NULL){
        if(!ptr->critical == 1){
            Instruction *tmp = ptr;
            ptr->prev->next = ptr->next;    //make the previous node point to current nodes next
            ptr = ptr->next;                //increment pointer
            free(tmp);
        }
    }
    if (head) {
        PrintInstructionList(stdout, head);
        DestroyInstructionList(head);
    }
    return EXIT_SUCCESS;
}

