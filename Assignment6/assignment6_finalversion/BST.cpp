/******************************************************************** 
PROJECT:		Assignment 6 - CS 355
GROUP:			Josh Reinoehl, Micheal Bretheric, Ricky Moore,
				Jonathon Marlar
DESCRIPTION:	Creation, modification, and deletion of binary
				search trees
DATE:			4 October 2012
*********************************************************************/
#include"BST.h"
using namespace std;

/**
Node Class
*/

BNode::BNode():
	data(NULL),
	left(NULL),
	right(NULL)
{}

BNode::BNode(int e):
	left(NULL),
	right(NULL)
{
	data=e;
}

BNode::BNode(int e, BNode* tleft, BNode* tright)
{
	data=e;
	left=tleft;
	right=tright;
}

int BNode::GetData()const
{
	return data;
}

/**
BST Class
*/

BST::BST():
	root(NULL),
	cursor(NULL)
{}

BST::BST(const BST& tmp)
{
	if( tmp.root == NULL )
	{
		root = NULL;
		cursor = NULL;
	}
	else
	{
		root = CopyList(tmp.root);
		cursor = root;
	}
}

BST::~BST()
{
	ClearList();
}

BST& BST::operator=(const BST& l)
{
    ClearList();

	if( l.root == NULL )
	{
		root = NULL;
		cursor = NULL;
	}
	else
	{
		root = CopyList(l.root);
		Find(l.cursor->data);
	}
	return *this;
}

/******************************************************************** 
FUNCTION:			InsertHelp
DESCRIPTION:		Utilizes a BNode* type to add data to the BST;
					used in Insert()
WRITER(S):			Group			
*********************************************************************/
bool BST::InsertHelp(BNode* n)
{
    BNode* current=root;
    while(true)
    {
        if(n->data==current->data)
            return false;
            
        if(n->data < current->data)
        {
                if(current->left != NULL)
                {
                        current = current->left;
                }
                else
                {
                        current->left = n;
                        return true;
                }
        }
        else
        {
                if(current->right != NULL)
                {
                        current = current->right;
                }
                else
                {
                        current->right = n;
                        return true;
                }
        }
    }
}

/******************************************************************** 
FUNCTION:			PrintInHelp
DESCRIPTION:		Helps print data in numeric order from a BNode*
					to an ostream; used in PrintIn()
WRITER(S):			Group
*********************************************************************/
void BST::PrintInHelp(ostream& os, BNode* n)
{
    
    if(n->left != NULL)
        PrintInHelp(os,n->left);
    
    if(n==cursor)
        os << "[" << n->data << "]\t";
    else
        os << n->data <<"\t";

    if(n->right != NULL)
        PrintInHelp(os,n->right);
}

/******************************************************************** 
FUNCTION:			PrintPreHelp
DESCRIPTION:		Helps print data in the order R(L)(R) from a 
					BNode* to an ostream; used in PrintPre()
WRITER(S):			Group	
*********************************************************************/
void BST::PrintPreHelp(ostream& os, BNode* n)
{
    if(n==cursor)
        os << "[" << n->data << "]\t";
    else
        os << n->data <<"\t";
        
    if(n->left != NULL)
        PrintPreHelp(os,n->left);
    
    if(n->right != NULL)
        PrintPreHelp(os,n->right);
}

/******************************************************************** 
FUNCTION:			PrintPostHelp
DESCRIPTION:		Helps print data in the order (L)(R)R from a 
					BNode* to an ostream; used in PrintPost()
WRITER(S):			Group
*********************************************************************/
void BST::PrintPostHelp(ostream& os, BNode* n)
{
    if(n->left != NULL)
        PrintPostHelp(os,n->left);
    
    if(n->right != NULL)
        PrintPostHelp(os,n->right);
        
    if(n==cursor)
        os << "[" << n->data << "]\t";
    else
        os << n->data <<"\t";
}

/******************************************************************** 
FUNCTION:			FindHelp
DESCRIPTION:		Helps find an integer e with a BNode* n as a
					reference; used in Find().
WRITER(S):			Group
*********************************************************************/
void BST::FindHelp(int e, BNode*n)
{
	if(e==n->data)
		cursor=n;

	else if(n->left!=NULL&&e<n->data)
		FindHelp(e,n->left);

	else if(n->right!=NULL&&e>n->data)
		FindHelp(e,n->right);

	else
		GoToEnd();
}

/******************************************************************** 
FUNCTION:			ClearListHelper
DESCRIPTION:		Aids in clearing a list using a BNode*; used in
					ClearList()
WRITER(S):			Group
*********************************************************************/
void BST::ClearListHelper(BNode* n)
{
    if(n->left != NULL)
    {
        ClearListHelper(n->left);
        n->left = NULL;
    }
    
    if(n->right != NULL)
    {
        ClearListHelper(n->right);
        n->right = NULL;
    }   
    delete n; 
}

