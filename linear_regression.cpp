#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <math.h>
#include "random.cpp"
using namespace std;

class node { //note that class can become a node with no ill effects
	
	public:
	float x, y;
	float xrank, yrank;
	node *next;
	
	private:
};

void count_nodes( node *root, int *num ) {
	int a=0;
	node *temp = root;
	while (temp->next != 0) {
		a++;
		temp=temp->next;
	}
	*num=a;
	return;
}

void add_node_to_tail ( node *root, float a, float b ) {
	node *temp, *new_node;
	temp = root;
	new_node = new node;
	new_node->next = 0; //the last node contains a NULL pointer

	while ( temp->next != 0 ) 
		temp = temp->next;
	temp->next = new_node;
	new_node->x = a;
	new_node->y = b;
	return;
}

void add_node_to_head ( node *root, node **pp, float a, float b ) {
	node *temp, *new_node;
	temp = root;
	new_node = new node;
	new_node->next = temp;
	new_node->x = a;
	new_node->y = b;
	*pp = new_node;
	return;
}
	
void delete_root_node ( node *root, node **pp ) {
	node *temp;
	temp = root->next;
	*pp = temp;
	free(root);
	return;
}

void add_node ( node *root, int whichnode, float a, float b ) {
	node *new_node, *before, *after;
	new_node = new node;
	new_node->x = a;
	new_node->y = b;
	before = root;
	for (int i=1;i<(whichnode-1);i++)
		before = before->next;
	after = before->next;
	before->next = new_node;
	new_node->next = after;
	return;
}

void delete_node( node *root, node **pp, int whichnode ) {
	if ( whichnode == 0 ) 
		return;
	if ( whichnode == 1 )
	{
		delete_root_node(root, pp);
		return;
	}
	int howmany=0;
	count_nodes(root, &howmany);
	if (howmany < whichnode){
		cout << "Warning: only " << howmany << " nodes, can't delete node #" << whichnode << endl;
		return;
	}
	node *temp, *before, *bad;
	temp = root;
	for (int i=1;i<(whichnode-1);i++)
		temp=temp->next;
	before = temp;
	temp=temp->next;
	bad=temp;
	before->next = bad->next;
	free(bad);
	return;
}

void delete_node_range( node *root, node **pp, int low, int high ) {
	int count = 0;
	count_nodes(root, &count);
	if (high > count)
		high = count;

	for (int i=1;i<=high;i++)
		delete_node(root,pp,i);

	return;
}

void sort_nodes_by_x ( node *root ) { //ascending sort
	node *temp1, *temp2;
	float xx = 0, yy = 0, xxrank=0, yyrank=0;
	temp1 = new node;
	temp2 = new node;

	for (temp1 = root; temp1->next != NULL; temp1 = temp1->next) {
	for (temp2 = temp1->next; temp2->next != NULL; temp2 = temp2->next) {
		if ( temp1->x > temp2->x)
		{
			xx = temp1->x;
			yy = temp1->y;
			xxrank = temp1->xrank;
			yyrank = temp1->yrank;
			temp1->x = temp2->x;
			temp1->y = temp2->y;
			temp1->xrank = temp2->xrank;
			temp1->yrank = temp2->yrank;
			temp2->x = xx;
			temp2->xrank = xxrank;
			temp2->y = yy;
			temp2->yrank = yyrank;
		}
	}}
	return;
}

void sort_nodes_by_y ( node *root ) { //ascending sort
	node *temp1, *temp2;
	float xx = 0, yy = 0, xxrank=0, yyrank=0;
	temp1 = new node;
	temp2 = new node;

	for (temp1 = root; temp1->next != 0; temp1 = temp1->next) {
	for (temp2 = temp1->next; temp2->next != 0; temp2 = temp2->next) {
		if ( temp1->y > temp2->y)
		{
			xx = temp1->x;
			yy = temp1->y;
			xxrank = temp1->xrank;
			yyrank = temp1->yrank;
			temp1->x = temp2->x;
			temp1->y = temp2->y;
			temp1->xrank = temp2->xrank;
			temp1->yrank = temp2->yrank;
			temp2->x = xx;
			temp2->xrank = xxrank;
			temp2->y = yy;
			temp2->yrank = yyrank;
		}
	}}
	return;
}

void print_nodes( node *root ) {
	node *temp;
	temp = root;
	int id = 1;
	while(temp->next != NULL)
	{
	if(0) cout << "Node " << id << " ... " << temp->x << " & " << temp->y << endl;
	temp = temp->next;
	id++;
	}	
}

void print_line() {
	cout << endl;
	return;
}

void sumX ( node *root, float *ssx ) {
	float sum=0, val=0;
	node *temp=root;
	while ( temp->next!= 0 ) {
		val = temp->x;
		sum = sum + val;
		temp = temp->next;
	}
	*ssx = sum;
	return;
}

void sumY ( node *root, float *ssy ) {
	float sum=0, val=0;
	node *temp=root;
	while ( temp->next != 0 ) {
		val = temp->y;
		sum = sum + val;
		temp = temp->next;
	}
	*ssy = sum;
	return;
}

