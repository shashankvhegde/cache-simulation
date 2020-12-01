#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	int freq;
	struct node* next;
	
}Nodetype;

Nodetype* makenode(int data){
	
	Nodetype *nptr;
	nptr = (Nodetype*)malloc(sizeof(Nodetype));
	nptr->data = data;
	nptr->freq = 1;
	nptr->next = NULL;
	
	return nptr;
	
}

void traverse(Nodetype *lptr){
	
	/*Prints node data*/
	
	Nodetype *nptr;
	nptr = lptr;
	while(nptr !=  NULL){
		printf("Data: ");
		printf("%d ",nptr->data);
		printf("Frequency: ");
		printf("%d\t",nptr->freq);
		nptr = nptr->next;
	}
	printf("\n");
}


int getlength(Nodetype *lptr){
	
	/*Return Length of the Cache*/
	
	int length = 0;
	Nodetype *nptr;
	nptr = lptr;
	
	while(nptr !=  NULL){
		
		length++;
		nptr = nptr->next;
	}
	
	return length;
}


Nodetype* exists(Nodetype *lptr,int data){
	
	
	/*Checks if a node with given data exists in cache or not */
	
	Nodetype *nptr;
	nptr = lptr;
	int found = 0;
	
	while(nptr != NULL && found == 0){
		
	
		if(nptr->data == data){
		
			found = 1;
		}
		else{
			nptr = nptr->next;
		}
		
	}	
	
	return nptr;
	
}


Nodetype* InsertAtEnd(Nodetype *lptr, int data){
	
	/*Creates a node and inserts it at the end*/
	
	Nodetype *nptr, *n;
	nptr = lptr;
	n = makenode(data);
	
	if(nptr != NULL){
				
		while(nptr->next != NULL){
			
			nptr = nptr->next;

		}
		nptr->next = n;	
			
	}
	else{
		/*This case arrives only at the start where you  start creating the cache*/
		lptr = n;
		
	}

	return lptr;
	
}

Nodetype* AppendAtEnd(Nodetype *lptr, Nodetype *nptr){
	
	/*Appends a node which exists in cache at the end */
	
	Nodetype *prev, *ptr, *last;
	prev = NULL;
	ptr = lptr;
	last = lptr;
	
	while(last->next != NULL){
		last = last->next;
	}
	
	if(nptr != last){
		
		while(ptr != nptr){
			prev = ptr;
			ptr = ptr->next;
		}
	
		if(prev != NULL){
			prev->next = nptr->next; 	//If any node other than the first node matches ,only then prev has to be taken into account 
		}
		last->next = nptr;
		if(nptr == lptr){
			lptr = lptr->next; 			//Only if the first node matches lptr will change 
		}
		nptr->next = NULL;
		
	}
	return lptr;
		
}

int main() {
	
	int n;
	int choice = 0;
	int data = 0;
	int cache_size = 0;
	int min;
	int rchoice;
	
	Nodetype *lptr = NULL,*nptr = NULL,*lfu = NULL;
		
	printf("Enter Cache size\n");
	scanf("%d",&n);
	if(n == 0){
		printf("ENTER A POSITIVE CACHE SIZE\n");
	}
	else{
		printf("You have the following choices :\n");
		printf("1.Access a Data element\n");
		printf("2.Exit\n");
		
		while(choice != 2){
			
			printf("Enter choice\n");
			scanf("%d",&choice);
			
			switch(choice){
				
				case 1:
					printf("Enter data element that is to be accessed\n");
					scanf("%d",&data);
					
					
					
					if(cache_size < n){
						
						
						nptr = exists(lptr,data); 
						
						
						if(nptr == NULL){
							lptr = InsertAtEnd(lptr,data);
						}
						else{
							//printf("\n,,%d\n",nptr->data);
							nptr->freq += 1;
							lptr = AppendAtEnd(lptr,nptr);
						}
						
					}				
					else{
						nptr = exists(lptr,data);
						
						if(nptr != NULL){
							nptr->freq = nptr->freq + 1;
							lptr = AppendAtEnd(lptr,nptr);
						}
						else{
							printf("Replacement choices:\n");
							printf("1.LRU:\n");
							printf("2.MRU:\n");
							printf("3.LFU:\n");
							scanf("%d",&rchoice);
						
							switch(rchoice){
								
								case 1:/*LRU*/
								
									printf("ELement removed: %d\n",lptr->data);
									lptr->data = data;
									lptr->freq = 1;
									lptr = AppendAtEnd(lptr,lptr);						
								
									break;
									
								case 2:/*MRU*/
									
									nptr = lptr;
									while(nptr->next != NULL){
										nptr = nptr->next;
									}
									printf("Element removed: %d\n",nptr->data);
									nptr->data = data;
									nptr->freq = 1;
									
									break;
										
								case 3:/*LFU*/
									
									min = INT_MAX;
									nptr = lptr;
									lfu = lptr;
									while(nptr != NULL){
										if(nptr->freq < min){
											min = nptr->freq;
											lfu = nptr;
										}
										nptr = nptr->next;
									}
									printf("Element removed: %d\n",lfu->data);
									lfu->data = data;
									lfu->freq = 1;
									lptr = AppendAtEnd(lptr,lfu);
									
									break;
										
								default:
									
									printf("Invalid choice\n");
	
									break;
									
							}
						}
					}
					cache_size = getlength(lptr);
					
					
					break;
				case 2:
					printf("*******************EXIT*******************");
					break;
				default:
					printf("Enter a valid choice\n");
			}
			
			
			
		}
		
	
	}
	
	getch();
	return 0;
}
