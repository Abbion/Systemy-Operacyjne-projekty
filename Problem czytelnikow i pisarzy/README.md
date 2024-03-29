# Problem czytelników i pisarzy
Zadanie zsynchronizowania dwóch grup procesów: czytelników i pisarzy, konkurujących o dostęp do
wspólnej czytelni. Proces czytelnik: co jakiś czas odczytuje informację zgromadzoną w czytelni i może
to robić razem z innymi czytelnikami; Proces pisarz: co jakiś czas zapisuje swoją informację i musi
wówczas przebywać sam w czytelni; W zadaniu tym może wystąpić tzw. zjawisko zagłodzenia jednej z
grup procesów. Występuje ono wówczas, gdy proces nie zostaje wznowiony, mimo że zdarzenie, na
które czeka występuje dowolną ilość razy. Za każdym razem, gdy proces ten mógłby być wznowiony,
wybierany jest jakiś inny oczekujący proces.

Rozważ 2 rozwiązania problemu czytelników i pisarzy:

• Rozwiązanie z możliwością zagłodzenia pisarzy – priorytet czytelnika;

• Rozwiązanie z możliwością zagłodzenia czytelników – priorytet pisarza;

Rozwiązać zadanie w 2 wersjach przy pomocy semaforów. Przyjąć, że liczba miejsc w czytelni jest
ograniczona i ustalona na pewną wartość M. Liczba czytelników oraz pisarzy może być zarówno większa
jak i mniejsza od M. Napisać program do generowania procesów czytelników i pisarzy w oparciu o
funkcje fork() i exec(). Zademonstrować zjawisko zagłodzenia procesów pisarza i procesów czytelnika.
Do symulacji różnych prędkości działania programów użyć np. funkcji sleep() z losową liczbą sekund.
Zaimplementuj obsługę przerwania wywołania funkcji systemowej semop(). Dla funkcji systemowych
zaprogramować obsługę błędów w oparciu o funkcję perror() i zmienną errno.
Program główny sprawdza dopuszczalny limit procesów, które może użytkownik uruchomić w danym
momencie i w przypadku, kiedy limit jest większy lub równy liczbie tworzonych procesów, uruchamia
zadanie.

Przykładowe wywołanie „powielacza”.

./program_główny liczba_p liczba_c liczba_m

gdzie, liczba_p - liczba pisarzy,

liczba_c - liczba czytelników,

liczba_m - liczba miejsc w czytelni.

[]$ ./prog 2 5 3
