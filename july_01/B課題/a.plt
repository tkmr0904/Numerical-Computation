load "I.plt";\
set output "(b)RKI.png";\
plot "error_RKI" using 1:2;\
\
set output "(b)eulerI.png";\
plot "error_eulerI" using 1:2;\
\
\
load "Q.plt";\
set output "(b)eulerQ.png";\
plot "error_eulerQ" using 1:2;\
\
set output "(b)RKQ.png";\
plot "error_RKQ" using 1:2;\