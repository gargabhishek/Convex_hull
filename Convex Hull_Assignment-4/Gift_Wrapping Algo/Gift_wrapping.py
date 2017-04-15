print('hi')
import numpy as np
import timeit
start = timeit.default_timer()

# Function to know if we have a CCW turn
def CCW(p1, p2, p3):
	if (p3[1]-p1[1])*(p2[0]-p1[0]) >= (p2[1]-p1[1])*(p3[0]-p1[0]):
		return True
	return False

# Main function:
def GiftWrapping(S):
	n = len(S)
	P = [None] * n
	l = np.where(S[:,0] == np.min(S[:,0]))
	pointOnHull = S[l[0][0]]
	i = 0
	while True:
		P[i] = pointOnHull
		endpoint = S[0]
		for j in range(1,n):
			if (endpoint[0] == pointOnHull[0] and endpoint[1] == pointOnHull[1]) or not CCW(S[j],P[i],endpoint):
				endpoint = S[j]
		i = i + 1
		pointOnHull = endpoint
		if endpoint[0] == P[0][0] and endpoint[1] == P[0][1]:
			break
	for i in range(n):
		if P[-1] == None:
			del P[-1]
	return np.array(P)

def main():
  # By default we build a random set of N points with coordinates in [0,300)x[0,300):
	P = np.array([(np.random.randint(0,1000000),np.random.randint(0,300)) for i in range(8000)])
	print('input')
	print(P)
	L = GiftWrapping(P)
	print('output')
	print(L)
	stop = timeit.default_timer()
	print(stop-start)

	
main()