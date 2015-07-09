#include <stdlib.h>
#include <time.h>
#include <set>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

struct node {
	int x, y;
	int id, r;
	int next[1600];
};

int centralized(set<int>* ds, struct node q[], int m, char mapp[], unsigned int d[]) {
	set<int>::iterator si, sj, sk, end;
	int i, j, k;
	char flag[m];

	i = 0;
	memset(flag, 0 ,sizeof(bool)*m);
	while (i < m) {
		ds->insert(i);
		flag[i] = 1;
		for (j=(i+1); j<m; j++) {
			if (mapp[i*m+j] && mapp[j*m+i]) flag[j] =1;
		}
		while ((i<m) && (flag[i])) i+=1;
	}
        printf("size:%d\n", ds->size());

        for (k=0; k<m; k++) {
                for (i=0; i<m; i++) {
                        for (j=0; j<m; j++) {
                                if (i == j) continue;
                                if (!d[i*m+k] || !d[k*m+j]) continue;
                                if (!d[i*m+j] || (d[i*m+j] > (d[i*m+k]+d[k*m+j]))) {
                                        d[i*m+j] = d[i*m+k]+d[k*m+j];
                                        q[i].next[j] = q[i].next[k];
				}
			}
		}
	}

        end = ds->end();
        for (si=ds->begin(); si!=end; si++) {
                for (sj=ds->begin(); sj!=end; sj++) {
                        if (si == sj) continue;
                        if (d[*si*m+*sj] <= 4) {
                                for (k=q[*si].next[*sj]; k!=(-1); k=q[k].next[*sj]) {
                                        //printf("%d->%d  %d\n", *si, *sj, k);
                                        ds->insert(k);
                                }
                        }
                }
        }
        printf("size:%d\n", ds->size());

}

void GenerateDiskGraph(struct node* q, int m, int width, int height) {
	int i, n, u;
        int x, y;
        int minr;

	n = rand()%m;
	//const int maxr = width*width + height*height;
        const int maxr = 25;
	q[0].x = rand()%width;
	q[0].y = rand()%height;
	q[0].id = 0;
	for (i=1; i<=n; i++) {
		x = rand()%width; y = rand()%height;
		minr = (x - q[i-1].x)*(x - q[i-1].x) + (y - q[i-1].y)*(y - q[i-1].y);
		q[i].x = x;
		q[i].y = y;
		q[i].id = i;
		q[i].r = rand()%(maxr-minr) + minr;
	}
	minr = (q[0].x - q[n].x)*(q[0].x - q[n].x) + (q[0].y - q[n].y)*(q[0].y - q[n].y);
	q[0].r = rand()%(maxr-minr) + minr;
	for (; i<m; i++) {
                u = rand()%n;
		q[i].x = rand()%width;
		q[i].y = rand()%height;
		q[i].id = i;
	        minr = (q[i].x - q[u].x)*(q[i].x - q[u].x) + (q[i].y - q[u].y)*(q[i].y - q[u].y);
		q[i].r = rand()%(maxr-minr) + minr;
	}
        printf("%d\n", n);
}

void GenerateGraph(struct node q[], int m, char map[], unsigned int d[]) {
	int i, j;

	for (i=0; i<m; i++) {
		for (j=0; j<m; j++) {
                        if (i == j) {
                                map[i*m+i] = 0;
                                q[i].next[i] = -1;
                                continue;
                        }
			if ((q[i].x-q[j].x)*(q[i].x-q[j].x)+(q[i].y-q[j].y)*(q[i].y-q[j].y) <= q[i].r) {
				map[i*m+j] = 1;
                                d[i*m+j] = 1;
				q[i].next[j] = j;
			} else {
				map[i*m+j] = 0;
                                d[i*m+j] = 0;
				q[i].next[j] = -1;
			}
		}
	}
}

void Pathds(set<int>* ds, char mapp[], int d[], int m) {
        int i, j, k;
        set<int>::iterator sk;
        memset(d, 1, sizeof(d));
        for (sk=ds->begin(); sk!=ds->end(); sk++) {
                k = *sk;
                for (i=0; i<m; i++) {
                        for (j=0; j<m; j++) {
                                if (mapp[i*m+k] || mapp[k*m+j]) continue;
                                if (d[i*m+j] > (d[i*m+k]+d[k*m+j])) {
                                        d[i*m+j] = d[i*m+k] + d[k*m+j];
                                        //q[i].next[j] = q[i].next[*sk];
				}
			}
		}
	}
}

int main() {
        int m = 100;
        struct node q[m];
        char map[m*m];
        unsigned int d[m*m];
        set<int> ds;
        srand((unsigned)time(0));

        GenerateDiskGraph(q, m, 1000, 1000);
        GenerateGraph(q, m, map, d);
        centralized(&ds, q, m, map, d);
        printf("%d\n", ds.size());

        int i, j;
        double avglen = 0;
        for (i=0; i<m; i++) {
                for (j=0; j<m; j++) {
                        if (i == j) continue;
                        avglen += d[i*m+j];
                }
        }
        avglen /= (m*(m-1));
        printf("%lf\n", avglen);
        set<int>::iterator si;
	return 0;
}