/******************************************************************** 
FUNCTION:			Parent
DESCRIPTION:		Assuming n is in the tree, finds the parent of n
WRITER(S):			Group
*********************************************************************/
BNode* BST::Parent(BNode* n)
{
    BNode* temp=root;
    
    if(n == root)
    {
        return n;
    }
	
	while( (temp->left != NULL && temp->left != cursor)
            || (temp->right != NULL && temp->right != cursor) )
    {
        if(temp->left == n || temp->right == n)//THIS IF NEEDS TO BE ADDED TO STOP ON THE ACTUAL POINT
            break;
        else if (n->data < temp->data)
            temp=temp->left;
        else
            temp=temp->right;
    }
    return temp;
}

/******************************************************************** 
FUNCTION:			Insert
DESCRIPTION:		Adds data into a binary search tree and places
					the tree's cursor to the newly added node
WRITER(S):			Group
*********************************************************************/
bool BST::Insert(int e)//cursor at insertion point
{
	BNode* temp;
	try
	{
		temp = new BNode;
	}
	catch(bad_alloc e)
	{
		return false;
	}

	temp->data = e;
	if(root == NULL)
	{
		root = temp;
		cursor=temp;
	}
	else 
	{
        if(InsertHelp(temp))
			cursor=temp;
	}
	return true;
}

/******************************************************************** 
FUNCTION:			Remove
DESCRIPTION:		Removes data from a binary search tree and places
					the cursor at the deleted node's parent
WRITER(S):			Group
*********************************************************************/
bool BST::Remove(int e)//cursor at parent of removed item or at root
{
    BNode* temp;
    BNode* parent;
    BNode* cparent;
    if (root == NULL || Find(e) == NULL)
	{
		cursor = root;
	    return false;
	}

    temp = cursor;
    
	/* CODE EDITED BY COLE */
    if(temp == root)
    {
		if ( root->left != NULL && root->right != NULL )
		{
			BNode* temproot = temp->right;
			root = root->right;
			cursor = root;
			while ( temproot->left != NULL )
				temproot = temproot->left;
			temproot->left = temp->left;
			delete temp;
			return true;
		}
		else
		{
			if ( root->left == NULL && root->right != NULL )
			{
				root = root->right;
				delete temp;
				cursor = root;
				return true;
			}
			else if ( root->left != NULL && root->right == NULL )
			{
				root= root->left;
				delete temp;
				cursor = root;
				return true;
			}
			else
			{
				root = NULL;
				cursor = root;
				return true;
			}
		}
    }
	/* END O' CODE EDITED BY COLE */
    
    parent = Parent(cursor);
    if(parent->left == temp && temp->left == NULL && temp->right == NULL)
    {
        parent->left = NULL;
        delete temp; 
    }
    else if (parent->right == temp && temp->left == NULL && temp->right == NULL)
    {
        parent->right = NULL;
        delete temp;
    }
    else if(parent->left == temp && temp->left != NULL && temp->right != NULL)
    {
       GoToNext();
       cparent=Parent(cursor);
       cparent->left=NULL;
       cursor->left=temp->left;
       parent->left=cursor;
       delete temp;  
    }
    else if (parent->right == temp && temp->left != NULL && temp->right != NULL)
    {
       GoToPrev();
       cparent=Parent(cursor);
       cparent->right=NULL;
       cursor->right=temp->right;
       parent->right=cursor;
       cursor->left=temp->left;
       delete temp; 
    }
    else if(parent->left == temp && temp->right == NULL && temp->left != NULL)
    {
        parent->left = temp->left;
        delete temp;
    }
    else if(parent->left == temp && temp->left == NULL && temp->right != NULL)
    {
        parent->left = temp->right;
        delete temp;
    }
    else if (parent->right == temp && temp->left != NULL && temp->right == NULL)
    {
        parent->right = temp->left;
        delete temp;
    }
    else if (parent->right == temp && temp->left == NULL && temp->right != NULL)
    {
        parent->right = temp->right;
        delete temp;
    }
    cursor=parent;
    return true;
}

/******************************************************************** 
FUNCTION:			PrintPre
DESCRIPTION:		Prints the data of a binary search tree in the
					order Root(Left)(Right)
WRITER(S):			Group
*********************************************************************/
void BST::PrintPre(ostream& os)
{
	if(root!=NULL)    
        PrintPreHelp(os, root);
    else
        os << "[]";
}

/******************************************************************** 
FUNCTION:			PrintPost
DESCRIPTION:		Prints the data of a binary search tree in the
					order (Left)(Right)Root
WRITER(S):			Group
*********************************************************************/
void BST::PrintPost(ostream& os)
{
	if(root!=NULL)    
        PrintPostHelp(os, root);
    else
        os << "[]";
}

