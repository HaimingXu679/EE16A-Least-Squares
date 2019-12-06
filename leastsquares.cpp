#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include <vector>
#include <utility>
using namespace std;

pair<vector<pair<int, int> >, double> inverse(int **arr) {
  vector<pair<int, int> > ans;
  ans.push_back(make_pair(arr[1][1], -1 * arr[0][1]));
  ans.push_back(make_pair(-1 * arr[1][0], arr[0][0]));
  if (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0] == 0) 
    return make_pair(ans, 0); 
  return make_pair(ans, (1 / ((double) arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0])));
}

void generate(int seed) {
  srand(time(NULL));
  int y = 2, x = rand() % 2 + seed;
  int **arr = new int*[x];
  for (int i = 0; i < x; i++) 
    arr[i] = new int[y];
  int **ai = new int*[y];
  for (int i = 0; i < y; i++) 
    ai[i] = new int[x];
  int **ata = new int*[y];
  for (int i = 0; i < y; i++)
    ata[i] = new int[y];
  while (true) {
    for (int i = 0; i < x; i++) 
      for (int j = 0; j < y; j++) 
        arr[i][j] = rand() % 5;
    for (int i = 0; i < y; i++)
      for (int j = 0; j < x; j++)
        ai[i][j] = arr[j][i];
    for (int i = 0; i < y; i++) 
      for (int j = 0; j < y; j++) 
        ata[i][j] = 0;
    for (int i = 0; i < y; i++) 
      for (int j = 0; j < y; j++) 
        for (int k = 0; k < x; k++) 
          ata[i][j] += ai[i][k] * arr[k][j];
    if (inverse(ata).second != 0)
      break; 
  }
  cout << "A:" << endl;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) 
      cout << arr[i][j] << " ";
    cout << endl;
  }
  cout << endl << "b: " << endl;
  int *b = new int[x];
  for (int i = 0; i < x; i++) 
    b[i] = rand() % 10;
  for (int i = 0; i < x; i++) 
    cout << b[i] << endl;
  cout << endl; 
  int temp = arr[0][0];
  arr[0][0] = arr[1][1];
  arr[1][1] = temp;
  pair<vector<pair<int, int> >, double> calc = inverse(ata);
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < y; j++) {
      if (j == 1) {
        ata[i][j] = calc.first[i].second;
        continue;
      }
      ata[i][j] = calc.first[i].first;
    }
  }
  int **aat = new int*[y];
  for (int i = 0; i < y; i++) 
    aat[i] = new int[x];
  for (int i = 0; i < y; i++) 
    for (int j = 0; j < x; j++) aat[i][j] = 0;
  for (int i = 0; i < y; i++) 
    for (int j = 0; j < x; j++) 
      for (int k = 0; k < y; k++) 
        aat[i][j] += ata[i][k] * ai[k][j]; 
  int *ans = new int[y];
  for (int i = 0; i < y; i++) 
    ans[i] = 0;
  for (int i = 0; i < y; i++) 
    for (int k = 0; k < x; k++) ans[i] += aat[i][k] * b[k];
  string holder;
  cin >> holder;
  cout << "******SOLUTION******" << endl << "FINAL SOLUTION:" << endl;
  for (int i = 0; i < y; i++) 
    cout << (double) calc.second * ans[i] << endl;
  cout << "DETERMINANT OF ATA= " << calc.second << endl << "DET * b FORM " << endl;
  for (int i = 0; i < y; i++) 
    cout << ans[i] << endl;
  cout << "********************" << endl;
}

int main() {
  int i = -1, counter = 0;
  cout << "==============================================" << endl << "Type any key then press enter to see solution." << endl;
  while (true) {
    if (counter % 4 == 0)
      i++;
    cout << "==============================================" << endl; 
    generate(i + 2);
    counter++;
  }
  return 0;
}
