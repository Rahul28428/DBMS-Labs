#include <iostream>
#include <bits/stdc++.h>


#include <chrono>
using namespace std::chrono; //Time

#define pb push_back
#define all(a) a.begin(),a.end()
#define cpresent(container,element) (find(all(container),element)!=container.end())
#define rep(i, a, b) 	for(int i = a; i < b; ++i)
using namespace std;
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
    cout<<A[hashFunction(book_id)].Book_Name<<endl;
    // return s;
}
//************************************************************************************************


struct Bucket
{
	int ld=0;
	vector<int>a;
};
map<int,Bucket *>bmap;
int gd,bucket_capacity;
void display()
{
	rep(i,0,1<<gd)
	{
		/* code */
		cout<<"Local depth of the bucket is : "<<bmap[i]->ld<<"\n";
		for(auto j : bmap[i]->a)
			cout<<j<<" ";
		cout<<"\n";
	}
}

int search(int n)
{
	int h = n & ((1<<gd) - 1);
	return cpresent(bmap[h]->a,n);
}

void split(int sp_Index,Bucket * sp_Bucket)
{
	Bucket * newB = new Bucket;
	vector<int>temp;
	for(auto i : sp_Bucket->a)
	{
		temp.pb(i);
	}
	
	sp_Bucket->a.clear();
	
	if(sp_Bucket->ld == gd)
	{
		bmap[sp_Index ^ (1<<gd)] = newB;
		if(gd!=0)
		{
// 			for (int i = 0; i < (1<<gd); ++i)
			rep(i,0,1<<gd)
			{
				/* code */
				if(i!=sp_Index)
					bmap[i ^ (1<<gd)] = bmap[i];
			}
		}
		gd++;
		newB->ld = ++ sp_Bucket->ld;
		for(auto i : temp)
		{
			int h = i & ((1<<gd) -1);
			bmap[h]->a.pb(i);
		}
	}
	else
	{
		int k = sp_Index & (1<<(sp_Bucket->ld) - 1);
		vector<int>indices;
// 		for (int i = 0; i < (1<<gd); ++i)
		rep(i,0,1<<gd)
		{
			/* code */
			int last = i & (1<<(sp_Bucket->ld)) - 1;
			if(last==k)
				indices.pb(i);
		}
		newB->ld = ++sp_Bucket->ld;
// 		for (int i = indices.size()/2; i < indices.size(); ++i)
		rep(i, indices.size()/2, indices.size())
		{
			bmap[indices[i]] = newB;
		}

		for(auto i : temp)
		{
			int h = i & ((1<<gd) -1);
			bmap[h]->a.pb(i);
		}
	}

}
void insert(int n)
{
	int h = n & ((1<<gd) - 1);
	if(bmap[h]->a.size()<bucket_capacity){
        bmap[h]->a.pb(n);
        cout<<"Successfully inserted: "<<n<<endl;
    }
	else
	{
		split(h,bmap[h]);
		insert(n);
        cout<<"Successfully inserted: "<<n<<endl;
	}
    
}

void merge()
{
	for(int i = 0; i<(1<<(gd-1));i++)
	{
		int h = i & ( ( 1<< ((bmap[i]->ld)-1) ) - 1);
		/*Current and Matched are pair of matching data buckets having ld-1 common suffix*/
		Bucket *curr = bmap[i];
		Bucket *matched = bmap[ i ^ (1<<(bmap[i]->ld-1)) ];
		if(curr != matched)
		{
			int sz = curr->a.size() + matched->a.size();
			if(sz <= bucket_capacity)
			{
				copy(all(matched->a),back_inserter(curr->a));
				vector<int>inds;
				for(auto i : bmap)
				{
					if(i.second==matched)
						inds.pb(i.first);
				}
				delete matched;
				for(auto j : inds)
					bmap[j] = bmap[i];
				bmap[i]->ld --;
			}
		}
	}
}

void shrink()
{
	set <Bucket *>buckets;
	for(auto i : bmap)
		buckets.insert(i.second);
	int count = 0;
	int sz = buckets.size();
	for(auto i : buckets)
		if ( (gd - (i->ld)) == 1)
			count++;
	if(count==sz)
		gd--;
}
void del(int n)
{
	if(search(n))
	{
		
		/*Deleting the entry */
		for(auto i : bmap)
		{
			auto it = find(all(i.second->a),n);
			if(it!=i.second->a.end())
			{
				i.second->a.erase(it);
				break;
			}
		}
		/*Merging the pair of data buckets if possible*/
		merge();

		/*If all the buckets have local depth less than global depth then shrink the directory*/
		shrink();

		cout<<"Number deleted successfully\n";
	}
	else
		cout<<"Element not found : \n";
}
void menu()
{
	int choice;
	int n;
	while(1)
	{
		cout<<"1. Insertion\n";
		cout<<"2. Deletion\n";
		cout<<"3. Display\n";
		cout<<"4. Search\n";
		cout<<"5. Exit\n";
		cout<<"--------------------\n";
		cout<<"Enter your choice : \n";
		cin>>choice;
		cout<<"--------------------\n";
		switch(choice)
		{
			case 1:
				cout<<"Enter the number to be inserted : \n";
				cin>>n;
				insert(n);
				cout<<"Number inserted successfully\n";
				break;
			case 2:
				cout<<"Enter the number to be deleted : \n";
				cin>>n;
				del(n);
				break;
			case 3:
				display();
				break;
			case 4:
				cout<<"Enter the number to be searched : \n";
				cin>>n;
				if(search(n))
					cout<<"Found\n";
				else
					cout<<"Not Found\n";
				break;
			case 5:
				exit(0);
			default:
				cout<<"Invalid choice !";
		}
	}
}


int main() 
{
    cout<<"Creating Table"<<endl;
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

	
    cout<<"Created Table Successfully! "<<endl;
    //if(A.find(hashFunction("Anim_CS_0319")) == A.end())cout<<"nice";
    // cout<<A[hashFunction("Anim_CS_0319")].Book_Name;

    //Trying Extendible Hashing
	cout<<endl;
	cout<<"Extendible Hashing:"<<endl<<endl;
    cout<<"Enter bucket capacity : \n";
	cin>>bucket_capacity;
	bmap[0] = new Bucket;
    //menu();
    //cout<<gd<<endl;
    for(auto i : A){
        insert(i.first);
        cout<<endl;
        display();
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
	if(search(hashFunction("Anim_CS_0319"))){
		cout<<"Found"<<endl;
	}
	else{
		cout<<"Not Found"<<endl;
	}
	cout<<endl; 
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout<<"Time taken to search (in microseconds): "<<endl;
	cout << duration.count() << endl;

	
    
    // display();
    return 0;
}