#include "KyloRen.h"
#include <cmath>

using namespace std;

KyloRen::KyloRen() {
	setCharacterType("kotu");
}

KyloRen::~KyloRen()
{
	//dtor
}

int KyloRen::shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index) { //en kisa yol algoritmasi

    int **matris;
    vector<int>roots;
    int V;
	int root[156] = {4,0, 12,0, 1,1, 2,1, 3,1, 4,1, 6,1, 7,1, 8,1, 9,1, 10,1, 11,1, 12,1, 1,2, 3,2, 4,2, 5,2, 6,2, 8,2, 12,2, 1,3, 3,3, 4,3, 6,3, 8,3, 9,3, 11,3, 12,3, 1,4, 3,4, 6,4, 8,4, 9,4, 11,4, 12,4, 0,5, 1,5, 3,5, 4,5, 5,5, 6,5, 8,5, 12,5, 13,5, 1,6, 4,6, 6,6, 8,6, 10,6, 11,6, 12,6, 1,7, 3,7, 4,7, 5,7, 6,7, 7,7, 8,7, 12,7, 1,8, 3,8, 8,8, 11,8, 12,8, 1,9, 2,9, 3,9, 4,9, 5,9, 6,9, 7,9, 8,9, 9,9, 10,9, 11,9, 12,9, 13,9, 4,10};

	for(int p=0;p<156;p++){
		 roots.push_back(root[p]);
	}

	int start;
	vector<int>finish;

    int fini[(*badCharacters).size()];
    int sayici[(*badCharacters).size()];

    for(int i=0; i<(*badCharacters).size(); i++) {
        sayici[i] = -1;
        fini[i] = -1;
    }

	for(int i=0;i<(*badCharacters).size();i++){
        for(int p=0;p<156;p+=2){
    		if(((*badCharacters)[i]->getXCoordinate()-130)/35 == root[p] &&  ((*badCharacters)[i]->getYCoordinate()-130)/35 == root[p+1]){
    			finish.push_back(p/2);
    			sayici[i]++;
			}
		}
	}

    int cikar = 0;
    for(int i=0; i<(*badCharacters).size(); i++) {
        if(sayici[i] != -1) {
            fini[i] = finish.at(i-cikar);
        }
        if(sayici[i] == -1) {
            cikar ++;
        }
	}

    for(int p=0;p<156;p+=2){
        if((character->getXCoordinate()-130)/35 == root[p] && (character->getYCoordinate()-130)/35 == root[p+1]){
            start = p/2;
        }
    }

    V = roots.size()/2;

	int f=152;
	int f3 = 15;

	int walls[152] = {0,0, 1,0, 2,0, 3,0, 5,0, 6,0, 7,0, 8,0, 9,0, 10,0, 11,0, 13,0, 0,1,
		5,1, 13,1, 0,2, 2,2, 7,2, 9,2, 10,2, 11,2, 13,2, 0,3, 2,3, 5,3, 7,3,
		10,3, 13,3, 0,4, 2,4, 4,4, 5,4, 7,4, 10,4, 13,4, 2,5, 7,5, 9,5, 10,5,
		11,5, 0,6, 2,6, 3,6, 5,6, 7,6, 9,6, 13,6, 0,7, 2,7, 9,7, 10,7, 11,7,
		13,7, 0,8, 2,8, 4,8, 5,8, 6,8, 7,8, 9,8, 10,8, 13,8, 0,9, 0,10, 1,10,
		2,10, 3,10, 5,10, 6,10, 7,10, 8,10, 9,10, 10,10, 11,10, 12,10, 13,10};

	int a[f3] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
	int a1[f3] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
	int a2[f3] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
	int t=0,t1=0,mesafe,i2,sayac=0,sayac2=0,kt;

	matris = new int*[V];
	for(int i=0; i<V; i++) {
		matris[i] = new int [V];
	}

	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			matris[i][j] = 0;
		}
	}

	for(int i=0;i<14;i++){
		for(int j=0;j<roots.size();j+=2){
			if(i == roots.at(j)){
				for(int k=0;k<roots.size();k+=2){
					if(i == roots.at(k) && k != j){
						a[t] = roots.at(k+1);
						t++;
						t1=t;
					}
				}
				t=0;
				if(t1 > 1){
                    int min = fabs(roots.at(j+1) - a[0]);
                    int value = a[0];
                    kt=0;

                    for(int k1=1;k1<f3;k1++){
                        if(fabs(roots.at(j+1) - a[k1]) < min){
                            min = fabs(roots.at(j+1) - a[k1]);
                            value = a[k1];
                            kt = k1;
                        }
                    }

                    int value2;
                    if(roots.at(j+1) > a[kt]){
                        a[kt] =50;
                        for(int k1=0;k1<f3;k1++){
                            if(roots.at(j+1) < a[k1] && a[k1] != 50){
                                a1[k1] = a[k1];
                                sayac2++;
                            }
                        }

                        min = fabs(roots.at(j+1) - a1[0]);
                        value2 = a1[0];

                        for(int k1=1;k1<f3;k1++){
                            if(fabs(roots.at(j+1) - a1[k1]) < min){
                                min = fabs(roots.at(j+1) - a1[k1]);
                                value2 = a1[k1];
                            }
                        }
                    }
                    else{
                        a[kt] =50;
                        for(int k1=0;k1<f3;k1++){
                            if(roots.at(j+1) > a[k1] && a[k1] != 50){
                                a2[k1] = a[k1];
                                sayac2++;
                            }
                        }
                        min = fabs(roots.at(j+1) - a2[0]);
                        value2 = a2[0];
                        for(int k1=1;k1<f3;k1++){
                            if(fabs(roots.at(j+1) - a2[k1]) < min){
                                min = fabs(roots.at(j+1) - a2[k1]);
                                value2 = a2[k1];
                            }
                        }
                    }

                    for(int k1=0;k1<f3;k1++){
                        a[k1] = 50;
                    }
                    for(int k1=0;k1<f3;k1++){
                        a1[k1] = 50;
                    }
                    for(int k1=0;k1<f3;k1++){
                        a2[k1] = 50;
                    }

                    mesafe = fabs(roots.at(j+1)- value);

                    if(roots.at(j+1)<value){
                        for(int k2=roots.at(j+1)+1;k2<value;k2++){
                            for(int k3=0;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3+1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    if(roots.at(j+1)>value){
                        for(int k2=value+1;k2<roots.at(j+1);k2++){
                            for(int k3=0;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3+1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    for(int i1=0;i1<roots.size();i1+=2){
                        if(roots.at(i1) == i && roots.at(i1+1) == value && sayac == 0){
                            matris[j/2][i1/2] = mesafe;
                            matris[i1/2][j/2] = mesafe;
                        }
                    }
                    sayac = 0;

                    if(sayac2 != 0){
                        mesafe = fabs(roots.at(j+1)- value2);

                        if(roots.at(j+1)<value2){
                            for(int k2=roots.at(j+1)+1;k2<value2;k2++){
                                for(int k3=0;k3<f;k3+=2){
                                    if(walls[k3] == i && walls[k3+1] == k2){
                                        sayac++;
                                    }
                                }
                            }
                        }

                        if(roots.at(j+1)>value2){
                            for(int k2=value2+1;k2<roots.at(j+1);k2++){
                                for(int k3=0;k3<f;k3+=2){
                                    if(walls[k3] == i && walls[k3+1] == k2){
                                        sayac++;
                                    }
                                }
                            }
                        }

                        for(int i1=0;i1<roots.size();i1+=2){
                            if(roots.at(i1) == i && roots.at(i1+1) == value2 && sayac == 0){
                                matris[j/2][i1/2] = mesafe;
                                matris[i1/2][j/2] = mesafe;
                            }
                        }
                        sayac = 0;

                    }
                    sayac2 = 0;
				}

				if(t1 == 1){
                    int min = fabs(roots.at(j+1) - a[0]);
                    int value = a[0];
                    for(int k1=1;k1<f3;k1++){
                        if(fabs(roots.at(j+1) - a[k1]) < min){
                            min = fabs(roots.at(j+1) - a[k1]);
                            value = a[k1];
                        }
                    }

                    for(int k1=0;k1<f3;k1++){
                        a[k1] = 50;
                    }

                    mesafe = fabs(roots.at(j+1)- value);

                    if(roots.at(j+1)<value){
                        for(int k2=roots.at(j+1)+1;k2<value;k2++){
                            for(int k3=0;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3+1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    if(roots.at(j+1)>value){
                        for(int k2=value+1;k2<roots.at(j+1);k2++){
                            for(int k3=0;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3+1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    for(int i1=0;i1<roots.size();i1+=2){
                        if(roots.at(i1) == i && roots.at(i1+1) == value && sayac == 0){
                            matris[j/2][i1/2] = mesafe;
                            matris[i1/2][j/2] = mesafe;
                        }
                    }
                    sayac = 0;
				}
				t1=0;
			}
		}
	}

	t=0;
	t1=0;

	for(int i=0;i<11;i++){
		for(int j=1;j<roots.size();j+=2){
			if(i == roots.at(j)){
				for(int k=1;k<roots.size();k+=2){
					if(i == roots.at(k) && k != j){
						a[t] = roots.at(k-1);
						t++;
						t1=t;
					}
				}

				t=0;
				if(t1 > 1){
                    int min = fabs(roots.at(j-1) - a[0]);
                    int value1 = a[0];
                    kt = 0;

                    for(int k1=1;k1<f3;k1++){
                        if(fabs(roots.at(j-1) - a[k1]) < min){
                            min = fabs(roots.at(j-1) - a[k1]);
                            value1 = a[k1];
                            kt =k1;
                        }
                    }

                    int value3;
                    if(roots.at(j-1) > a[kt]){
                        a[kt] =50;
                        for(int k1=0;k1<f3;k1++){
                            if(roots.at(j-1) < a[k1] && a[k1] != 50){
                                a1[k1] = a[k1];
                                sayac2++;
                            }
                        }

                        min = fabs(roots.at(j-1) - a1[0]);
                        value3 = a1[0];

                        for(int k1=1;k1<f3;k1++){
                            if(fabs(roots.at(j-1) - a1[k1]) < min){
                                min = fabs(roots.at(j-1) - a1[k1]);
                                value3 = a1[k1];
                            }
                        }
                    }
                    else{
                        a[kt] =50;
                        for(int k1=0;k1<f3;k1++){
                            if(roots.at(j-1) > a[k1] && a[k1] != 50){
                                a2[k1] = a[k1];
                                sayac2++;
                            }
                        }

                        min = fabs(roots.at(j-1) - a2[0]);
                        value3 = a2[0];

                        for(int k1=1;k1<f3;k1++){
                            if(fabs(roots.at(j-1) - a2[k1]) < min){
                                min = fabs(roots.at(j-1) - a2[k1]);
                                value3 = a2[k1];
                            }
                        }
                    }
                    for(int k1=0;k1<f3;k1++){
                        a[k1] = 50;
                    }
                    for(int k1=0;k1<f3;k1++){
                        a1[k1] = 50;
                    }
                    for(int k1=0;k1<f3;k1++){
                        a2[k1] = 50;
                    }

                    mesafe = fabs(roots.at(j-1)- value1);

                    if(roots.at(j-1)<value1){
                        for(int k2=roots.at(j-1)+1;k2<value1;k2++){
                            for(int k3=1;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3-1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    if(roots.at(j-1)>value1){
                        for(int k2=value1+1;k2<roots.at(j-1);k2++){
                            for(int k3=1;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3-1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }
                    for(int i1=1;i1<roots.size();i1+=2){
                        if(roots.at(i1) == i && roots.at(i1-1) == value1 && sayac == 0){
                            matris[j/2][i1/2] = mesafe;
                            matris[i1/2][j/2] = mesafe;
                        }
                    }
                    sayac = 0;

                    if(sayac2 != 0){
                        mesafe = fabs(roots.at(j-1)- value3);
                        if(roots.at(j-1)<value3){
                            for(int k2=roots.at(j-1)+1;k2<value3;k2++){
                                for(int k3=1;k3<f;k3+=2){
                                    if(walls[k3] == i && walls[k3-1] == k2){
                                        sayac++;
                                    }
                                }
                            }
                        }

                        if(roots.at(j-1)>value3){
                            for(int k2=value3+1;k2<roots.at(j-1);k2++){
                                for(int k3=1;k3<f;k3+=2){
                                    if(walls[k3] == i && walls[k3-1] == k2){
                                        sayac++;
                                    }
                                }
                            }
                        }
                        for(int i1=1;i1<roots.size();i1+=2){
                            if(roots.at(i1) == i && roots.at(i1-1) == value3 && sayac == 0){
                                matris[j/2][i1/2] = mesafe;
                                matris[i1/2][j/2] = mesafe;
                            }
                        }
                        sayac = 0;
                    }
                    sayac2 = 0;
				}
				if( t1 == 1){
                    int min = fabs(roots.at(j-1) - a[0]);
                    int value1 = a[0];

                    for(int k1=1;k1<f3;k1++){
                        if(fabs(roots.at(j-1) - a[k1]) < min){
                            min = fabs(roots.at(j-1) - a[k1]);
                            value1 = a[k1];
                        }
                    }

                    for(int k1=0;k1<f3;k1++){
                        a[k1] = 50;
                    }

                    mesafe = fabs(roots.at(j-1)- value1);

                    if(roots.at(j-1)<value1){
                        for(int k2=roots.at(j-1)+1;k2<value1;k2++){
                            for(int k3=1;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3-1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }

                    if(roots.at(j-1)>value1){
                        for(int k2=value1+1;k2<roots.at(j-1);k2++){
                            for(int k3=1;k3<f;k3+=2){
                                if(walls[k3] == i && walls[k3-1] == k2){
                                    sayac++;
                                }
                            }
                        }
                    }
                    for(int i1=1;i1<roots.size();i1+=2){
                        if(roots.at(i1) == i && roots.at(i1-1) == value1 && sayac == 0){
                            matris[j/2][i1/2] = mesafe;
                            matris[i1/2][j/2] = mesafe;
                        }
                    }
                    sayac = 0;
				}
				t1=0;
			}
		}

	}

    int distance[V];
    bool Set[V];

    for (int i = 0; i < V; i++)
       distance[i] = INT_MAX, Set[i] = false;

    distance[start] = 0;

     int way[V][V];
     for(int i=0;i<V;i++){
     	for(int j=0;j<V;j++){
     		way[i][j] = -1;
		 }
	 }

     int v1[V];

     for(int i=0;i<V;i++)
     	v1[i]= -1;

     int i1,j=0;

     for (int count = 0; count < V-1; count++){
       int min = INT_MAX, min_index;

   		for (int v = 0; v < V; v++){
			if (Set[v] == false && distance[v] <= min){
				min = distance[v];
				min_index = v;
			}
   		}

       int u = min_index;

       Set[u] = true;

       for (int v = 0; v < V; v++)
         if (Set[v] == false && matris[u][v] != 0 && distance[u]+matris[u][v] < distance[v]) {
		 	distance[v] = distance[u] + matris[u][v];
		 	way[v][0] = u;
		 	way[v][1] = v;
		 	for(int k=0;k<V;k++){
		 		if(v1[k] == u){
		 			for(int i=0;i<V;i++){
		 				way[v][i] = way[u][i];
                        if(way[u][i] != -1)
                            i1 = i;
				 	}
		 			way[v][i1+1] = v;
				}
			}
		 	v1[j] =v;
		 	j++;
		 }
     }


    vector <vector <int> >ways;
    for(int i=0;i<V;i++){
        vector <int> row2;
        for(int j=0;j<V;j++){
            if(way[i][j] != -1)
                row2.push_back(way[i][j]);
        }
        ways.push_back(row2);
    }

    if(olcum == 0) {
        (*badCharacters)[index]->setXCoordinate(roots[ways[fini[index]][ways[fini[index]].size()-1]*2]*35+130);
        (*badCharacters)[index]->setYCoordinate(roots[ways[fini[index]][ways[fini[index]].size()-1]*2+1]*35+130);
    }
    else {
        (*badCharacters)[index]->setXCoordinate(roots[ways[fini[index]][ways[fini[index]].size()-3]*2]*35+130);
        (*badCharacters)[index]->setYCoordinate(roots[ways[fini[index]][ways[fini[index]].size()-3]*2+1]*35+130);
    }

    (*fin).clear();

    for(int i=0; i<(*badCharacters).size(); i++) {
        fin->push_back(fini[i]);
    }

    (*coord).clear();
    for(int i=0; i<ways.size(); i++) {
        vector <int> row1;

        for(int j=0; j<ways[i].size(); j++) {
            row1.push_back(ways[i][j]);
        }
        coord->push_back(row1);
    }

    (*ro).clear();
     for(int i=0; i<roots.size(); i++) {
        ro->push_back(roots[i]);
    }
}
