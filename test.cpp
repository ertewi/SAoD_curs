//variant 51 1 2 3 1 3
// 1B base
// 2C year and author | K (key) - year 
// 3S direct merge sort
// 1D AVL-tree
// 3E Fano code

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

typedef struct st
{
    struct st *next;
    int element;
} list;

typedef struct queue
{
    list *head = NULL;
    list *tail = NULL;
} line;

struct record
{
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;	
};

void list_add(list **head, int x)
{
	list *p;
	p = new list[1];
	
	p->element = x;
	
	p->next = *head;
	*head = p;
}

int Split(list *&S, list *&A, list *&B)
{
    list *k, *p;
    int n = 1;
    A = S, B = S->next;
    k = A, p = B;
    while (p != NULL)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    return n;
}

void FromListToLine(list *&list, line &queue)
{
    queue.tail->next = list;
    queue.tail = list;
    list = list->next;
}

void Merge(list *&A, int &q, list *&B, int &r, line &C, record *&tt)
{
	int i;
    while ((q != 0) && (r != 0))
    {
        if (tt[A->element].year < tt[B->element].year)
        {
            FromListToLine(A, C);
            q = q - 1;
        } else if(tt[A->element].year > tt[B->element].year) {
        	FromListToLine(B, C);
            r = r - 1;
		} else {
			for(i = 0; i < 12; i++) {
				if(tt[A->element].author[i] == tt[B->element].author[i]) continue;
			
	            if(tt[A->element].author[i] < tt[B->element].author[i]) {
	            	FromListToLine(A, C);
	            	q = q - 1;
	            	break;
				} else {
					FromListToLine(B, C);
	            	r = r - 1;
	            	break;
				}
			}
			if(i == 12) {
				FromListToLine(A, C);
	            q = q - 1;
			}
        }
    }
    while (q > 0)
    {
        FromListToLine(A, C);
        q = q - 1;
    }
    while (r > 0)
    {
        FromListToLine(B, C);
        r = r - 1;
    }
}

void MergeSort(list *&S, record *&tt)
{
    int q, r;
    list *A, *B;
    A = B = NULL;
    line C[2];
    int length = Split(S, A, B);
    int p = 1;
    while (p < length)
    {
        for (int i = 0; i < 2; i++)
        {
            C[i].tail = (list *)&C[i].head;
        }
        int i = 0, m = length;
        while (m > 0)
        {
            if (m >= p)
            {
                q = p;
            }
            else
            {
                q = m;
            }
            m = m - q;
            if (m >= p)
            {
                r = p;
            }
            else
            {
                r = m;
            }
            m = m - r;
            Merge(A, q, B, r, C[i], tt);
            i = 1 - i;
        }
        A = C[0].head;
        B = C[1].head;
        p = 2 * p;
    }
    C[0].tail->next = NULL;
    S = C[0].head;
}

int main()
{
	int j;
	int page = 1;
	int tt_index[4000];
	list* S;
	S = NULL;
	for(j = 0; j < 4000; j++) tt_index[j] = j;
	char ch;
	FILE *fp;
	fp=fopen("testBase1.dat", "rb");
	record* tt = new record[4000];
	int i=0,sum=0;
	i=fread((record *)tt, sizeof(record), 4000, fp);
	i = 0;
	while(i < 4000) {
		cout<<"page: "<<page<<endl;
		for(i = page * 20 - 20; i < 20 * page; i++)
			cout<<i+1<<".\t"<<tt[tt_index[i]].author<<"\t"<<tt[tt_index[i]].title<<"\t"<<tt[tt_index[i]].publisher<<"\t\t"<<tt[tt_index[i]].year<<"\t"<<tt[tt_index[i]].num_of_page<<endl;
		cout<<"\n\r"<<"<"<<" prev"<<"\t"<<">"<<" next"<<"\t"<<"?"<<" own page"<<"\t"<<"@"<<" exit"<<"\t"<<"S"<<" sort"<<"\t"<<endl;
		cin>>ch;
		
		switch(ch){
			case '<':
				if(page > 1) page--;
				break;
				
			case '>':
				if(page < 4000 / 20) page++;
				break;
				
			case '?':
				cin>>page;
				if(page < 1) page = 1;
				if(page > 4000 / 20) page = 4000 / 20;
				break;
			
			case 'S':
			case 's':
				for(j = 0; j < 4000; j++)
				{
					list_add(&S, j);
				}
				MergeSort(S, tt);
				for(j = 0; j < 4000; j++)
				{
					tt_index[j] = S->element;
					S = S->next;
				}
				break;
		}
		
		system("cls");
		
		if(ch == '@') break;
	}
	
	return 0;
}

//void my_merge_sort(int** arr, int** buff, record* tt, int a, int b)
//{
//	if(b - a < 2)
//	{
//		return; 
//	} else {
//		my_merge_sort(arr, buff, tt, a, floor(b / 2));
//		my_merge_sort(arr, buff, tt, ceil(b / 2), a);
//		
//		int j = ceil(b / 2);
//		for(int i = a; i < b; i++)
//		{
//			if(tt[*arr[a]].year < tt[*arr[j]].year)
//			{
//				*arr[i] = *arr[a];
//				a++;
//			} else {
//				*arr[i] = *arr[j];
//				j++;
//			}
//		}
//	}
//}
