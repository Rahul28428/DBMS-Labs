// Searching a key on a B-tree in C++

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono; //Time


/***********************************************************************************/
struct Library  //Structure to store the database of books
{
    string Author_ID;
    string Book_ID;
    string Book_Name;
    string Author_Name;
};
// int get_hash(string s) {
//     const int p = 11111, m = 400;
//     int hash = 0;
//     long p_pow = 1;
//     int n=s.length();
//     for(int i = 0; i < n; i++) {
//         hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
//         p_pow = (p_pow * p) % m;
//     }
//     // if(hash<0)hash = hash*-1;
//     return hash;
// }

map<int,struct Library> A;

const int PRIME_CONST = 31;
//The below function hashes the book_id
int hashFunction(string key) {  // Adding ASCII values of characters in the book_id and then adding the last 4 characters (book_number) to it.
    int hashCode = 0;
    for (int i = 0; i < key.length()-4; i++) {
        hashCode += key[i];
    }
    return abs(hashCode+stoi(key.substr(key.size() - 4)));
}




void insert_table(string Auth_id, string book_id, string Author_Name, string book_name){
    Library s;
    s.Author_ID = Auth_id;
    s.Book_ID = book_id;
    s.Book_Name = book_name;
    s.Author_Name = Author_Name;
    A.insert({hashFunction(book_id),s});
    cout<<hashFunction(book_id)<<" ";
    cout<<A[hashFunction(book_id)].Book_Name<<" ";
    // return s;
}


/***********************************************************/



class TreeNode {
  int *keys;
  int t;
  TreeNode **C;
  int n;
  bool leaf;

   public:
  TreeNode(int temp, bool bool_leaf);

  void insertNonFull(int k);
  void splitChild(int i, TreeNode *y);
  void traverse();

  TreeNode *search(int k);

  friend class BTree;
};

class BTree {
  TreeNode *root;
  int t;

   public:
  BTree(int temp) {
    root = NULL;
    t = temp;
  }

  void traverse() {
    if (root != NULL)
      root->traverse();
  }

  TreeNode *search(int k) {
    return (root == NULL) ? NULL : root->search(k);
  }

  void insert(int k);
};

TreeNode::TreeNode(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new TreeNode *[2 * t];

  n = 0;
}

void TreeNode::traverse() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->traverse();
    cout << " " << keys[i];
  }

  if (leaf == false)
    C[i]->traverse();
}

TreeNode *TreeNode::search(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k);
}

void BTree::insert(int k) {
  if (root == NULL) {
    root = new TreeNode(t, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      TreeNode *s = new TreeNode(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);

      root = s;
    } else
      root->insertNonFull(k);
  }
}

void TreeNode::insertNonFull(int k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}

int main() {
    BTree t(3);
    insert_table("An_Ch_0103","Aest_AC_0103","Anjan Chatterjee","The Aesthetic Brain");
    insert_table("An_Da_0104","Self_AD_0104","Antonio Damasio","Self Comes to Mind");
    insert_table("Ca_Sa_0319","Anim_CS_0319","Carl Safina","What Animals Think");
    insert_table("Jo_Ro_1018","Deat_JR_1018","Joanne K. Rowling","Deathly Hallows_Harry Potter");
    insert_table("Jo_Ro_1018","Fant_JR_1018","Joanne K. Rowling","Fantastic Beasts and Where to  Find Them");
    insert_table("Jo_Ro_1018","Gobl_JR_1018","Joanne K. Rowling","Goblet of Fire_Harry Potter");
    insert_table("Jo_Ro_1018","Phil_JR_1018","Joanne K. Rowling","Philosophers Stone_Harry Potter");
    insert_table("Jo_Ro_1018","Pris_JR_1018","Joanne K. Rowling","Prisoner of Azkaban_Harry Potter");
    insert_table("La_Ch_1203","Mind_LC_1203","Lars Chittka","The Mind of a Bee");
    insert_table("Ma_Mi_1313","Emot_MM_1313","Marvin Minsky","Emotion Machine");
    insert_table("Ma_Mi_1313","Soci_MM_1313","Marvin Minsky","Society of Mind");
    insert_table("Pe_Wo_1623","Aunt_PW_1623","Pelham G. Wodehouse","Aunts Arent Gentlemen");
    insert_table("Pe_Wo_1623","Wode_PW_1623","Pelham G. Wodehouse","Wodehouse at the Wicket");
    insert_table("Vi_Ra_2218","Emer_VR_2218","Vilayanur Ramachandran","The Emerging Mind");
    insert_table("Vi_Ra_2218","Phan_VR_2218","Vilayanur Ramachandran","Phantoms in the Brain");

    cout<<"Created Table Successfully! The hased values are stored in the map 'A'. "<<endl;
    for(auto i : A){
        t.insert(i.first);
        //cout<<endl;
        cout<<"Successfully Inserted in B-Tree: "+to_string(i.first)<<endl;
    }

    cout<<endl;

	auto start = high_resolution_clock::now();

	cout<<"Searching new enrty according to question 5"<<endl;
	//Inserting new entry for question 5
	// insert_table("Ko_Ya_2218","Find_KY_2000","Kobi Yamada","Finding Muchness");
	// int new_hashValue = hashFunction("Find_KY_2000");
	// insert(new_hashValue);
	// cout<<"Inserted successfully"<<endl;
	// display();
	if(t.search(hashFunction("Anim_CS_0319"))){
		cout<<"Found"<<endl;
	}
	else{
		cout<<"Not Found"<<endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout<<"Time taken to insert (in microseconds): "<<endl;
	cout << duration.count() << endl;
    cout<<endl;
    // int k = 1048;
    // (t.search(k) != NULL) ? cout << endl
    //                 << k << " is found"
    //             : cout << endl
    //                 << k << " is not Found";

    // k = 2;
    // (t.search(k) != NULL) ? cout << endl
    //                 << k << " is found"
    //             : cout << endl
    //                 << k << " is not Found\n";
    }