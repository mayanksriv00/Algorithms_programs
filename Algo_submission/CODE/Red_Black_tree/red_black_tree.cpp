//Red Black Tree
//Both Insertion and Deletion are implemented
#include <iostream> 
#include <queue> 
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

enum CLR {
    RED,
    BLACK
};

class Tree
{
public:

    Tree* current_parent;
    Tree* current_left;
    Tree* current_right;
    int data;
    CLR current_col;
    Tree(int data) : data(data)
    {
        current_col = RED;
        current_parent = NULL;
        current_left = NULL;
        current_right = NULL;
    }

    void NodeShiftBelow(Tree* para_node)
    {
        if (current_parent != NULL)
        {
            if (NodeToLeft())
            {
                current_parent->current_left = para_node;
            }
            else
            {
                current_parent->current_right = para_node;
            }
        }
        para_node->current_parent = current_parent;
        current_parent = para_node;
    }

    Tree* NodeUncl()
    {
        if (current_parent == NULL || current_parent->current_parent == NULL)
        {
            return NULL;
        }
        if (current_parent->NodeToLeft())
        {
            return current_parent->current_parent->current_right;
        }
        else
        {
            return current_parent->current_parent->current_left;
        }
    }
    Tree* NodeBrohr()
    {
        if (current_parent == NULL)
        {
            return NULL;
        }
        if (NodeToLeft())
        {
            return current_parent->current_right;
        }
        return current_parent->current_left;
    }

    bool NodeToLeft()
    {
        return current_parent->current_left == this;
    }
    bool NodeWithRedChild()
    {
        return (current_left != NULL && current_left->current_col == RED) || (current_right != NULL && current_right->current_col == RED);
    }
};

class TreeNode
{
    Tree* FirstNode;
    void TreeNode_RR(Tree* tmp_node)
    {
        Tree* para_node = tmp_node->current_left;
        if (tmp_node == FirstNode)
        {
            FirstNode = para_node;
        }
        tmp_node->NodeShiftBelow(para_node);
        tmp_node->current_left = para_node->current_right;
        if (para_node->current_right != NULL)
        {
            para_node->current_right->current_parent = tmp_node;
        }
        para_node->current_right = tmp_node;
    }

    

