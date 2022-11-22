clear
p = input('give the probability ');
N = input('give the nb of sim ');
for i=1:N
	X(i) = 0;
	while rand >= p
		X(i) = X(i)+1;
	endwhile
endfor
k=0:20;
U_X = unique(X);
n_X = hist(X,length(U_X));
rel_freq = n_X / N;
plot(U_X,rel_freq,'*',k,geopdf(k,p),'*r')