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
    while(node != NULL){
        if(node->prev == NULL){
            return;
        }
        node = node->prev;
        if(node->opcode  == STORE || node->opcode  == LOAD){
            if(node->field1 == field || node->field2 == field){ //if the field1 macthces, then its critical
                node->critical = 1;
                //printf("%d", field);
                markCritical(node, node->field2); //call markCritical on the previous node
                //break;
            }
            else{
                markCritical(node, node->field1);
                markCritical(node, node->field2);
            }
        }
        else if(node->opcode == MUL || node->opcode == ADD || node->opcode == SUB){
            if(node->field1 == field || node->field2 == field || node->field3 == field){
                node->critical =1;
                //printf("%d", field);
                markCritical(node, node->field2);
                markCritical(node, node->field3);
                //break;
            }
            else{
                markCritical(node, node->field1);
                markCritical(node, node->field2);
                markCritical(node, node->field3);
            }
        }
        else if(node->opcode == LOADI){
            if(node->field1 == field){
                node->critical = 1;
                //printf("%d", field);
                //break;
            }
            else{
                markCritical(node, node->field1);
            }
        }
        node = node->prev;
        //count++;
        //printf("\n%d\n", count);
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

