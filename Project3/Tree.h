#ifndef TREE_H__	//file Tree.h
#define TREE_H__	//Tree, ADT definition

#include <iostream>
#include <iomanip>
using namespace std;
//*******************************************************************************
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 4/15/2021
//	ADT name: Tree
//	ADT file: Tree.h
//
//	Class Name: Tree
//
//	Data Elements: A Tree is comprised of TreeNode<BaseData>'s.
//
//
//	A Tree object has 3 private data members:
//				TreeNode<BaseData>  *root - creates a root for the tree
//				info arr[26] - holds an array of info copied from mylist Huffman table
//				string message - message read in from user console to output back 
//					to console after decoding to verify correct results.
//
//	A Tree object has no friend functions.
//		
//	An Tree object has the following public functions:
//				void make_tree(list<TreeNode<BaseData>> mylist) - creates a tree
//					from a list of TreeNodes made of info. Prints Preorder traversal
//					to display Huffman Tree after completion.
//				list<TreeNode<BaseData>> getlist() - read in from user input file 
//					while character isn't * symbol. adds letter read in to 
//					std::list<info>. increments weight of letter with each successive
//					add. returns mylist for use elsewhere.
//				void print_Huff_table(list<TreeNode<BaseData>> mylist) - displays
//					the Huffman Table 
//				void encode(TreeNode<BaseData>* p, string code) - Encodes a message
//					by following the Huffman tree - "1" is left, "0" is right
//				void store_table() - asks user to input a filename to store Huffman
//					table in, stores table.
//				void store_msg() - asks user to input a filename to store Encoded
//					message in, stores encoded message.
//				void decode() - Asks user to input two files - one for the Huffman
//					table, and one for the encoded message. Creates a temp array of 
//					info to hold new Huffman table info from user file. Reads through
//					encoded message, using given Huffman Table.
//		 
//					   
//*******************************************************************************
//		Class Tree DEFINITION SECTION
//*******************************************************************************




//*******************************************************************************
//	Programmer: Patrick Sadowy
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 4/15/2021
//	ADT name: info
//	ADT file: Tree.h
//
//	Struct Name: info
//
//	Data Elements: An info is comprised of a letter, weight, and a code.
//
//*******************************************************************************
//		Struct info DEFINITION SECTION
//*******************************************************************************
struct info
{

	char letter;
	int weight = 0;
	string code = "";
	bool operator < (info& n)
	{
		return weight < n.weight;
	}
};

//header file for a Binary tree with the ordering property
//BaseData class is assumed to have overloaded relational
//> < == !=  <= >=       operators if not a base type

template <class BaseData>
struct  TreeNode {
	info TreeData;
	TreeNode* left = nullptr, * right = nullptr;
	//overloaded relational operator to abide by ordering Conventions
	bool operator < (TreeNode<BaseData>& n)
	{
		if (this->TreeData.letter == '*')
		{
			if (this->TreeData.weight == n.TreeData.weight)
			{
				return this->TreeData.weight < n.TreeData.weight;
			}
		}
		if (this->TreeData.weight == n.TreeData.weight)
		{
				return this->TreeData.letter < n.TreeData.letter;
		}
		
		
		return this->TreeData.weight < n.TreeData.weight;
	}
};

//these are file level because traversals are recursive
//void openOutFile() ;  //probably not the same as yours
//ofstream opf;         //opf is ofstream object used

