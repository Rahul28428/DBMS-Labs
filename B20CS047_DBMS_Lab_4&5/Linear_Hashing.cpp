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
    cout<<A[hashFunction(book_id)].Book_Name<<endl;
    // return s;
}


/***********************************************************/
unsigned int BUCKETSIZE=4;
unsigned int GLOBAL_BUCKET_ORDER = 3;
class Block {
    vector<int> records;
    Block *overflow;

    public:
    Block() {
        overflow = NULL;
        records.clear();
    }

    bool isPresent(int x) {
        Block *node = this;
        while(node) {
            for(unsigned int i = 0; i < node->records.size(); i++) {
                if(node->records[i] == x) {
                    return true;
                }
            }
            node = node->overflow;
        }
        return false;
    }

    void add(int x) {
        // as sizeof(int) is 4
        if(records.size() <=  BUCKETSIZE) {
            records.push_back(x);
        }
        else {
            if(overflow == NULL) {
                overflow = new Block();
            }
            overflow->add(x);
        }
    }

    void clearElements(vector<int> &v) {
        for(unsigned int i = 0; i < records.size(); i++) {
            v.push_back(records[i]);
        }
        records.clear();
        if(overflow) {
            overflow->clearElements(v);
            delete overflow;
            overflow = NULL;
        }
    }

    void print() {
        Block *node = this;
        while(node) {
            for(unsigned int i = 0; i < node->records.size(); i++) {
                cout << node->records[i] << ' ';
            }
            node = node->overflow;
        }
        cout << '\n';
    }

};

class HashTable {
    int numRecords, numBits;
    vector<Block *> buckets;
    int block_to_split=0;
    public:
    HashTable() {
        // initial configuration of Hash table
        numRecords = 0;
        numBits = 1;
        for(int i=0; i<GLOBAL_BUCKET_ORDER; i++){
            buckets.push_back(new Block());
        }
    }

    unsigned int hash(int x) {
        unsigned int mod = (1 << numBits);
        return (unsigned int)(x % buckets.size());
    }

    int occupancy() {
        
        double ratio = 1.0 * numRecords / buckets.size();
        return (int)(100 * (ratio /BUCKETSIZE)); //Since the bucket size is 4
    }

    bool isPresent(int x) {
        unsigned int k = hash(x);
        if(k >= buckets.size()) {
            k -= (1 << (numBits - 1));
        }
        if(buckets[k]->isPresent(x)) {
            return true;
        }
        return false;
    }

    void insert(int x) {
        unsigned int k = hash(x);
        if(k >= buckets.size()) {
            k -= (1 << (numBits - 1));
        }
        buckets[k]->add(x);
        numRecords++;
        while(occupancy() >= 75) {
            int t=buckets.size();
            for(int i=0; i<t; i++){
                buckets.push_back(new Block());
            }
            //buckets.push_back(new Block());
            numBits = ceil(log2((double)buckets.size()));
            // split old bucket and rehash
            //k = buckets.size() - 1 - (1 << (numBits - 1));
            k=block_to_split;
            cout<<"Splitting Bucket: "+to_string(k)<<endl;

            block_to_split++;
            vector<int> v;
            buckets[k]->clearElements(v);
            for(unsigned int i = 0; i < v.size(); i++) {
                buckets[hash(v[i])]->add(v[i]);
            }
        }
        //print();
    }

    void print() {
        for(unsigned int i = 0; i < buckets.size(); i++) {
            cout << i << " -> ";
            buckets[i]->print();
        }
        cout << '\n';
    }

};



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

    cout<<"Created Table Successfully!"<<endl;
    //if(A.find(hashFunction("Anim_CS_0319")) == A.end())cout<<"nice";
    // cout<<A[hashFunction("Anim_CS_0319")].Book_Name;
    cout<<"Enter Bucket Size: "<<endl;
    cin>>BUCKETSIZE;
    cout<<"Enter Global Bucket Order: "<<endl;
    cin>>GLOBAL_BUCKET_ORDER;
    //Trying LINEAR Hashing
    HashTable h;
    cout<<"Linear hashing"<<endl;
    for(auto i : A){
        h.insert(i.first);
        cout<<endl;
        h.print();
        cout<<endl;
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
	if(h.isPresent(hashFunction("Anim_CS_0319"))){
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
    
    // display();
    return 0;
}