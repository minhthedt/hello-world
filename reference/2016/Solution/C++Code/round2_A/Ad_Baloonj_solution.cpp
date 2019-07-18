#include<stdio.h>
#include<math.h>

int main() {
	int t, tc;
	int ox, oy, n;
	double theta1, theta2;
	int ans;
	scanf("%d", &t);

	for (tc = 0; tc < t; tc++) {
		scanf("%d%d%d", &ox, &oy, &n);
		theta1 = atan2(oy, ox);
		theta2 = atan2(oy, n - ox);
		ans=ceil((theta1 + theta2) * 2 * oy  + n);
		printf("%d\n", ans);
	}

	return 0;
}