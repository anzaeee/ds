#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

/////////////////////////////////////////////////////	Shanzay Asad, 19I1998, CS-A		/////////////////////////////////////////////////////
// DS Assignment#2

/*
	* All signatures to be used for NODE type classes
*/

template <typename i, typename s, typename f> class MMD;
template <typename i, typename s> class AMD;
template <typename i, typename s, typename f> class AD;
template <typename i> class ADP;
template <typename i> class Tracks;
template <typename i> class Albums;


/*
	* All signatures to be used for LIST type classes
*/
template <typename i, typename s, typename f> class MMD_List;
template <typename i, typename s> class AMD_List;
template <typename i, typename s, typename f> class AD_List;
template <typename i> class ADP_List;
template <typename i> class Tracks_List;
template <typename i> class Albums_List;


/*
	* Global pointers to point to the HEAD of already created lists
*/

MMD<int, string, float>* MMDlist;
AMD<int, string>* AMDlist;
Tracks<int>* Tracklist;
Albums<int>* Albumslist;
AD<int, string, float>* ADlist;
ADP<int>* ADPlist;

/*
	* Function signatures that are to be implemented
*/

MMD<int, string, float>* Create_MMD(string path); //should return head of the MMD linkedlist
AMD<int, string>* Create_AMD(string path); //should return head of the AMD linkedlist
AD<int, string, float>* Create_AD(string path); //should return head of the AD linkedlist
ADP<int>* Create_ADP(string path); //should return head of the ADP linkedlist
MMD<int, string, float>* Search_Music(int MBID); //should return pointer to track having mbid = MBID
AMD<int, string>* Search_Author(int AID); //should return pointer to author having aid = AID
AD<int, string, float>* Search_Album(int ABID); //should return pointer to album having abid = ABID
ADP<int>* Search_Discography(int DID); //should return pointer to discography having did = DID
Tracks<int>* Search_Music_By_Album(int ABID); //should return singly linklist of "Tracks" in given album
Albums<int>* Search_Music_By_Author(int DID); //should return singly linklist of "Albums" in given discography

/*
	* Function signatures for functions I created for ease of access
*/
void Connect_AD();
void Connect_ADP();

/////////////////////////// NODES FOR ALL LISTS /////////////////////////////////
//
//Music Metadata DataBase (A doubly linked list)
template <typename i, typename s, typename f>
class MMD
{
public:
	//data members
	i mbid;
	s sname;
	s wname;
	s length;

	AD<i, s, f>* album;

	//connections
	MMD<i, s, f>* next;
	MMD<i, s, f>* previous;

	//constructor
	MMD()
	{
		next = NULL;
		previous = NULL;
		album = NULL;
	}
	MMD(i m, s str, s w, s l)
	{
		mbid = m;
		sname = str;
		wname = w;
		length = l;

		next = NULL;
		previous = NULL;
		album = NULL;
	}

};

//Author Metadata DataBase (A circular linked list)
template <typename i, typename s>
class AMD
{
public:
	//data members
	i aid;
	s name;
	s band;
	s gender;
	s genre;
	s dob;
	s cdate;

	//two way connections
	AD<i, s, float>* albums;
	ADP<i>* adp;


	//connections
	AMD<i, s>* next;

	//constructor
	AMD()
	{
		aid = 0;
		name = " ";
		band = " ";
		genre = " ";
		dob = " ";
		cdate = " ";

		next = NULL;
		albums = NULL;
		adp = NULL;
	}
	AMD(i a, s n, s b, s g, s d, s c, s gn) //parametrised constructor
	{
		aid = a;
		name = n;
		band = b;
		gender = g;
		dob = d;
		cdate = c;
		genre = gn;

		next = NULL;
		albums = NULL;
		adp = NULL;
	}

};



//Album DataBase (A circular linked list)
template <typename i, typename s, typename f>
class AD
{
public:
	//data members
	i abid;
	i aid;
	i notracks;
	s duration;
	s aname, publisher;

	AMD<i, s>* author;
	Tracks<i>* tracks;
	ADP<i>* adp;

	//connections
	AD<i, s, f>* next;

