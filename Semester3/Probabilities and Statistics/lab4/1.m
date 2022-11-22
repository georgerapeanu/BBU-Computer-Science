clear
p = input('give the probability');
N = input('give the nb of sim');
U = rand(1,N);
X = (U < p);
U_X = unique(X)
n_X = hist(X,length(U_X));
rel_freq = n_X / N