template <class BaseData>
class  tree
       {      //friend class stated here;
       public  :
		 tree();
		 ~tree();
		 tree(tree<BaseData> &t);
		 tree<BaseData> & operator = (const tree<BaseData> &t);
		 void insert(BaseData &item);
		 void SearchAndDestroy(BaseData target);
		 void writeTree(int) ;
		 int fullTree() const;
		 int emptyTree() const;
		 //new functions
		 void make_tree(list<TreeNode<BaseData>> mylist);
		 list<TreeNode<BaseData>> getlist();
		 void print_Huff_table(list<TreeNode<BaseData>> mylist);
		 void encode(TreeNode<BaseData> *p, string code);
		 void store_table();
		 void store_msg();
		 void decode();
		 
		 

       protected:   //helping functions
		 void remove(TreeNode<BaseData> * &current);
		 void inOrder(TreeNode<BaseData> *);
		 void preOrder(TreeNode<BaseData> *);
		 void postOrder(TreeNode<BaseData> *);
		 void destroy(TreeNode<BaseData> *p);
		 void copyTreeNode (TreeNode <BaseData>** into,
					 TreeNode<BaseData>* from);
		 void insertNode(TreeNode<BaseData>** into,
					  BaseData& item);
		 TreeNode <BaseData>  getnode(TreeNode<BaseData>* llink,
			 TreeNode<BaseData>* rlink, int weightsum);

       private:
		 TreeNode<BaseData>  *root;
		 //added new members
		 info arr[26];
		 string message;

}; //end class Tree Definition section

//constructor
template <class BaseData>
tree<BaseData>::tree()
{
	root = 0;
}

//destructor
template <class BaseData>
tree<BaseData>::~tree()
{
  if (root)
	destroy (root);
}


//helping function for destructor and copying functions
template <class BaseData>
void tree<BaseData>::destroy(TreeNode<BaseData> *p)
{  if (p)
    { destroy(p->left);
      destroy(p->right);
      delete p;
    }
}

//copy constructor: uses helping function copyTreeNode
template <class BaseData>
tree<BaseData> :: tree(tree<BaseData> &t)
{
    root = 0;
    copyTreeNode(&root,t.root);
}

//copy constructor: uses helping functions destroy and copyTreeNode
template <class BaseData>
tree<BaseData> &  tree<BaseData>:: operator = (const tree<BaseData> &t)
{   if (this == &t) return *this;
    if (root)
	destroy(root);
    root = 0;
    copyTreeNode(&root,t.root);
    return *this;
}

//helping function
template <class BaseData>
void tree<BaseData>::inOrder(TreeNode<BaseData> *p)
{   
	static int index = 0;
	if (p != nullptr)
     { 
	   inOrder(p->left);
	   if (p->TreeData.letter != '*')
	   {
		   cout << p->TreeData.letter << " " << p->TreeData.code << endl;
		   arr[index].letter = p->TreeData.letter;
		   if (p->TreeData.letter != ' ')
		   {
			  arr[index].code = p->TreeData.code;
		   }
		   index++;
	   }
       inOrder(p->right);
     }
}//END InOrder;

//helping function
template <class BaseData>
void tree<BaseData>::preOrder(TreeNode<BaseData> *p)
{
	static int index = 0;
   if (p != nullptr)
     {
	   if (p->TreeData.letter != '*')
	   {
		   cout << p->TreeData.letter << " " << p->TreeData.code << endl;
		   arr[index].letter = p->TreeData.letter;
		   if (p->TreeData.letter != ' ')
		   {
			   arr[index].code = p->TreeData.code;
		   }
		   index++;
	   }
       preOrder(p->left);
       preOrder(p->right);
     }
}//END PreOrder;

//helping function
template <class BaseData>
void tree<BaseData>::postOrder(TreeNode<BaseData> *p)
{  
	static int index = 0;
	if (p != nullptr)
    { postOrder(p->left);
      postOrder(p->right);
	  if (p->TreeData.letter != '*')
	   {
		   cout << p->TreeData.letter << " " << p->TreeData.code << endl;
		   arr[index].letter = p->TreeData.letter;
		   if (p->TreeData.letter != ' ')
		   {
			  arr[index].code = p->TreeData.code;
		   }
		   index++;
	   }
     }
}//END PostOrder; */