void sumXY ( node *root, float *ssxy ) {
	float sum=0, val=0;
	node *temp=root;
	while ( temp->next != 0 ) {
		val = temp->y * temp->x;
		sum = sum + val;
		temp = temp->next;
	}
	*ssxy = sum;
	return;
}

void sumX2 ( node *root, float *ssx2 ) {
	float sum=0, val=0;
	node *temp=root;
	while ( temp->next != 0 ) {
		val = temp->x;
		sum = sum + val*val;
		temp = temp->next;
	}
	*ssx2 = sum;
	return;
}

void sumY2 ( node *root, float *ssy2 ) {
	float sum=0, val=0;
	node *temp=root;
	while ( temp->next != 0 ) {
		val = temp->y;
		sum = sum + val*val;
		temp = temp->next;
	}
	*ssy2 = sum;
	return;
}

void compute_Lxx (node *root, float *lxx) {
	float ssx = 0;
	float ssx2 = 0;
	int n = 0;
	count_nodes(root, &n);
	sumX(root, &ssx);
	sumX2(root, &ssx2);
	*lxx = ssx2 - ssx*ssx / (float)n;
	return;
}

void compute_Lyy (node *root, float *lyy) {
	float ssy2 = 0;
	float ssy = 0;
	int n = 0;
	count_nodes(root, &n);
	sumY(root, &ssy);
	sumY2(root, &ssy2);
	*lyy = ssy2 - ssy*ssy / (float)n;
	return;
}

void compute_Lxy (node *root, float *lxy) {
	float ssxy = 0;
	float ssx = 0;
	float ssy = 0;
	int n = 0;
	count_nodes(root, &n);
	sumXY(root, &ssxy);
	sumX(root, &ssx);
	sumY(root, &ssy);
	*lxy = ssxy - ssy*ssx / (float)n;
	return;
}

void compute_xbar (node *root, float *xbar) {
	node *temp = root;
	float mean = 0;
	float var=0;
	int n = 0;
	count_nodes(root, &n);
	while (temp->next != 0)
	{
		mean = mean + temp->x;
		temp = temp->next;
	}
	cout << "Xbar " << mean/(float)n << endl;
	*xbar = mean / (float)n;
	return;
}

void compute_ybar (node *root, float *ybar) {
	node *temp = root;
	float mean = 0.0;
	float var=0.0;
	int n = 0;
	float pn;
	count_nodes(root, &n);
	while (temp->next != 0)
	{
		mean = mean + temp->y;
		temp = temp->next;
	}
	cout << "Ybar " << mean/n << endl;
	*ybar = mean / n;
	return;
}

void compute_regression_line (node *root, float *m, float *b) {
	// compute the Y-int (b) & slope (m) of a line
	// y = m*x + b
	int n = 0;
	count_nodes(root, &n);
	float ybar = 0.0;
	compute_ybar(root, &ybar);
	float xbar = 0.0;
	compute_xbar(root, &xbar);
	
	float Lxx = 0; //corrected sum of squares for X
	compute_Lxx(root, &Lxx);
	float Lyy = 0; //corrected sum of squares for Y
	compute_Lyy(root, &Lyy);
	float Lxy = 0; //corrected sum of cross products
	compute_Lxy(root, &Lxy);

	*m = Lxy / Lxx;
	*b = ybar - ( *m * xbar );
	return;
}

void compute_pearson_coefficient (node *root, float *pc) { //Pearson cause we calculate L values from the true values
	float Lxx = 0;
	compute_Lxx(root, &Lxx);
	float Lyy = 0;
	compute_Lyy(root, &Lyy);
	float Lxy = 0;
	compute_Lxy(root, &Lxy);

	*pc = Lxy / sqrt(Lxx*Lyy);
	return;
}

void initialize_ranks(node *root)
{
	node *temp = root;
	int rank = 1;
	while(temp->next != 0)
	{
		temp->xrank = rank;
		temp->yrank = rank;
		temp=temp->next;
	}
}

