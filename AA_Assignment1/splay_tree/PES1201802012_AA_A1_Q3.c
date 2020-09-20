#include<stdio.h>
#include<stdlib.h>
#include "splay_tree_imp.h"

typedef struct splay_tree_node
{
    int key;
    int value;
    struct splay_tree_node* left;
    struct splay_tree_node* right;
    struct splay_tree_node* parent;
}node;

typedef struct splay_tree
{
    node* head;
}tree;

void inorder(node* head)
{
    if (head)
        {
            inorder(head->left);
            printf("%d ",head->key);
            inorder(head->right);
        }
}
void preorder(node* head)
{
    if (head)
        {
            printf("%d ",head->key);
            preorder(head->left);
            preorder(head->right);
        }
}

node* create_node(int key,int value)
{
    node* temp=malloc(sizeof(node));
    temp->left=NULL;
    temp->right=NULL;
    temp->parent=NULL;//important for an easier splay function
    temp->key=key;
    temp->value=value;
    return temp;
}
int no_of_rotations=0;

node* rightrotate(node* head,node* child)
{
    //child is on left subtree
    ++no_of_rotations;
    //printf("%d\n",no_of_rotations);
    head->left=child->right;
    if (child->right)//very important condition. Code broke many times because of this
        child->right->parent=head;
    child->right=head;
    return child;
}

node* leftrotate(node* head,node* child)
{
    //child is on left subtree
    ++no_of_rotations;
    //printf("%d\n",no_of_rotations);
    head->right=child->left;
    if (child->left)//very important condition. Code broke many times because of this
        child->left->parent=head;
    child->left=head;
    return child;
}