	AD()
	{
		next = NULL;
	}
	AD(i a, s an, i ai, s p, i n, s d)
	{
		abid = a;
		aname = an;
		aid = ai;
		publisher = p;
		notracks = n;
		duration = d;

		author = NULL;
		tracks = NULL;
		adp = NULL;
	}
};



//Author Discography Playlist (A circular linked list)
template <typename i>
class ADP //author discography
{
public:
	//data members
	i did;
	i aid;
	AMD<i, string>* author;
	Albums<i>* albums;

	//connections
	ADP<i>* next;
	ADP()
	{
		next = NULL;
		author = NULL;
		albums = NULL;
	}
	ADP(i d, i a)
	{
		did = d;
		aid = a;
		next = NULL;
		author = NULL;
		albums = NULL;
	}
};


//Tracks (A singly linked list)
template <typename i>
class Tracks
{
public:
	//data members
	i trackNumber;
	MMD<i, string, float>* trackRef;


	//connections
	Tracks<i>* next;

	Tracks()
	{
		next = NULL;
		trackRef = NULL;
	}
	Tracks(i t)
	{
		trackNumber = t;
		next = NULL;
		trackRef = NULL;
	}
};

//Albums (A singly linked list)
template <typename i>
class Albums
{
public:
	//data members
	i year;
	AD<i, string, float>* albumRef;

	//connections
	Albums<i>* next;

	Albums()
	{
		next = NULL;
		albumRef = NULL;
	}
	Albums(i y)
	{
		year = y;
		next = NULL;
		albumRef = NULL;
	}
};


////////// LIST IMPLEMENTATION ////////////////
template<typename i, typename s, typename f>
class MMD_List //List is a Doubly linked list
{
public:
	MMD<i, s, f>* head;
	MMD<i, s, f>* tail;
	MMD_List()
	{
		head = NULL;
		tail = NULL;
	}
	void MMDinsert(i M, s str, s w, s l)
	{
		if (head == NULL)	//When list is empty create head
		{
			head = new MMD<i, s, f>(M, str, w, l);
			head->next = NULL;
			head->previous = NULL;
			tail = head;
		}
		else
		{
			MMD<i, s, f>* temp = head;
			while (temp->next != NULL)
				temp = temp->next;

			temp->next = new MMD<i, s, f>(M, str, w, l);
			(temp->next)->previous = temp;
			tail = temp->next;
		}
	}
	MMD<i, s, f>* traverse(int mbid)
	{
		MMD<i, s, f>* n = MMDlist;
		while (n != NULL) //traverse till end of list
		{
			if (n->mbid == mbid)
				break;
			else
				n = n->next; //next data entry
		}
		return n; //if entry not found this will return NULL
	}
};


template <typename i, typename s>
class AMD_List  //(A circular linked list)
{
public:
	AMD<i, s>* head;
	AMD<i, s>* tail;
	AMD_List()
	{
		head = NULL;
		tail = NULL;
	}
	void AMDinsert(i a, s n, s b, s g, s d, s c, s gn)
	{
		if (head == NULL) //When list is empty create head
		{
			head = new AMD<i, s>(a, n, b, g, d, c, gn);
			tail = head;
			head->next = head;
		}
		else
		{
			AMD<i, s>* temp = tail;
			temp->next = new AMD<i, s>(a, n, b, g, d, c, gn);
			temp = temp->next;
			temp->next = head; //New element will be pointing to head
			tail = temp;
		}
	}
	AMD<i, s>* traverse(int aid)
	{
		AMD<i, s>* n = AMDlist;
		while (n->next != n) //traverse till end of list
		{
			if (n->aid == aid)
				break;
			else
				n = n->next; //moving to next element
		}
		return n; //if entry not found this will return NULL
	}
};

template <typename i, typename s, typename f>
class AD_List  //(A circular linked list)
{
public:
	AD<i, s, float>* head;
	AD<i, s, float>* tail;
	AD_List()
	{
		head = NULL;
		tail = NULL;
	}
	void ADinsert(i a, s an, i ai, s p, i n, s d)
	{
		if (head == NULL)
		{
			head = new AD<i, s, float>(a, an, ai, p, n, d);
			tail = head;
			head->next = head;
		}
		else
		{
			AD<i, s, float>* temp = tail;
			temp->next = new AD<i, s, float>(a, an, ai, p, n, d);
			temp = temp->next;
			temp->next = head;
			tail = temp;
		}
	}
	AD<i, s, f>* traverse(int ABID)
	{
		AD<i, s, f>* n = ADlist;
		while (n->next != n) //traverse till end of list
		{
			if (n->abid == ABID)
				break;
			else
				n = n->next; //moving to next element
		}
		return n;
	}
};


