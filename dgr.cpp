#include <stdlib.h>
#include <time.h>
#include <queue>

struct node {
	int x, y;
	int id, radius;
	int[1600] next;
}

int centralized(set<int> ds, struct node[] q, int qsize) {
	set<int>::iterator si;
	int i, j, k;
	bool flag[qsize];
	
	i = 0;
	memset(flag, 0 ,sizeof(bool)*qsize);
	while (i < qsize) {
		ds.insert(i);
		flag[i] = 1;
		for (j=i+1; j<qsize; j++) {
			if (map[i][j] && map[j][i]) flag[j] = 1;
		}
		while ((i<qsize) && (flag[i])) i+=1;
	}

	for (k=0; k<ds.size; k++) {
		for (i=0; i<di; i++) {
			for (j=0; j<di; j++) {
				if (d[i][j] > (d[i][k]+d[k][j])) {
					d[i][j] = d[i][k] + d[k][j];
					q[ds[i]].next[ds[j]] = q[ds[i]].next[ds[k]];
				}
			}
		}
	}
}

void GenerateDiskGraph(struct node[] q, int m, int width, int height) {
	int i, n;

	n = rand(m);
	const int maxr = width*width + height*height;
	q[0].x = rand(width);
	q[0].y = rand(height);
	q[0].id = 0;
	for (i=1; i<=n; i++) {
		x = rand(width); y = rand(height);
		minr = (x - q[i-1].x)*(x - q[i-1].x) + (y - q[i-1].y)*(y - q[i-1].y);
		nd = new node(x, y , i, rand(maxr - minr) + minr);
		q[i].x = x;
		q[i].y = y;
		q[i].id = i;
		q[i].r = rand(maxr-minr) + minr;
	}
	minr = (x - q[n].x)*(x - q[n].x) + (y - q[n].y)*(y - q[n].y);
	q[0].r = rand(maxr - minr) + minr;
	for (; i<m; i++) {
		nd = new node(rand(width), rand(height), i, rand(maxr));
		q[i].x = rand(width);
		q[i].y = rand(height);
		q[i].id = i;
		q[i].r = rand(maxr);
	}
}

void GenerateGraph(struct node[] q, int m, char* map, int mapsize) {
	int i, j;
	
	for (i=0; i<m; i++) {
		for (j=0; j<m; j++) {
			if ((q[i].x-q[j].x)*(q[i].x-q[j].x)+(q[i].y-q[j].y)*(q[i].y-q[j].y) < q[i].r) {
				map[i][j] = 1;
				q[i].next[j] = j;
			} else {
				map[i][j] = 0;
				q[i].next[j] = -1;
			}
		}
	}
}

int main() {
	randomize();
	return 0;
}
