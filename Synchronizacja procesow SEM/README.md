# Synchronizacja procesów przy pomocy semaforów zadanie

Rozwiązać zadanie synchronizacji trzech procesów przy pomocy semaforów:

P1: t11, t12

P2: t21, t22, t23

P3: t31, t32, t33

Kolejność czasowa zdefiniowana jest zbiorem par G={(t21,t31),(t32,t22),(t22,t11),(t12,t23),(t23,t33)}.

Jeżeli para (a,b) należy do zbioru, to akcja b musi być poprzedzona akcją a.
Każdy z tasków tij(dla i,j=1,2,3) wyprowadza na ekran ciąg znaków:
Sekcja tij procesu o PID=tu podaje PID procesu,
oraz powyższy ciąg znaków zapisuje w pliku o nazwie wynik.txt.
Każdy z tasków kończy się funkcją: sleep(1);
Napisz program do generowania procesów P1, P2, P3 w oparciu o funkcje fork(), exec() (projekt nr
1_3). W programie tym należy utworzyć oraz usunąć (po zakończeniu procesów P1, P2, P3) zbiór
semaforów użyty do synchronizacji. Do tworzonych struktur ustawić minimalne prawa dostępu,
konieczne do wykonania zadania.