void compute_spearman_coefficient (node *root, float *sc) { //Spearman uses ranks not the actual values
	float coeff = 0;
	int n = 0;
	count_nodes(root,&n);
	node *temp = root;
	vector<float> xrank, yrank;
	vector<float> x, y;
	float sum_rank = 0;
	vector<float> x_sum_rank, y_sum_rank;
	initialize_ranks(root); //dont loose data here

	//get x ranks in a vector
	sort_nodes_by_x(root); 
	temp=root;
	while (temp->next != NULL) {
		if(0)cout << "test look at hours " << temp->x  << " " << temp->y << endl;
		x.push_back(temp->x);
		temp=temp->next;
	}
	vector<int> duplicates;
	for (int i=0;i<x.size();i++)
	{
		duplicates.clear();
		duplicates.push_back(i);
		sum_rank=0;
		for (int j=0;j<x.size();j++)
		{
			if ( x[j] == x[i] & i != j)
				duplicates.push_back(j);
		}
		for (int k=0;k<duplicates.size();k++)
		{
			sum_rank = sum_rank + duplicates[k] + 1;
			//cout << "Adding ranks of " << duplicates[k] << " at value i " << i << endl;
		}
		sum_rank = sum_rank / duplicates.size();
		for (int k=0;k<duplicates.size();k++)
			xrank.push_back(sum_rank);
		if(0) cout << "XIndex " << i << " Value " << x[i] << " & #occurances " << duplicates.size() << " & new rank " << sum_rank << endl;
		x_sum_rank.push_back(sum_rank);
	}//end outer loop

	temp=root;
	int index = 0;
	while(temp->next != 0)
	{
		temp->xrank = x_sum_rank[index];
		//cout << "Index " << index+1 << " " << temp->xrank << endl;
		index++;
		temp = temp->next;
	}
	//get y ranks in a vector
	sort_nodes_by_y(root);
	temp=root;
	while (temp->next != 0) {
		y.push_back(temp->y);
		temp=temp->next;
	}

	duplicates.clear();
	for (int i=0;i<y.size();i++)
	{
		duplicates.clear();
		duplicates.push_back(i);
		sum_rank=0;
		for (int j=0;j<y.size();j++)
		{
			if ( y[j] == y[i] & i != j)
				duplicates.push_back(j);
		}
		for (int k=0;k<duplicates.size();k++)
		{
			sum_rank = sum_rank + duplicates[k] + 1;
			//cout << "Adding ranks of " << duplicates[k] << " at value i " << i << endl;
		}
		sum_rank = sum_rank / duplicates.size();
		for (int k=0;k<duplicates.size();k++)
			yrank.push_back(sum_rank);
		temp=root;
		int index = 0;
		while(temp->next != 0)
		{
			temp->yrank = yrank[index];
			index++;
			temp = temp->next;
		}
		if(0) cout << "YIndex " << i << " Value " << y[i] << " & #occurances " << duplicates.size() << " & new rank " << sum_rank << endl;
		y_sum_rank.push_back(sum_rank);
	}//end outer loop
	temp=root;
	index = 0;
	while(temp->next != 0)
	{
		temp->yrank = y_sum_rank[index];
		//cout << "Index " << index+1 << " " << temp->xrank << endl;
		index++;
		temp = temp->next;
	}
	//compute d values based on the X & Y rank vectors
	float td=0, td2=0;
	float td2sum=0;
	temp=root;
	int t=1;
	while (temp->next != 0)
	{
		if(0) cout << "NodeIndex " << t << " Xvalue@ " << temp->x << " Xrank " << temp->xrank << " Yvalue@ " << temp->y << " Yrank " << temp->yrank << endl;t++;
		td = temp->yrank - temp->xrank;
		td2 = td*td;
		td2sum = td2sum + td2;
		temp=temp->next;
	}

	//Spearman formula --> 1 - ( 6*sum(d^2) / ( n(n^2-1)) ) 
	coeff = 1 - ( (6*td2sum) / (n*n*n - n) );
	*sc = coeff;
	return;
}

int main (int argc, char *argv[]) {
bool display = 0;

if (argc <2)
{
	cout << "Pass the function a file containing linear regression data" << endl;
	exit(0);
}
srand ( time(NULL) );

FILE *fp; 
//char filename [ sizeof(argv[1]) ];
//By default malloc returns void* so we cast the output of malloc as what we want ie (int *) for integers, (char *) for chars, (float *) for floats and so on
char *filename = new char( sizeof(char)*strlen(argv[1]) );
strcpy(filename, argv[1]);
fp = fopen(filename, "r");

if ( fp == NULL ) {
	cout << "File " << filename << " not found" << endl;
	cout << "Exiting" << endl;
	fclose(fp);
	exit(0);
}

ifstream myfile(filename);
string line;
//initialize the linked list
node *root, *conductor;
root = new node;
float tx=0, ty=0;
if (myfile) {
while ( ! myfile.eof() ) {
	getline(myfile, line);
	cout << line << endl;
	sscanf(line.c_str(), "%f %f", &tx, &ty);
	add_node_to_tail(root, tx, ty);
}
getline(myfile, line);
sscanf(line.c_str(), "%f %f", &tx, &ty);
add_node_to_tail(root, tx, ty);
}
myfile.close();
//delete the initilization node
node **pp;
pp = &root;
delete_root_node(root,pp);
print_nodes(root);

//line properties y = m*x + b
float m=0, b=0;
compute_regression_line(root, &m, &b);
cout << "The slope of the line is " << m << " and the Y-intercept is " << b << endl;

float pearson_coefficient=0;
compute_pearson_coefficient(root, &pearson_coefficient);
cout << "The Pearson coefficient is " << pearson_coefficient << endl;

float spearman_coefficient=0;
compute_spearman_coefficient(root, &spearman_coefficient);
cout << "The Spearman coefficient is " << spearman_coefficient << endl;

return 0;
}