    void TreeNodeChangeData(Tree* Node_k, Tree* Node_l) {
        int var_n;
        var_n = Node_k->data;
        Node_k->data = Node_l->data;
        Node_l->data = var_n;
    }
    void TreeNode_LR(Tree* tmp_node)
    {
        Tree* para_node = tmp_node->current_right;
        if (tmp_node == FirstNode)
        {
            FirstNode = para_node;
        }
        tmp_node->NodeShiftBelow(para_node);
        tmp_node->current_right = para_node->current_left;
        if (para_node->current_left != NULL)
        {
            para_node->current_left->current_parent = tmp_node;
        }
        para_node->current_left = tmp_node;
    }
     void TreeNodeDel(Tree* Node_l) 
	{
        Tree* Node_k = Change_Nodes(Node_l);
        bool BoolVar_col = ((Node_k == NULL || Node_k->current_col == BLACK) && (Node_l->current_col == BLACK));
        Tree* current_parent = Node_l->current_parent;
        if (Node_k == NULL) 
		{
            if (Node_l == FirstNode)
			{
                FirstNode = NULL;
            }
            else
			{
                if (BoolVar_col)
				{
                    Set_BB(Node_l);
                }
                else 
				{
                    if (Node_l->NodeBrohr() != NULL)
					{
						Node_l->NodeBrohr()->current_col = RED;
					}
                        
                }
                if (Node_l->NodeToLeft()) 
				{
                    current_parent->current_left = NULL;
                }
                else
				{
                    current_parent->current_right = NULL;
                }
            }
            delete Node_l;
            return;
        }

        if (Node_l->current_left == NULL || Node_l->current_right == NULL) 
		{
            if (FirstNode==Node_l) 
			{
                Node_l->data = Node_k->data;
                Node_l->current_left = Node_l->current_right = NULL;
                delete Node_k;
            }
            else
			{
                if (Node_l->NodeToLeft()) 
				{
                    current_parent->current_left = Node_k;
                }
                else 
				{
                    current_parent->current_right = Node_k;
                }
                delete Node_l;
                Node_k->current_parent = current_parent;
                if (BoolVar_col)
				{
                    Set_BB(Node_k);
                }
                else
				{
                    Node_k->current_col = BLACK;
                }
            }
            return;
        }
        TreeNodeChangeData(Node_k, Node_l);
        TreeNodeDel(Node_k);
    }
    void Set_RR(Tree* tmp_node)
    {
        if (tmp_node == FirstNode)
        {
            tmp_node->current_col = BLACK;
            return;
        }
        Tree* current_parent = tmp_node->current_parent;
        Tree* tmp_gpr = current_parent->current_parent;
            Tree *NodeUncl = tmp_node->NodeUncl();
        if (current_parent->current_col != BLACK)
        {
            if (NodeUncl != NULL && NodeUncl->current_col == RED)
            {
                current_parent->current_col = BLACK;
                NodeUncl->current_col = BLACK;
                tmp_gpr->current_col = RED;
                Set_RR(tmp_gpr);
            }
            else
            {
                if (current_parent->NodeToLeft())
                {
                    if (tmp_node->NodeToLeft())
                    {
                        TreeNodeChangecol(current_parent, tmp_gpr);
                    }
                    else
                    {
                        TreeNode_LR(current_parent);
                        TreeNodeChangecol(tmp_node, tmp_gpr);
                    }
                    TreeNode_RR(tmp_gpr);
                }
                else
                {
                    if (tmp_node->NodeToLeft())
                    {
                        TreeNode_RR(current_parent);
                        TreeNodeChangecol(tmp_node, tmp_gpr);
                    }
                    else
                    {
                        TreeNodeChangecol(current_parent, tmp_gpr);
                    }
                    TreeNode_LR(tmp_gpr);
                }
            }
        }
    }
    void TreeNodeChangecol(Tree* h, Tree* j)
    {
        CLR var_n;
        var_n = h->current_col;
        h->current_col = j->current_col;
        j->current_col = var_n;
    }
    Tree* AfterCurrentNode(Tree* tmp_node)
	{
        Tree* var_n = tmp_node;

        while (var_n->current_left != NULL)
        {
			var_n = var_n->current_left;
		}
        return var_n;
    }
    Tree* Change_Nodes(Tree* tmp_node) 
	{
        if (tmp_node->current_left != NULL && tmp_node->current_right != NULL)
        {
			return AfterCurrentNode(tmp_node->current_right);
		} 
        if (tmp_node->current_left == NULL && tmp_node->current_right == NULL)
        {
			return NULL;
		}
        if (tmp_node->current_left != NULL)
        {
			return tmp_node->current_left;
		}
        else
        {
			return tmp_node->current_right;
		}
    }
    void Set_BB(Tree* tmp_node)
	{
        if (tmp_node == FirstNode)
        {
			return;
		}
        Tree* NodeBrohr = tmp_node->NodeBrohr();
		Tree* current_parent = tmp_node->current_parent;
        if (NodeBrohr == NULL) 
		{
            Set_BB(current_parent);
        }
        else 
		{
            if (NodeBrohr->current_col == RED) 
			{
                current_parent->current_col = RED;
                NodeBrohr->current_col = BLACK;
                if (NodeBrohr->NodeToLeft())
				{
                    TreeNode_RR(current_parent);
                }
                else 
				{    
                    TreeNode_LR(current_parent);
                }
                Set_BB(tmp_node);
            }
            else 
			{ 
                if (NodeBrohr->NodeWithRedChild()) 
				{
                    if (NodeBrohr->current_left != NULL && NodeBrohr->current_left->current_col == RED) 
					{
                        if (NodeBrohr->NodeToLeft()) 
						{ 
                            NodeBrohr->current_left->current_col = NodeBrohr->current_col;
                            NodeBrohr->current_col = current_parent->current_col;
                            TreeNode_RR(current_parent);
                        }
                        else 
						{
                            NodeBrohr->current_left->current_col = current_parent->current_col;
                            TreeNode_RR(NodeBrohr);
                            TreeNode_LR(current_parent);
                        }
                    }
                    else 
					{
                        if (NodeBrohr->NodeToLeft())
						{
                            NodeBrohr->current_right->current_col = current_parent->current_col;
                            TreeNode_LR(NodeBrohr);
                            TreeNode_RR(current_parent);
                        }
                        else 
						{
                            NodeBrohr->current_right->current_col = NodeBrohr->current_col;
                            NodeBrohr->current_col = current_parent->current_col;
                            TreeNode_LR(current_parent);
                        }
                    }
                    current_parent->current_col = BLACK;
                }
                else 
				{ 
                    NodeBrohr->current_col = RED;
                    if (current_parent->current_col == BLACK)
                    {
						Set_BB(current_parent);
					}
                    else
                    {
						current_parent->current_col = BLACK;
					}
                }
            }
        }
    }
    void TraverseBFS(Tree* tmp_node) {
        if (tmp_node == NULL)
        {
			return;
		}
        queue<Tree*> Q;
        Tree* curr; 
        Q.push(tmp_node);
        while (!Q.empty()) 
		{
            curr = Q.front();
            Q.pop();
            cout << curr->data << " ";
            if (curr->current_left != NULL)
            {
				Q.push(curr->current_left);
			}
            if (curr->current_right != NULL)
            {
				Q.push(curr->current_right);
			}
        }
    }
    void inorder(Tree* tmp_node) 
	{
        if (tmp_node == NULL)
            return;
        inorder(tmp_node->current_left);
        cout << tmp_node->data << " ";
        inorder(tmp_node->current_right);
    }

public:
    TreeNode() 
	{
		FirstNode = NULL;
	}
    Tree* FetchFirstNode() 
	{ 
		return FirstNode;
	}
    void BFS_format() {
        cout << "Level order: " << endl;
        if (FirstNode == NULL)
            cout << "No element is tree" << endl;
        else
            TraverseBFS(FirstNode);
        cout << endl;
    }
    Tree* Find_NodeD(int elm)
	{
        Tree* var_n = FirstNode;
        while (var_n != NULL) 
		{
            if (elm < var_n->data) 
			{
                if (var_n->current_left == NULL)
                {
					break;
				}
                else
                {
					var_n = var_n->current_left;
				}
            }
            else if (var_n->data==elm)
			{
                break;
            }
            else 
			{
                if (var_n->current_right == NULL)
                {
					break;
				}
                else
                {
					var_n = var_n->current_right;
				}
            }
        }
        return var_n;
    }