//searches for target of the base data type and if found it removes it
//uses helping function remove
template <class BaseData>
void tree<BaseData>::SearchAndDestroy(BaseData target)
{	TreeNode<BaseData> *previous, *current;

	current = root;
	previous = 0;
	while(current && (current->TreeData != target))
	   { 	previous = current;
		if (current->TreeData > target)
			current = current->left;
		else current = current->right;
	   }  //(*while*)
	if (!current)    //target not found
		{ cout << "target not found " << '\n';
		  return;
		}

	//remove requires the actual node in the tree
	if (current == root)  remove (root);
	else
		{if (previous->left == current) remove(previous->left);
		 else remove (previous->right);
		}

}//END SearchAndDestroy;

//helping function to search and destroy
//important:  the input is the actual pointer inside the tree

template<class BaseData>
void tree<BaseData>:: remove(TreeNode<BaseData>* &current)
{	TreeNode<BaseData> *previous, *temp;
// (*the pointer sent in is the parent (left or right) in the tree*)
       temp = current;
       if (current->left == 0 && current->right == 0)  //leaf node
	   current = 0;                                //parent is null
       else
	  {
	    if (current->left == 0)       //  no left child
		current = current->right; //  replace with right child
	    else                          //  has left child
	       {  temp = current->left;
		  previous = current;
		  while (temp->right != 0)
		   { previous = temp;     // locate TreeNode that has the
		     temp = temp->right;  // largest value smaller than
		   }                      // the value of TreeNode to be
					  // deleted
		  current->TreeData = temp->TreeData; // replace with
						//that TreeData
		  if (previous == current)      //  replace is left child
		      previous->left = temp->left;
		  else
		      previous->right = temp->left;// replace is down rt
						  // subtree of left child
	       }

	  }
    delete temp;
}//END Delete;

//returns true if the tree is empty   otherwise false
template<class BaseData>
int tree<BaseData> :: emptyTree()  const
{
return !root;
}

//returns true if the tree is full   otherwise false
template<class BaseData>
int tree<BaseData> :: fullTree()   const
{
	TreeNode<BaseData> *temp = new TreeNode<BaseData>;

	if (!temp) return 1;
	delete temp;
	return 0;
}


//inserts a data item of base data type into the tree
//uses helping function insertnode
template <class BaseData>
void tree<BaseData> ::insert(BaseData &item)
{
	insertNode(&root, item);
}


//helping function for insert
//this takes the address of a pointer to a node and inserts
//item into the ordered binary tree headed
//by that node.  This assumes overloaded comparison operators
//for class BaseData.
template <class BaseData>
void tree<BaseData>::insertNode(TreeNode<BaseData>** into, BaseData& item)
{
  if (!(*into))
	{*into = getnode(item);
	return;
	}
  if ( item.TreeData < (*into)->TreeData &&  !((*into)->left))
       (*into)->left = tree<BaseData>::getnode(item);
  else if (item.TreeData < (*into)->TreeData)
       insertNode (&((*into)->left),item);
  else if (item.TreeData >= (*into)->TreeData && !((*into)->right))
       (*into)->right = tree<BaseData>::getnode(item);
  else insertNode ( &((*into)->right), item);

}

//gets storage for a new node to be inserted into the tree
template <class BaseData>
TreeNode <BaseData>  tree<BaseData>::getnode(TreeNode<BaseData> *llink, 
										TreeNode<BaseData>* rlink, int weightsum)
{
	TreeNode<BaseData> *temp = new TreeNode<BaseData>;
	if (temp)
	  {
		temp->TreeData.letter = '*';
		temp->TreeData.weight = weightsum;
		temp->left = llink;
		temp->right = rlink;
	  }
	  return *temp;
}

//helping function for copy constructor and =operator
//it copies the ordered tree pointed to by "from" into
//another ordered binary tree whose root
//node has its address in the "into" pointer.

