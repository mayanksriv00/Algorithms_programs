#include<iostream>
#include<vector>
using namespace std;

struct TreeNode{
    int number;
    struct TreeNode* left;
    struct TreeNode* right;
}*root;

struct TreeNode* insertion(int num,TreeNode* node)            //Inserting elements in Binary search Tree
{
    if(node == NULL)
    {
        node=new TreeNode;
        node->number=num;
        node->left=NULL;
        node->right=NULL;
        return node;
    }
    else if(num<node->number)
        node->left=insertion(num,node->left);
    else 
        node->right=insertion(num,node->right);
    return node;
}

void inorder_traversal(TreeNode* node)                                  //Inorder Traversal 
{
    if(node==NULL)
        return;
    inorder_traversal(node->left);
    cout<<node->number<<" ";
    inorder_traversal(node->right);
}

void preorder_traversal(TreeNode* node)                                //preorder traversal
{
    if(node==NULL)
        return;
    cout<<node->number<<" ";
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void postorder_traversal(TreeNode* node)                                //Post order traversal
{
    if(node==NULL)
        return;
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    cout<<node->number<<" ";
}

int height(TreeNode* node)                                              //Height of the tree
{
    int left=0,right=0;
    if(node==NULL)
        return 0;
    left=left+height(node->left);
    right=right+height(node->right);
    if(left>right)
        return left+1;
    else
        return right+1;
}

struct TreeNode* findingMin(TreeNode* node)                             //Finding Min element in the BST
{
    if(node==NULL)
        return NULL;
    else if(node->left==NULL)
        return node;
    else
        return findingMin(node->left);
}

struct TreeNode* findingMax(TreeNode* node)                             //Finding max element in the BST
{
    if(node==NULL)
        return NULL;
    else if(node->right==NULL)
        return node;
    else
        return findingMax(node->right);
}

struct TreeNode* search(TreeNode* node,int element)                 //Search element in a BST
{
    if(node==NULL)
        return node;
    if(element<node->number)
        return search(node->left,element);
    else if(element>node->number)
        return search(node->right,element);
    else
        return node;
}

struct TreeNode* NodeWithMin(struct TreeNode* node)
{
    struct TreeNode* present=node;
    while(present && present->left!=NULL)
        present = present->left;
    return present;
}

struct TreeNode* nodeDeletion(TreeNode* node,int element)
{
    if(node==NULL)
        return node;
    if(element<node->number)                                                //If element is less than node value, means mve left
        node->left=nodeDeletion(node->left,element);
    else if(element>node->number)                                           //If the element is greater than the node value, means move right
        node->right=nodeDeletion(node->right,element);                      
    else{
        if(node->left==NULL)                                                //nodes with 1 children
        {
            struct TreeNode* tmp=node->right;;
            free(node);
            return tmp;
        }
        else if(node->right==NULL)
        {
            struct TreeNode* tmp=node->left;
            free(node);
            return tmp;
        }
        struct TreeNode* tmp=NodeWithMin(node->right);                      //inorder successor: nodes with 2 children
        node->number=tmp->number;   
        node->right=nodeDeletion(node->right,tmp->number);
    }
    return node;
}

int main()
{
    int n;
    cout<<"Enter the size of an array"<<endl;
    cin>>n;
    vector<int> abc;
    for(int i=0;i<n;i++)
    {
        int x=0;
        cin>>x;
        abc.push_back(x);;
    }
    //inserting elements in BST
    for(int i=0;i<abc.size();i++)
    {
        root=insertion(abc[i],root);
    }
    //Traversal--------------------------------------------------

    //inorder_traversal(root);
    //preorder_traversal(root);
    //postorder_traversal(root);

    //Finding max in BST-----------------------------------------

    //TreeNode* tmp=findingMax(root);
    //cout<<tmp->number<<endl;

    //FInding mix in BST-----------------------------------------

    //TreeNode* tmp=findingMin(root);
    //cout<<tmp->number<<endl;

    //Searching element in BST  ---------------------------------

    //TreeNode* tmp=search(root,56);                                 //if tmp return null element not found else found
    //if(tmp)
      //  cout<<"Element found"<<endl;
    //else 
      //  cout<<"Element not found"<<endl;

    
    //Height of the Binary search tree------------------------------------
    //cout<<height(root)<<endl;1

    //Node deletion
    //inorder_traversal(root);
    //root=nodeDeletion(root,23);
    //inorder_traversal(root);

    return 0;
}