template <typename i>
class ADP_List //A circular linked list
{
public:
	ADP<i>* head;
	ADP<i>* tail;
	ADP_List()  //When list is empty create Head
	{
		head = NULL;
		tail = NULL;
	}
	void ADPinsert(i d, i a)
	{
		if (head == NULL)
		{
			head = new ADP<i>(d, a);
			tail = head;
			head->next = head;

		}
		else
		{
			ADP<i>* temp = tail;
			temp->next = new ADP<i>(d, a);
			temp = temp->next;
			temp->next = head;
			tail = temp;
		}
	}
	ADP<i>* traverse(int DID)
	{
		ADP<i>* n = ADPlist;
		while (n->next != n) //traverse till end of list
		{
			if (n->did == DID)
				break;
			else
				n = n->next; //moving to next element
		}
		return n;
	}
};

template <typename i>
class Tracks_List //(A singly linked list)
{
public:
	Tracks<i>* head;
	Tracks<i>* temp;
	Tracks_List()
	{
		head = NULL;
		temp = NULL;
	}
	void Tracksinsert(i t)
	{
		if (head == NULL) //When list is empty create head
		{
			head = new Tracks<i>(t);
			temp = head;
		}
		else
		{
			temp->next = new Tracks<i>(t);
			temp = temp->next;
		}
	}
	Tracks<i>* traverse(int ABID)
	{
		Tracks<i>* n = Tracklist;
		while (n->next != NULL) //traverse till end of list
		{
			if ((n->trackRef)->album->abid == ABID)
				break;
			else
				n = n->next; //moving to next element
		}
		return n;		//if entry not found will return NULL
	}
};

template <typename i>
class Albums_List //(A singly linked list)
{
public:
	Albums<i>* head;
	Albums<i>* temp;
	Albums_List()
	{
		head = NULL;
		temp = NULL;
	}
	void Albumsinsert(i y)
	{
		if (head == NULL) //When list is empty create head
		{
			head = new Albums<i>(y);
			temp = head;
		}
		else
		{
			temp->next = new Albums<i>(y);
			temp = temp->next;
		}
	}
	Albums<i>* traverse(int d)
	{
		Albums<i>* n = Albumslist;
		while (n != NULL) //traverse till end of list
		{
			if ((n->albumRef)->adp->did == d)
			{
				break;
			}
			else
			{
				n = n->next; //next element
			}
		}

		return n; //if entry not found this will return NULL
	}
};


////////////////// FUNCTION IMPLEMENTATION ///////////////
template <typename i, typename s, typename f>
MMD<i, s, f>* Create_MMD(string path)					  //Passed
{

	MMD_List<i, s, f> obj;

	string MBID, songname, writer, length;
	int M;
	ifstream mFile(path);
	if (!mFile.is_open())
	{
		cout << "File not found." << endl;
		exit(1);
	}
	string str;
	getline(mFile, str);	// skip the first line
	while (getline(mFile, str))
	{
		stringstream ss(str);
		getline(ss, MBID, ',');
		getline(ss, songname, ',');
		getline(ss, writer, ',');
		getline(ss, length, ',');
		M = stoi(MBID);
		obj.MMDinsert(M, songname, writer, length);
	}
	mFile.close();
	MMDlist = obj.head;
	return obj.head;
}

template <typename i, typename s>
AMD<i, s>* Create_AMD(string path)	 //Passed
{
	AMD_List<i, s> obj;
	string aid, name, band, gender, dob, cdate, genre;
	int A;
	ifstream mFile(path);
	if (!mFile.is_open())
	{
		cout << "File not found." << endl;
		exit(1);
	}
	string str;
	getline(mFile, str); // skip the first line
	while (getline(mFile, str))
	{
		stringstream ss(str);
		getline(ss, aid, ',');
		getline(ss, name, ',');
		getline(ss, band, ',');
		getline(ss, gender, ',');
		getline(ss, dob, ',');
		getline(ss, cdate, ',');
		getline(ss, genre, ',');
		A = stoi(aid);
		obj.AMDinsert(A, name, band, gender, dob, cdate, genre);

	}
	mFile.close();
	AMDlist = obj.head;
	return obj.head;
}

