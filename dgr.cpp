#include <stdlib.h>
#include <time.h>
#include <queue>

struct node {
	private:
		int x, y;
		int id, radius;
		vector<node *> path;
	public:
		node(int xx, int yy, int a, int b):
			x(xx), y(yy), id(a), radius(b)
	{
	}
}

int centralized(set<node> d, priority_queue<node, vector<node>, cmp> q) {
	while (!q.empty()) {
		d.push(q.top());
		u = q.top().id;
		q.pop();
		v = q.top().id;
		while (map[u][v] && map[v][u]) {
			q.pop();
		}
	}

}

void GenerateDiskGraph(struct node[] q, int width, int height) {
	int i, n;
	node nd;

	n = rand(m);
	const int maxr = width*width + height*height;
	q[0] = nd;
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
	minr = int((x - q[n].x)*(x - q[n].x) + (y - q[n].y)*(y - q[n].y)) + 1;
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
	
	memset(map, 0, mapsize);
	for (i=0; i<m; i++) {
		for (j=0; j<m; j++) {
			if ((q[i].x-q[j].x)*(q[i].x-q[j].x)+(q[i].y-q[j].y)*(q[i].y-q[j].y) < q[i].r) {
				map[i][j] = 1;
			}
		}
	}
}

int main() {
	randomize();
	return 0;
}
