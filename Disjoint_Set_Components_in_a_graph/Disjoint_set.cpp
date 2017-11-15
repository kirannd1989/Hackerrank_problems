#define _CRT_SECURE_NO_WARNINGS


//solution to the problem https://www.hackerrank.com/challenges/components-in-graph/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define INT_MIN     (-2147483647 - 1) // minimum (signed) int value
#define INT_MAX       2147483647    // maximum (signed) int value
int maximum_tree = INT_MIN;
int minimum_tree = INT_MAX;
struct Disjoint_list {
	int rank;
	int data;
	Disjoint_list *node;
};

void create_node(Disjoint_list &input, int value) {
	input.data = value;
	input.rank = 0;
	input.node = NULL;
}

Disjoint_list*  get_parent(Disjoint_list &input) {

	if (input.node == NULL)
		return &input;
	return get_parent(*input.node);
}

void make_set(int a, int b, vector<Disjoint_list> &input) {

	Disjoint_list *inputA = get_parent(input[a]);
	Disjoint_list *inputB = get_parent(input[b]);

	if (inputA == inputB)
		return;

	if (inputA->rank > inputB->rank) {
		inputA->rank += inputB->rank + 1;
		inputB->node = inputA;

	}
	else if (inputA->rank < inputB->rank) {
		inputB->rank += inputA->rank + 1;
		inputA->node = inputB;

	}
	else {
		if (inputA->data < inputB->data) {
			inputA->rank += inputB->rank + 1;
			inputB->node = inputA;

		}
		else {
			inputB->rank += inputA->rank + 1;
			inputA->node = inputB;

		}
	}

}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#ifdef DEBUG
	freopen("input.txt", "rb", stdin);
#endif
	int N;
	cin >> N;

	vector<Disjoint_list> input(2 * N + 1);
	for (int i = 1; i <= 2 * N; i++) {
		create_node(input[i], i);
	}
	int a, b;

	for (int j = 0; j < N; j++) {
		cin >> a >> b;
		make_set(a, b, input);
	}
	for (int i = 1; i <= N; i++) {
		if (input[i].node == NULL) {
			if (input[i].rank > maximum_tree)
				maximum_tree = input[i].rank;
			if (input[i].rank && input[i].rank < minimum_tree)
				minimum_tree = input[i].rank;
		}
	}

	cout << minimum_tree + 1 << " " << maximum_tree + 1 << endl;
	return 0;
}