//helping function for copy constructor and =operator
template <class BaseData>
void tree<BaseData>::copyTreeNode (TreeNode <BaseData>** into,
					TreeNode<BaseData>* from)
{
	if(!from) return;
	insertNode( &(*into), from->TreeData);
	copyTreeNode( &(*into), from->left);
	copyTreeNode(&(*into), from->right);
}

//writes the tree in three different orders: pre,in, post and uses the respective helping functions
//requires input of a choice 1-2-3 for the order desired.
template <class BaseData>
void tree<BaseData>::writeTree(int choice)
{    switch (choice) {
	case 1 : tree<BaseData>::preOrder(root);
		 break;
	case 2 : tree<BaseData>::inOrder(root);
		 break;
	case 3 : tree<BaseData>::postOrder(root);
		 break;
	default :  cout << "tree not written" << '\n';
	}//end switch
}//end write Tree





//ADDED ALL THESE FUNCTIONS BELOW





//*******************************************************************************
//	Function Name: make_tree
//	Purpose: creates a tree from a list of TreeNodes made of info. Prints Preorder 
//		traversal to display Huffman Tree after completion.
//	Parameters: Variable mylist of datatype list<TreeNode<BaseData>>.
//	Return value: void/none.
//	Data Members Accessed/Altered: root - set front of list as root
//	Functions Called: mylist.size() - find size of the list
//					  mylist.front() - access front of the list
//					  mylist.pop_front() - remove front of the list
//					  mylist.push_back(getnode(temp1, temp2, sum)) - add item to 
//						back of the list
//					  getnode(temp1, temp2, sum) - create a new sub tree of nodes
//					  mylist.sort() - sort the list
//					  encode(root, temp) - encode the message starting at root, using
//						inorder method
//					  writeTree(2) - display the tree in selected traversal ordering,
//						option 2 is Inorder Display.
//*******************************************************************************
template <class BaseData>
void tree<BaseData>::make_tree(list<TreeNode<BaseData>> mylist)
{
	string temp;
	TreeNode<info>* temp1, * temp2;
	int sum;
	while (mylist.size() != 1)
	{
		temp1 = new TreeNode<info>;
		temp2 = new TreeNode<info>;

		//pop front 2 items from list and hold in temp
		//value. Used to create a new tree.
		temp1->TreeData.letter = mylist.front().TreeData.letter;
		temp1->TreeData.weight = mylist.front().TreeData.weight;
		temp1->left = mylist.front().left;
		temp1->right = mylist.front().right;
		mylist.pop_front();

		temp2->TreeData.letter = mylist.front().TreeData.letter;
		temp2->TreeData.weight = mylist.front().TreeData.weight;
		temp2->left = mylist.front().left;
		temp2->right = mylist.front().right;
		mylist.pop_front();
		sum = temp1->TreeData.weight + temp2->TreeData.weight;

		mylist.push_back(getnode(temp1, temp2, sum));
		mylist.sort();
	}
	
	root = &mylist.front();

	cout << endl << "Creating huffman coding... \n";
	encode(root, temp);
	writeTree(2);
}