template <typename i, typename s, typename f>
AD<i, s, f>* Create_AD(string path)  //Passed
{

	AD_List<i, s, f> obj;
	Tracks_List<i> objt;

	string album, publisher, tracksno, totalduration, tnum, tmbid, abid, aid;
	int A, AID, Tnum, tonum;

	ifstream mFile(path);
	if (!mFile.is_open())
	{
		cout << "File not found." << endl;
		exit(1);
	}
	string str;
	getline(mFile, str); // skip the first line
	bool firstvalue = true;
	int temp = 1;		//as starting abid will be ONE in reference to file hence using a control variable with one

	while (getline(mFile, str))			//reading all data from file
	{
		stringstream ss(str);
		getline(ss, abid, ',');
		getline(ss, album, ',');
		getline(ss, aid, ',');
		getline(ss, publisher, ',');
		getline(ss, tracksno, ',');
		getline(ss, totalduration, ',');
		getline(ss, tnum, ',');
		getline(ss, tmbid, ',');
		A = stoi(abid);
		AID = stoi(aid);
		Tnum = stoi(tnum);
		tonum = stoi(tracksno);
		if (firstvalue == true)
		{
			//cout << A << " " << AID << " " << Tnum << endl;
			obj.ADinsert(A, album, AID, publisher, tonum, totalduration);
			objt.Tracksinsert(Tnum);
			firstvalue = false;
		}
		else if (temp < A)
		{
			temp = A;
			//cout << A << " " << AID << " " << Tnum << endl;
			obj.ADinsert(A, album, AID, publisher, tonum, totalduration);
			objt.Tracksinsert(Tnum);
		}
		else
		{
			//cout << "track entry" << endl;
			objt.Tracksinsert(Tnum);
		}
	}
	mFile.close();
	Tracklist = objt.head;		//assigning global variable address of head of Tracks for connection purposes
	ADlist = obj.head;

	Connect_AD();				//calling function responsible for connecting MMD AMD AD Tracks Albums

	return obj.head;			//returning head of AMD
}

template <typename i>
ADP<i>* Create_ADP(string path)
{
	ADP_List<i> obj;
	Albums_List<i> obja;
	//DID, AID, ALBUM ABID, YEAR
	string did, aid, albumabid, year;
	int d, a, y;
	ifstream mFile(path);
	if (!mFile.is_open())
	{
		cout << "File not found." << endl;
		exit(1);
	}
	string str;
	bool firstvalue = true;
	int temp = 1;
	getline(mFile, str); // skip the first line
	while (getline(mFile, str))
	{

		stringstream ss(str);
		getline(ss, did, ',');
		getline(ss, aid, ',');
		getline(ss, albumabid, ',');
		getline(ss, year, ',');
		d = stoi(did);
		a = stoi(aid);
		y = stoi(year);
		if (firstvalue == true)
		{
			//cout << d << " " << a << " " << y << endl;
			obj.ADPinsert(d, a);
			obja.Albumsinsert(y);
			firstvalue = false;
		}
		else if (temp < d)
		{
			temp = d;
			//cout << d << " " << a << " " << y << endl;
			obj.ADPinsert(d, a);
			obja.Albumsinsert(y);
		}
		else
		{
			//cout << "album entry" << endl;
			obja.Albumsinsert(y);
		}
	}
	mFile.close();
	Albumslist = obja.head;
	ADPlist = obj.head;
	Connect_ADP();
	return obj.head;
}


