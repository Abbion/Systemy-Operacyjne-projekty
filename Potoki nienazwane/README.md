# Potoki nienazwane zadanie
Wykorzystując potoki nienazwane uogólnić zadanie producent–konsument na wielu producentów i
wielu konsumentów. W zadaniu wykorzystać jedno łącze nienazwane.
Argumentem wywołania programu jest liczba konsumentów, liczba producentów oraz liczba znaków
„wyprodukowanych” przez każdego producenta (np. ./prog 10 50 1000). Program sprawdza
dopuszczalny limit procesów, które może użytkownik uruchomić w danym momencie (np. przy pomocy
funkcji popen()) i w przypadku, kiedy limit jest większy lub równy liczbie tworzonych procesów,
uruchamia zadanie.
Każdy z producentów losuje określoną trzecim argumentem wywołania liczbę znaków. Wylosowane
znaki zapisuje – po jednym znaku - do potoku oraz swojego pliku z danymi (np. we_1250.txt, gdzie
podany numer to pid procesu, który utworzył dany plik). Każdy z konsumentów odczytuje po jednym
znaku z potoku i zapisuje w swoim pliku z wynikami (np.: wy_1320.txt). Po zakończeniu zadana liczba
znaków we wszystkich plikach we_*.txt musi się równać liczbie znaków we wszystkich plikach wy_*.txt.
Pliki
Dla funkcji systemowych zaprogramować obsługę błędów w oparciu o funkcję perror() i zmienną errno.