//*******************************************************************************
//	Function Name: get_list
//	Purpose: read in from user input file while character isn't * symbol. adds letter
//		read in to std::list<info>. increments weight of letter with each successive
//		add. returns mylist for use elsewhere.
//	Parameters: none.
//	Return value: list<TreeNode<BaseData>>.
//	Data Members Accessed/Altered: message - append to message string
//	Functions Called: message.size() - find size of the string
//					  mylist.front() - access front of the list
//					  mylist.pop_front() - remove front of the list
//					  mylist.push_back(info_obj) - add item to 
//						back of the list
//					  mylist.sort() - sort the list
//					  inFile.open(filename) - open input file
//					  exit(0) - exit program if executed
//					  inFile.close() - close input file
//					  message.append(temp) - append string with additional text
//					  mylist.begin() - point to beginning of the list
//					  mylist.end() - point to end of list
//*******************************************************************************
template <class BaseData>
list<TreeNode<BaseData>> tree<BaseData>::getlist()
{
	list<TreeNode<info>> mylist;
	TreeNode<info> info_obj;
	bool inlist = false;
	ifstream inFile;
	string filename, temp;


	cout << "Please enter text file name: ";
	cin >> filename;
	cout << '\n';

	//open input file
	inFile.open(filename);
	if (!inFile)
	{
		cout << "Unable to open input file. Terminating program. \n";
		exit(0);
	}

	//read in from file while character isn't * symbol.
	//adds letter read in to std::list<info>.
	//increments weight of letter with each successive add.
	inFile >> info_obj.TreeData.letter;
	while (info_obj.TreeData.letter != '*')
	{
		if (info_obj.TreeData.letter != ' ')
		{
			temp = info_obj.TreeData.letter;
			message.append(temp);
		}
		for (list<TreeNode<info>>::iterator it = mylist.begin(); it != mylist.end(); it++)
		{
			if (it->TreeData.letter == info_obj.TreeData.letter)
			{
				it->TreeData.weight++;
				inlist = true;
			}
		}
		if (inlist == false)
		{
			info_obj.TreeData.weight++;
			mylist.push_back(info_obj);
		}

		inFile >> info_obj.TreeData.letter;
		info_obj.TreeData.weight = 0;
		inlist = false;
	}
	for (int i = 0; i < message.size(); i++)
	{
		cout << message[i];
	}
	cout << '*' << ' ';
	//close input file
	cout << " closing input file" << endl;
	inFile.close();
	//add all non-used letters to list
	for (int i = 0; i < 26; i++)
	{
		for (list<TreeNode<info>>::iterator it = mylist.begin(); it != mylist.end(); it++)
		{
			if (it->TreeData.letter == char(i + 97))
			{
				inlist = true;
			}
		}
		if (inlist == false)
		{
			info_obj.TreeData.letter = (char(i + 97));
			mylist.push_back(info_obj);
		}
		inlist = false;
	}
	//sort list
	mylist.sort();
	return mylist;
}

//*******************************************************************************
//	Function Name: print_Huff_table
//	Purpose: Displays the Huffman Table 
//	Parameters: list<TreeNode<BaseData>> mylist.
//	Return value: none.
//	Data Members Accessed/Altered: message - append to message string
//	Functions Called: mylist.begin() - point to beginning of the list
//					  mylist.end() - point to end of list
//*******************************************************************************
template <class BaseData>
void tree<BaseData>::print_Huff_table(list<TreeNode<BaseData>> mylist)
{
	//print out the Huffman Table.
	//also fill each TreeNode with info,
	//then insert Node into Tree
	cout << endl << "Printing huffman table: " << endl;
	for (list<TreeNode<info>>::iterator it = mylist.begin(); it != mylist.end(); it++)
	{
		cout << it->TreeData.letter << " " << it->TreeData.weight << endl;
	}
	cout << endl << endl;
}

//*******************************************************************************
//	Function Name: store_table
//	Purpose: Displays the Huffman Table 
//	Parameters: none.
//	Return value: none.
//	Data Members Accessed/Altered: arr - access the Huffman Table
//	Functions Called: c_str() - convert a string to proper file syntax
//					  outFile.open(filename.c_str()) - open output file
//					  outFile.close() - close output file
//*******************************************************************************
template <class BaseData>
void tree<BaseData>::store_table()
{
	ofstream outFile;
	string filename;
	cout << "Enter the name of the file to store the table: " << endl;
	cin >> filename;
	outFile.open(filename.c_str());
	
	for (int i = 0; i < 26; i++)
	{
		outFile << arr[i].letter << " " << arr[i].code << endl;
	}
	outFile << '*';
	outFile.close();
}