//template <typename i, typename s, typename f>
void Connect_AD()							//PASSED
{
	MMD<int, string, float>* MMDn = MMDlist;
	AMD<int, string>* AMDn = AMDlist;
	AD<int, string, float>* ADn = ADlist;
	Tracks<int>* Trackn = Tracklist;

	AD<int, string, float>* startofnewartist = ADlist;				//currently pointing to first album of first artist
	Tracks<int>* startofnewalbum = Tracklist;		//currently having first track of first album

	//int currentaid = AMDn->aid, currentabid = ADn->abid;
	//these newly declared pointers will work to change/update the lists without losing reference to the HEAD of each list
	int count = 0;
	while (MMDn != NULL)	//end of list
	{


		if (ADn->notracks == Trackn->trackNumber)
		{
			//cout << "changing abid " << endl;
			ADn->author = AMDn;						//AD to AMD
			ADn->tracks = startofnewalbum;			//AD to tracks
			AMDn->albums = ADn;						//AMD to AD
			if (ADn->next != ADlist)
				ADn = ADn->next;			//changing ALBUM
			startofnewalbum = Trackn;

			//cout << ADn << "   ";
			//cout << AMDn << endl;
		}

		if (ADn->aid > AMDn->aid)
		{
			AMDn->albums = startofnewartist;		//AMD to AD
			startofnewartist = ADn;
			if (AMDn->next != AMDlist)
				AMDn = AMDn->next; //updating ARTIST METADATA
			//cout << AMDn << endl;
		}
		//to connect MMD to Track
		Trackn->trackRef = MMDn;  //referral based on current node (works)
		MMDn->album = ADn;		  //connect MMD to AD  (works)


		//changing all respective nodes to the next element in the list
		MMDn = MMDn->next;		//works
		Trackn = Trackn->next;	//works

	}
	//cout << "connect AMD executed" << endl;
}

//template <typename i, typename s, typename f>
void Connect_ADP()				//INCORRECT
{
	AMD<int, string>* AMDn = AMDlist;	// 5 elements seperated on basis of AID
	AD<int, string, float>* ADn = ADlist;		//13 elements
	ADP<int>* ADPn = ADPlist;	// 5 elements on the basis of AID AND DID
	Albums<int>* An = Albumslist;	//13 elements
	ADn->adp = ADPlist;
	int currentaid = ADPn->aid;
	while (ADn->next != ADlist)		//while not at the end of AD list which has 13 elements
	{
		if (ADn->aid > currentaid)
		{
			//cout << "changing AID" << endl;
			//cout << AMDn << endl;
			currentaid = ADn->aid;
			AMDn->adp = ADPlist;		//AMD to ADP
			ADPn->author = AMDn;		//ADP to AMD
			ADPn->albums = An;          //ADP to albums
			//changing aid
			if (AMDn->next != AMDlist)
				AMDn = AMDn->next;
			if (ADPn->next != ADPlist)
				ADPn = ADPn->next;
		}

		ADn->adp = ADPn;			//AD to ADP
		An->albumRef = ADn;			//Albums to AD
		//going to next element in the list
		ADn = ADn->next;
		if (An->next != Albumslist)
			An = An->next;
	}
	//cout << "connect ADP executed" << endl;
}

/*
	Search functions' definitions:
	All search functions implemented generically and depend on connections to work
*/
template <typename i, typename s, typename f>
MMD<i, s, f>* Search_Music(int MBID)
{
	MMD_List<i, s, f> obj;
	MMD<i, s, f>* n = obj.traverse(MBID);
	return n;
}
template <typename i, typename s>
AMD<i, s>* Search_Author(int AID)
{
	AMD_List<i, s> obj;
	AMD<i, s>* n = obj.traverse(AID);
	return n;
}

template <typename i, typename s, typename f>
AD<i, s, f>* Search_Album(int ABID)
{
	AD_List<i, s, f> obj;
	AD<i, s, f>* n = obj.traverse(ABID);
	return n;
}
template <typename i>
ADP<i>* Search_Discography(int DID)
{
	ADP_List<i> obj;
	ADP<i>* n = obj.traverse(DID);
	return n;
}
template <typename i>
Tracks<i>* Search_Music_By_Album(int ABID)
{
	Tracks_List<i> obj;
	Tracks<i>* n = obj.traverse(ABID);
	return n;
}

template <typename i>
Albums<i>* Search_Music_By_Author(int DID)
{
	Albums_List<i> obj;
	Albums<i>* n = obj.traverse(DID);
	return n;
}