void splay(void* treeptr,node* temp)
{
    // printf("\nsplayPREORDER: ");  
    // preorder(((tree*)treeptr)->head);
    // printf("\n");
    //the parent of head is NULL;
    //printf("in splay\n");
    while(temp!=((tree*)treeptr)->head)
    {   //printf("IN inorder:\n");
        //inorder(((tree*)treeptr)->head);
        //printf("\n");
        if (temp->parent==((tree*)treeptr)->head)
        {   //printf("YES\n");
            //printf("%d %d %d\n",temp->key,temp->parent->key,((tree*)treeptr)->head->key);
            temp->parent=NULL;
            ((tree*)treeptr)->head->parent=temp;
            if (((tree*)treeptr)->head->left==temp)
                ((tree*)treeptr)->head=rightrotate(((tree*)treeptr)->head,temp);
            else
                ((tree*)treeptr)->head=leftrotate(((tree*)treeptr)->head,temp);
            return;
        }
        //we can have parent and grandparent
        node* parent=temp->parent;
        node* grandparent=parent->parent;

        if (parent->left==temp && grandparent->left==parent)//zig-zig rotation
        {
            if (grandparent->parent)//grandparent is not the tree's head
            {
                if (grandparent->parent->left==grandparent)
                {
                    parent->parent=grandparent->parent;
                    grandparent->parent=parent;
                    parent->parent->left=rightrotate(grandparent,parent);
                }
                else
                {
                    parent->parent=grandparent->parent;
                    grandparent->parent=parent;
                    parent->parent->right=rightrotate(grandparent,parent);
                }               
            }
            else
            {
                parent->parent=NULL;
                grandparent->parent=parent;
                ((tree*)treeptr)->head=rightrotate(grandparent,parent);
            }
            if (parent==((tree*)treeptr)->head)//parent has become tree's head
            {
                temp->parent=NULL;
                parent->parent=temp;
                ((tree*)treeptr)->head=rightrotate(parent,temp);
            }
            else
            {
                if (parent->parent->left==parent)//parent is left child
                {
                    temp->parent=parent->parent;
                    parent->parent=temp;
                    temp->parent->left=rightrotate(parent,temp);
                }
                else
                {
                    temp->parent=parent->parent;
                    parent->parent=temp;
                    temp->parent->right=rightrotate(parent,temp);
                }
            } 
            
            // if (parent->key==59)
            //     {   printf("\nchildof 59 %d:\n",parent->left->parent->key);
            //         // node* j=parent;
            //         // while(j)
            //         //     {printf("%d ",j->key);
            //         //     j=j->parent;
            //         //     }
            //     }
            // printf("\n");
        }
        else if (parent->right==temp && grandparent->right==parent)//zig-zig rotation
        {
            if (grandparent->parent)//grandparent is not the tree's head
            {   
                if (grandparent->parent->left==grandparent)
                {
                    parent->parent=grandparent->parent;
                    grandparent->parent=parent;
                    parent->parent->left=leftrotate(grandparent,parent);
                }
                else
                {
                    parent->parent=grandparent->parent;
                    grandparent->parent=parent;
                    parent->parent->right=leftrotate(grandparent,parent);
                }               
            }
            else
            {
                parent->parent=NULL;
                grandparent->parent=parent;
                ((tree*)treeptr)->head=leftrotate(grandparent,parent);
            }
            if (parent==((tree*)treeptr)->head)//parent has become tree's head
            {
                temp->parent=NULL;
                parent->parent=temp;
                ((tree*)treeptr)->head=leftrotate(parent,temp);
            }
            else
            {
                if (parent->parent->left==parent)//parent is left child
                {
                    temp->parent=parent->parent;
                    parent->parent=temp;
                    temp->parent->left=leftrotate(parent,temp);
                }
                else
                {
                    temp->parent=parent->parent;
                    parent->parent=temp;
                    temp->parent->right=leftrotate(parent,temp);
                } 
            }
            
        }
        else if (parent->right==temp && grandparent->left==parent)//zig-zag rotation
        {
            //first parent has to be processed and then grandparent
            parent->parent=temp;
            temp->parent=grandparent;
            grandparent->left=leftrotate(parent,temp);
            if (grandparent->parent)//grandparent is not the tree's head
            {
                temp->parent=grandparent->parent;
                grandparent->parent=temp;

                if (grandparent==temp->parent->left)
                    temp->parent->left = rightrotate(grandparent,temp);
                else
                    temp->parent->right = rightrotate(grandparent,temp);
            }
            else
            {
                temp->parent=NULL;
                grandparent->parent=temp;
                ((tree*)treeptr)->head=rightrotate(grandparent,temp);
            }
        }
        else if(parent->left==temp && grandparent->right==parent)
        {
            parent->parent=temp;
            temp->parent=grandparent;
            grandparent->right=rightrotate(parent,temp);
            if (grandparent->parent)
            {
                temp->parent=grandparent->parent;
                grandparent->parent=temp;
                if (temp->parent->left==grandparent)
                    temp->parent->left = leftrotate(grandparent,temp);
                else
                    temp->parent->right = leftrotate(grandparent,temp);
            }
            else
            {
                temp->parent=NULL;
                grandparent->parent=temp;
                ((tree*)treeptr)->head=leftrotate(grandparent,temp);
            }
        }
    }
}

void* make_new_dictionary()
{
    void* temp=malloc(sizeof(tree));
    ((tree*)temp)->head=NULL;
    return temp;
}

void insert(void* treeptr, int key, int value)
{   //printf("\ninsert %d\n",key);
    if (!(((tree*)treeptr)->head))
    {
        ((tree*)treeptr)->head = create_node(key,value);
        return;
    }
    node* head=((tree*)treeptr)->head;
    node* parent=NULL;
    while(head!=NULL && head->key!=key)
    {
        parent=head;
        //printf("insert %d\n",head->key);
        if (key>head->key)
            head=head->right;
        else
            head=head->left;
        
    }
    if (!parent)//only head's value has to be changed.
    {   //printf("no change\n");
        head->value=value;
        return;//no need to splay;
    }
    else //we have a parent
    {
        if (!head)//end of tree has been reached->new node has to be inserted
        {
            head=create_node(key,value);
            head->parent=parent;
            if (key<parent->key)
                parent->left=head;
            else
                parent->right=head;
        }
        else//the key is already there=>only modification
        {
            //printf("no change\n");
            head->value=value;
        }
        splay(treeptr,head);  
        /*
        printf("INORDER:");
        inorder(((tree*)treeptr)->head);
        printf("\n");
        printf("PREORDER:");
        preorder(((tree*)treeptr)->head);
        printf("\n\n");
        */
        //head will not be the tree's head=> we need to splay
        //printf("bsplay %d %d\n",head->key,((tree*)treeptr)->head->key);
        //printf("bsplay h%d p%d t%d\n",head->key,head->parent->key,((tree*)treeptr)->head->key);
        //inorder(((tree*)treeptr)->head);
        //printf("\n");
        // node* j=head;
        // printf("parents: ");
        // while(j)
        // {
        //     printf("%d ",j->key);
        //     j=j->parent;
        // }
        // printf("\n");
        
        //printf("as %d\n",((tree*)treeptr)->head->key);  
        // printf("asplay h%d t%d\nINORDER: ",head->key,((tree*)treeptr)->head->key);  
        // inorder(((tree*)treeptr)->head);
        // printf("\nPREORDER: ");  
        // preorder(((tree*)treeptr)->head);
        // printf("\n");
        // printf("InsertParent:");
        // while(head!=NULL)
        // {
        //     printf("%d ",head->key);
        //     head=head->parent;
        // }
        //printf("\n");

        //printf("asplay %d %d\n",head->key,((tree*)treeptr)->head->key);
    }
    //printf("nor %d\n",no_of_rotations);
    // inorder(((tree*)treeptr)->head);
    // printf("\ninsert preorder: ");
    // preorder(((tree*)treeptr)->head);
    printf("nor %d\n",no_of_rotations);
    
}