//*******************************************************************************
//	Function Name: Encode
//	Purpose: Encodes a message by following the Huffman tree - "1" is left, 
//		"0" is right.
//	Parameters: TreeNode<BaseData>* p, string code.
//	Return value: none.
//	Data Members Accessed/Altered: none.
//	Functions Called: encode(p->left, code + '1') - encode a 1 if left child
//					  encode(p->left, code + '0') - encode a 0 if right child
//*******************************************************************************
template <class BaseData>
void tree<BaseData>::encode(TreeNode<BaseData>* p, string code)
{
	if (p != nullptr)
	{
		encode(p->left, code + '1');
		if (p->TreeData.letter  != '*')
		{
			p->TreeData.code = code;
		}
		encode(p->right, code + '0');
	}
}

//*******************************************************************************
//	Function Name: store_msg
//	Purpose: Asks user to input a filename to store Encoded message in, stores 
//		encoded message.
//	Parameters: none.
//	Return value: none.
//	Data Members Accessed/Altered: arr - access the Huffman Table
//								   message - access the user message
//	Functions Called: c_str() - convert a string to proper file syntax
//					  outFile.open(filename.c_str()) - open output file
//					  outFile.close() - close output file
//					  message.size() - find size of the string
//*******************************************************************************
template<class BaseData>
void tree<BaseData>::store_msg()
{
	ofstream outFile;
	string filename;
	cout << "enter the file name to store the encoded message: ";
	cin >> filename;
	outFile.open(filename.c_str());
	for (int k = 0; k < message.size(); k++)
	{
		for (int i = 0; i < 26; i++)
		{
			if (arr[i].letter != ' ')
			{
				if (message[k] == arr[i].letter)
				{
					outFile << arr[i].code;
				}
			}
		}
	}
	outFile << '*';
	outFile.close();
}

//*******************************************************************************
//	Function Name: decode
//	Purpose: Asks user to input two files - one for the Huffman table, and one for
//		the encoded message. Creates a temp array of info to hold new Huffman table 
//		info from user file. Reads through encoded message, using given Huffman 
//		Table.
//	Parameters: none.
//	Return value: none.
//	Data Members Accessed/Altered: none.
//	Functions Called: c_str() - convert a string to proper file syntax
//					  inFile1.open(filename1.c_str()) - open input file
//					  inFile1.close() - close input file
//					  inFile2.open(filename2.c_str()) - open input file
//					  inFile2.close() - close input file
//					  exit(0) - exit program if executed
//					  inFile1.ignore(5, ' ') - ignore input until desired time
//					  getline(inFile1, temp_arr[index].code) - acquire string for
//						related letter & code
//*******************************************************************************
template<class BaseData>
void tree<BaseData>::decode()
{
	info temp_arr[27];
	int index = 0;
	ifstream inFile1, inFile2;
	string  filename1, filename2, temp;
	char x;
	cout << "enter input filename for Huffman encoding table: ";
	cin >> filename1;
	cout << '\n';

	//open input file
	inFile1.open(filename1.c_str());
	if (!inFile1)
	{
		cout << "Unable to open input file. Terminating program. \n";
		exit(0);
	}
	
	inFile1 >> temp_arr[index].letter;
	while (temp_arr[index].letter != '*')
	{
		inFile1.ignore(5, ' ');
		getline(inFile1, temp_arr[index].code);
		index++;
		inFile1 >> temp_arr[index].letter;
	}
	inFile1.close();



	cout << "uncompressing file ....\n";
	cout << "enter compressed message file name: ";
	cin >> filename2;
	cout << '\n';

	//open input file
	inFile2.open(filename2.c_str());
	if (!inFile2)
	{
		cout << "Unable to open input file. Terminating program. \n";
		exit(0);
	}
	inFile2 >> x;
	while (x != '*')
	{
		temp += x;
		for (int i = 0; i < 26; i++)
		{
			if (temp_arr[i].code == temp)
			{
				if (temp_arr[i].letter != '*')
				{
					cout << temp_arr[i].letter;
					temp = "";
				}
			}
		}
		inFile2 >> x;
	}
	inFile2.close();
}
#endif