    void add_elements(int elm) 
	{
        Tree* tmp = new Tree(elm);
        if (FirstNode == NULL) 
		{
            tmp->current_col = BLACK;
            FirstNode = tmp;
        }
        else 
		{
            Tree* var_n = Find_NodeD(elm);
            if (var_n->data == elm)
			{   
                return;
            }
            tmp->current_parent = var_n;
            if (elm < var_n->data)
            {
				var_n->current_left = tmp;
			}
            else
            {
				var_n->current_right = tmp;
			}
            Set_RR(tmp);
        }
    }

    void Nodes_delete(int elm) 
	{
        if (FirstNode == NULL)
		{
			return;
		}
		Tree* Node_k;
        Tree* Node_l = Find_NodeD(elm) ;
        if (Node_l->data != elm) 
		{
            cout << "Node not preset" << elm << endl;
            return;
        }
        TreeNodeDel(Node_l);
    }
	
    void InOrder_format() 
	{
        cout << "Inorder: " << endl;
        if (FirstNode == NULL)
            cout << "No element is tree" << endl;
        else
            inorder(FirstNode);
        cout << endl;
    }
    int calHeight(Tree* node)
    {
        int left=0,right=0;
        if(node==NULL)
            return 0;
        left=left+calHeight(node->current_left);
        right=right+calHeight(node->current_right);
        if(left>right)
            return left+1;
        else
            return right+1;
    }
    int height()
    {
        return calHeight(FirstNode);
    }
};

int main(int argc,char* argv[]) {
    TreeNode tree;

    //-----------------------------------------------------------
    fstream file_dec;
    long long int total_time=0;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    file_dec.open(argv[1],ios::in);
    vector<int> abc;
    if(file_dec.is_open())
    {
        string text;
        while (getline(file_dec,text))
        {
            stringstream ss(text);
            cout<<text<<endl;
            string mid;
            while(getline(ss,mid,' '))
            {  
                abc.push_back(stoll(mid,nullptr,10));
            }
        }
    }
    file_dec.close();
    cout<<endl<<"Input"<<endl;
    for(int i=0;i<abc.size();i++)
        cout<<i<<"::"<<abc[i]<<" ";
    cout<<endl<<endl;

    ofstream output_file_sort;
    output_file_sort.open("Result_height.txt",ios::out|ios::app);
    for(int i=0;i<abc.size();i++)
    {
        tree.add_elements(abc[i]);
        int h=tree.height();                 //calculating height for each insertion
        output_file_sort<<h<<endl;
    }
    output_file_sort.close();
    tree.BFS_format();
    cout<<endl;

    //In order to delete nodes from the tree used fun()
    //tree.Nodes_delete(<val>);

    return 0;
}