/******************************************************************** 
FUNCTION:			PrintIn
DESCRIPTION:		Prints the data of a binary search tree in
					numerical order
WRITER(S):			Group
*********************************************************************/
void BST::PrintIn(ostream& os)
{
    if(root!=NULL)    
        PrintInHelp(os, root);
    else
        os << "[]";
}

/******************************************************************** 
FUNCTION:			Find
DESCRIPTION:		Returns the pointer to a node that contains
					a value (e) to be found; returns NULL if the
					data was not found
WRITER(S):			Group
*********************************************************************/
BNode* BST::Find(int e)//cursor at located node or rightmost node
{
	if(root==NULL)
		return NULL;
	else
	{
		FindHelp(e,root);
		if(cursor->data==e)
            return cursor;
        else
            return NULL;
	}
}

/******************************************************************** 
FUNCTION:			AtCursor
DESCRIPTION:		Returns a pointer to the cursor
WRITER(S):			Group
*********************************************************************/
BNode* BST::AtCursor()const
{
    return cursor;
}

/******************************************************************** 
FUNCTION:			GoToBeginning
DESCRIPTION:		Sets the cursor of a BST to the smallest number
					of the tree
WRITER(S):			Group
*********************************************************************/
void BST::GoToBeginning()
{
	if(root != NULL)
	{
		BNode* current = root;
		
		while(current->left != NULL)
			current = current->left;
		
		cursor = current;
	}
}

/******************************************************************** 
FUNCTION:			GoToEnd
DESCRIPTION:		Sets the cursor of a BST to the largest number
					of the tree
WRITER(S):			Group
*********************************************************************/
void BST::GoToEnd()
{
	if(root != NULL)
	{
		BNode* current = root;
    
		while(current->right != NULL)
			current = current->right;
    
		cursor = current;
	}
}

/******************************************************************** 
FUNCTION:			GoToNext
DESCRIPTION:		Moves the cursor to the next number in numeric
					order
WRITER(S):			Group
*********************************************************************/ 
void BST::GoToNext()
{
	if(root != NULL)
	{
		BNode* temp;

		//Block For Checking End of BST
		temp = cursor;
		GoToEnd();
		if(temp == cursor)
		{
			GoToBeginning();
		}
		//ENDBLOCK
		else
		{
			cursor = temp;

            temp = Parent(cursor);

			if(cursor->right == NULL && temp->data > cursor->data)//Leaf Node that is on the left of its parent.
			{
				cursor = temp;
			}
			else if(cursor->right == NULL && temp->data < cursor->data)//Leaf on the right side of a parent.
			{
				while(temp->data < cursor->data)
				{
					cursor = temp;
					temp = Parent(cursor);
				}
				cursor = temp;
			}
			else//Move to own right. Also checks if what was moved to has a left if so moves to it.
			{
				cursor = cursor->right;
				while(cursor->left != NULL)
				{
					cursor = cursor->left;
				}
			}
		}
	}
}
 
/******************************************************************** 
FUNCTION:			GoToPrev
DESCRIPTION:		Moves the cursor to the previous number in numeric
					order
WRITER(S):			Group
*********************************************************************/
void BST::GoToPrev()
{
	if(root != NULL)
	{
		BNode* temp;

		//Block For Checking Beginning of BST
		temp = cursor;
		GoToBeginning();
		if(temp == cursor)
		{
			GoToEnd();
		}
		//ENDBLOCK
		else
		{
			cursor = temp;

            temp = Parent(cursor);

			if(cursor->left != NULL)
			{
                cursor = cursor->left;
                while(cursor->right != NULL)
                {
                    cursor = cursor->right;   
                }   
            }
            else
            {
                if(temp->left == cursor)
                {
                    while(temp->data > cursor->data)
                    {
                        cursor = Parent(cursor);
                        temp = Parent(temp);
                    }
                }
                cursor = Parent(cursor);
            }
		}
	}
}

/******************************************************************** 
FUNCTION:			ClearList
DESCRIPTION:		Completely removes all the data within a BST
WRITER(S):			Group
*********************************************************************/
void BST::ClearList()
{
    if(root != NULL)
        ClearListHelper(root);
    root = NULL;
}

/******************************************************************** 
FUNCTION:			CopyList
DESCRIPTION:		Creates a copy of a BST passed in
WRITER(S):			Group
*********************************************************************/
BNode* BST::CopyList(BNode* n)// to be called by copy constructor and assignment
{
    BNode* temp = new BNode;
    temp->data = n->data;
    
    if(n->left != NULL)
        temp->left = CopyList(n->left);
    
    if(n->right != NULL)
        temp->right = CopyList(n->right);
        
    return temp;
}

/******************************************************************** 
FUNCTION:			Empty
DESCRIPTION:		Returns whether or not a tree is empty
WRITER(S):			Group
*********************************************************************/
bool BST::Empty()const
{
	if(root==NULL)
		return true;
	else
		return false;
}