int find(void* treeptr, int key)
{   //printf("\nfind %d\n",key);
    if (!((tree*)treeptr)->head)
        return -1;
    else
    {
        node* parent=NULL;
        node* current=((tree*)treeptr)->head;
        while(current && current->key!=key)
        {
            parent=current;
            if (current->key<key)
                current=current->right;
            else
                current=current->left;
        }
        if (!current)
            return -1;
        //printf("\nBADKA:");
        // node* ju=current;
        // while(ju!=NULL)
        // {
        //     printf("%d ",ju->key);
        //     ju = ju->parent;
        // }
        // //printf("\n");
        splay(((tree*)treeptr),current);
        // printf("\nINORDER:");
        // inorder(((tree*)treeptr)->head);
        // printf("\nPREORDER:");
        // preorder(((tree*)treeptr)->head);
        // printf("\n");
        printf("nor %d\n",no_of_rotations);
        return ((tree*)treeptr)->head->value;
        
    }
}
/*
int main(){
    void *dict = make_new_dictionary();
    insert(dict, 5, 1);
    insert(dict, 2, 1);
    insert(dict, 7, 1);
    insert(dict, 6, 1);
    insert(dict, 1, 1);
    insert(dict, 3, 1);
    insert(dict, 5, 2);
    insert(dict, 5, 3);
    insert(dict, 6, 2);
    insert(dict, 2, 2);
    insert(dict, 2, 3);
    insert(dict, 2, 3);

    printf("Before find: \n");

    printf("Data is: %d \n", find(dict, 2));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Data is: %d \n", find(dict, 1));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Data is: %d \n", find(dict, 5));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Data is: %d \n", find(dict, 7));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Data is: %d \n", find(dict, 2));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Data is: %d \n", find(dict, 6));
    printf("Preorder: ");
    preorder(((tree*)dict) -> head);
    printf("\n");
    printf("Inorder: ");
    inorder(((tree*)dict) -> head);
    printf("\n");
    printf("\n");
    printf("\n");

    // insert(tree,67 , rand()%BENCHMARK_COUNT);
	// insert(tree,45, rand()%BENCHMARK_COUNT);
	// insert(tree,89, rand()%BENCHMARK_COUNT);
	// insert(tree,56, rand()%BENCHMARK_COUNT);
	// insert(tree,31, rand()%BENCHMARK_COUNT);
	// insert(tree,35, rand()%BENCHMARK_COUNT);
	// insert(tree,28, rand()%BENCHMARK_COUNT);
	// insert(tree,64, rand()%BENCHMARK_COUNT);
	// insert(tree,53, rand()%BENCHMARK_COUNT);
	// insert(tree,91, rand()%BENCHMARK_COUNT);
	// insert(tree,93, rand()%BENCHMARK_COUNT);
	// insert(tree,92, rand()%BENCHMARK_COUNT);
    // printf("Preorder: ");
    // preorder(((tree*)tree) -> head);
    // printf("\n");


    // printInorder(((tree*)tree) -> head);
    // print_t(((tree*)tree) -> head);
}
*/
