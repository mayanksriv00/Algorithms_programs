//Red Black Tree
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
enum COL {RED,BLACK};

class TreeNode
{
    public:
        COL tree_col;
        int data;
        TreeNode *current_father,*left,*right;
        TreeNode(int data):data(data) 
        {
            current_father=NULL;
            left=NULL;
            right=NULL;
            tree_col = RED;
        }
        TreeNode* current_sibling()
        {
            if(current_father==NULL)
                return NULL;
            if(side_left())
                return current_father->right;
            return current_father->left;
        }
        bool side_left()                                                        
        {
            return this==current_father->left;
        }
        bool with_red_child()
        {
            return((left!=NULL && left->tree_col==RED) || (right!=NULL && right->tree_col==RED));
        }
        void shift_down(TreeNode *root)
        {
            if(root==NULL)
            {
                if(side_left())
                    current_father->left=root;
                else
                    current_father->right=root;
            }
            root->current_father=current_father;
            current_father=root;
        }
        TreeNode* current_node_uncle()
        {
            if(current_father==NULL || current_father->current_father==NULL)
            {
                return NULL;
            }

            if(current_father->side_left())
                return current_father->current_father->right;
            else
                return  current_father->current_father->left;
        }
};
class Red_Black_Tree
{
    TreeNode *RBroot;
    void BB_fx(TreeNode* root)
    {
        if(root==RBroot)
            return;
        TreeNode *tmpsib=root->current_sibling();
        TreeNode *tmppar=root->current_father;
        if(tmpsib==NULL)
        {
            BB_fx(tmppar);
        }
        else
        {
            if(tmpsib->tree_col==RED)
            {
                tmppar->tree_col=RED;
                tmpsib->tree_col=BLACK;
                if(tmpsib->side_left())
                {
                    RR(tmppar);
                }
                else
                {
                    LR(tmppar);
                }
                BB_fx(root);
            }
            else
            {
                if(tmpsib->with_red_child())
                {
                    if(tmpsib->left!=NULL && tmpsib->left->tree_col==RED)
                    {
                        if(tmpsib->side_left())
                        {
                            tmpsib->left->tree_col=tmpsib->tree_col;
                            tmpsib->tree_col=tmppar->tree_col;
                            RR(tmppar);
                        }
                        else
                        {
                            tmpsib->left->tree_col=tmppar->tree_col;
                            RR(tmpsib);
                            LR(tmppar);
                        }
                    }
                    else
                    {
                        if(tmpsib->side_left())
                        {
                            tmpsib->right->tree_col=tmppar->tree_col;
                            LR(tmpsib);
                            RR(tmppar);
                        }
                        else
                        {
                            tmpsib->right->tree_col=tmpsib->tree_col;
                            tmpsib->tree_col=tmppar->tree_col;
                            LR(tmppar);
                        }
                    }
                    tmppar->tree_col=BLACK;
                }
                else
                {
                    tmpsib->tree_col=RED;
                    if(tmppar->tree_col==BLACK)
                        BB_fx(tmppar);
                    else
                        tmppar->tree_col=BLACK;
                }
            }
        }
    }
    void BFS(TreeNode *root)
    {
        if(root == NULL)
            return;
        queue<TreeNode *> Q;
        TreeNode *node_current;
        Q.push(root);
        while(!Q.empty())
        {
            node_current=Q.front();
            Q.pop();
            cout<<node_current->data<<" ";
            if(node_current->left!=NULL)
                Q.push(node_current->left);
            if(node_current->right!=NULL)
                Q.push(node_current->right);
        }
    }
    void ColChange(TreeNode* root1,TreeNode* root2)
    {
        COL g;
        g=root1->tree_col;
        root1->tree_col=root2->tree_col;
        root2->tree_col=g;
    }
    void trav_L_R(TreeNode* root)
    {
        if(root==NULL)
            return;
        trav_L_R(root->left);
        cout<<root->data<<" ";
        trav_L_R(root->right);
    }
    void RR(TreeNode* Nroot)
    {
        TreeNode* tmp=Nroot->left;
        if(Nroot==RBroot)
            RBroot=tmp;
        Nroot->shift_down(tmp);
        Nroot->left=tmp->right;
        if(tmp->right!=NULL)
            tmp->right->current_father=Nroot;
        tmp->right=Nroot;
    }
    void RBTdel(TreeNode* root)
    {
        TreeNode *tmp=Binary_search_tree_rep(root);
        bool temp_root_bl=((tmp==NULL || tmp->tree_col==BLACK)&&(root->tree_col==BLACK));
        TreeNode* cpr=root->current_father;
        if(tmp==NULL)
        {
            if(root==RBroot)
            {
                RBroot=NULL;
            }
            else
            {
                if(temp_root_bl)
                {
                    BB_fx(root);
                }
                else 
                {
                    if(root->current_sibling()!=NULL)
                        root->current_sibling()->tree_col=RED;
                }
                if(root->side_left())
                {
                    cpr->left=NULL;
                }
                else
                {
                    cpr->right=NULL;
                }
            }
            delete root;
            return;
        }
        if(root->left==NULL || root->right==NULL)
        {
            if(root==RBroot)
            {
                root->data=tmp->data;
                root->left=root->right=NULL;
                delete tmp;
            }
            else
            {
                if(root->side_left())
                {
                    RBroot->left=tmp;
                }
                else
                {
                    RBroot->right=tmp;
                }
                delete root;
                tmp->current_father=RBroot;
                if(temp_root_bl)
                {
                    BB_fx(tmp);
                }
                else
                {
                    tmp->tree_col=BLACK;
                }
            }
            return;
        }
        DatChange(tmp,root);
        RBTdel(tmp);
    }
    void setRR(TreeNode* root)
    {
        if(root==RBroot)
        {
            root->tree_col=BLACK;
            return;
        }
        TreeNode *currentpar=root->current_father;
        TreeNode *currentgpr=currentpar->current_father;
        TreeNode *currentubr=root->current_node_uncle();
        if(currentpar->tree_col!=BLACK)
        {
            if(currentubr!=NULL && currentubr->tree_col==RED)
            {
                currentpar->tree_col=BLACK;
                currentubr->tree_col=BLACK;
                currentgpr->tree_col=RED;
                setRR(currentgpr);
            }
            else
            {
                if(currentpar->side_left())
                {
                    if(root->side_left())
                    {
                        ColChange(currentpar,currentgpr);
                    }
                    else
                    {
                        LR(currentpar);
                        ColChange(root,currentgpr);
                    }
                    RR(currentgpr);
                }
                else
                {
                    if(root->side_left())
                    {
                        RR(currentpar);
                        ColChange(root,currentgpr);
                    }
                    else
                    {
                        ColChange(currentpar,currentgpr);
                    }
                    LR(currentgpr);
                }
            }
        }
    }
    TreeNode *Binary_search_tree_rep(TreeNode *root)
    {
        if(root->left!=NULL && root->right!=NULL)
            return AfterNode(root->right);
        if(root->left==NULL && root->right==NULL)
            return NULL;
        if(root->left!=NULL)
            return root->left;
        else
            return root->right;
    }
    void LR(TreeNode* Nroot)
    {
        TreeNode* tmp=Nroot->right;
        if(Nroot==RBroot)
            RBroot=tmp;
        Nroot->shift_down(tmp);
        Nroot->right=tmp->left;
        if(tmp->left!=NULL)
            tmp->left->current_father=Nroot;
        tmp->left=Nroot;
    }
    TreeNode *AfterNode(TreeNode *root)         //successor
    {
        TreeNode* g=root;
        while(g->left!=NULL)
            g=g->left;
        return g;
    }
    void DatChange(TreeNode* root1,TreeNode* root2)
    {
        int g;
        g=root1->data;
        root1->data=root2->data;
        root2->data=g;
    }
    public:
    Red_Black_Tree()
    {
        RBroot=NULL;
    }
    void build_tree(int val)
    {
        TreeNode* tmp_node=new TreeNode(val);
        if(RBroot==NULL)
        {
            tmp_node->tree_col=BLACK;
            RBroot=tmp_node;;
        }
        else
        {
            TreeNode *ssnode=find(val);
            if(ssnode->data==val)
            {
                return;
            }
            tmp_node->current_father=ssnode;
            if(val<ssnode->data)
                ssnode->left=tmp_node;
            else
                ssnode->right=tmp_node;
            setRR(tmp_node);
        }   
    }
    TreeNode *fetchRBroot()
    {
        return RBroot;
    }
    TreeNode *find(int val)
    {
        TreeNode* g=RBroot;
        while(g!=NULL)
        {
            if(val<g->data)
            {
                if(g->left==NULL)
                    break;
                else
                    g=g->left;
            }
            else if(g->data==val)
            {
                break;
            }
            else
            {
                if(g->right==NULL)
                    break;
                else
                    g=g->right;
            }
        }
        return g;
    }
    void BFSpr()
    {
        cout<<"BFS level wise "<<endl;
        if(RBroot==NULL)
            cout<<"No element in tree"<<endl;
        else
        {
            BFS(RBroot);
        }
        cout<<endl;        
    }
    void dataDel(int da)
    {
        if(RBroot==NULL)
            return;
        TreeNode *tmp=find(da);
        TreeNode *tmp1;
        if(tmp->data!=da)
        {
            cout<<"Unable to delete node: not found"<<da<<endl;
            return;
        }
        RBTdel(tmp);
    }
    void L_R_pr()
    {
        cout<<"ELM in Inoder : "<<endl;
        if(RBroot==NULL)
            cout<<"No elements in tree"<<endl;
        else
        {
            trav_L_R(RBroot);
        }
        cout<<endl;
    }

};


int main()
{
    Red_Black_Tree node;
    node.build_tree(7);
    node.build_tree(3);
    node.build_tree(18);
    node.build_tree(10);
    node.build_tree(22);
    node.build_tree(8);
    node.build_tree(11);
    node.build_tree(26);
    node.build_tree(2);
    node.build_tree(6);
    node.build_tree(13);

    node.L_R_pr();
    node.BFSpr();
    return 0;
}