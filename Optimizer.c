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
#include "Instr.h"
void markCritical(Instruction *node, int field){
    node->critical=1;
    node=node->prev;
    while(node){
        if(node->field1==field){
            switch(node->opcode){
                case LOADI: node->critical=1;
                case LOAD: node->critical=1;
                           markCritical(node,node->field2);
                case STORE: node->critical=1;
                            markCritical(node,node->field2);
                case ADD: node->critical=1;
                          markCritical(node,node->field2);
                          markCritical(node,node->field3);
                case SUB: node->critical=1;
                          markCritical(node,node->field2);
                          markCritical(node,node->field3);
                case MUL: node->critical=1;
                          markCritical(node,node->field2);
                          markCritical(node,node->field3);
                default: node->critical=1;
            }
        }
        node=node->prev;
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
            //printf("%d\n",ptr->opcode);
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
        ptr = ptr->next;
    }
    if (head) {
        PrintInstructionList(stdout, head);
        DestroyInstructionList(head);
    }
    return EXIT_SUCCESS;
}

